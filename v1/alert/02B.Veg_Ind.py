#Estimation of Vegetation fraction
#@Author: Zhen Song 09/14/2023
#import pandas as pd
import numpy as np
from joblib import Parallel, delayed
import joblib
from datetime import datetime
import os
import sys
import subprocess
import csv
from sklearn.decomposition import PCA
from sklearn.neighbors import KNeighborsRegressor
import sklearn.neighbors
import warnings
from sklearn.exceptions import DataConversionWarning
warnings.filterwarnings(action='ignore', category=DataConversionWarning)
import parameters
try:
	from osgeo import gdal
except:
	import gdal

currdir = os.getcwd()
softwareVersion = parameters.softwareVersion
DISTversion = parameters.DISTversion
HLSsource = parameters.HLSsource #"/gpfs/glad3/HLS"
outbase = parameters.outbase #"/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT"
dbpath = parameters.dbpath #"/gpfs/glad3/HLSDIST/System/database/"

def estimateVF(redfile,nirfile,sw1file,sw2file,fmaskfile,fileOceanMask,vfOutFileVF,vfOutFileMask):

    dsred = gdal.Open(redfile)
    dsnir = gdal.Open(nirfile)
    dssw1 = gdal.Open(sw1file)
    dssw2 = gdal.Open(sw2file)
    dsqa = gdal.Open(fmaskfile)
    if dsred is not None and dsnir is not None and dssw1 is not None and dssw2 is not None and dsqa is not None:
        hlsnrow = int(dsred.RasterYSize)
        hlsncol = int(dsred.RasterXSize)
        
        matred = dsred.GetRasterBand(1).ReadAsArray(0,0,hlsncol,hlsnrow)
        matnir = dsnir.GetRasterBand(1).ReadAsArray(0,0,hlsncol,hlsnrow)
        matsw1 = dssw1.GetRasterBand(1).ReadAsArray(0,0,hlsncol,hlsnrow)
        matsw2 = dssw2.GetRasterBand(1).ReadAsArray(0,0,hlsncol,hlsnrow)
        matqa = dsqa.GetRasterBand(1).ReadAsArray(0,0,hlsncol,hlsnrow)
    else:
        dsred = None
        dsnir = None
        dssw1 = None
        dssw2 = None
        dsqa = None
        return False

    if matred is None or matnir is None or matsw1 is None or matsw2 is None or matqa is None:
        dsred = None
        dsnir = None
        dssw1 = None
        dssw2 = None
        dsqa = None
        return False
    else:
        red = np.reshape(matred,(hlsnrow*hlsncol))
        nir = np.reshape(matnir,(hlsnrow*hlsncol))
        sw1 = np.reshape(matsw1,(hlsnrow*hlsncol))
        sw2 = np.reshape(matsw2,(hlsnrow*hlsncol))
        qa = np.reshape(matqa,(hlsnrow*hlsncol))
        
        cloud = (qa/2)%2
        cbuffer = (qa/4)%2
        shadow = (qa/8)%2
        ice = (qa/16)%2
        water = (qa/32)%2

        dsOcean = gdal.Open(fileOceanMask)
        ocean = dsOcean.GetRasterBand(1).ReadAsArray(0,0,hlsncol,hlsnrow)
        matOcean = np.reshape(ocean,(hlsnrow*hlsncol))

        #index excluding cloud,cloud buffer,cloud shadow, ice, water
        index = np.where((red>0)&(nir>0)&(sw1>0)&(sw2>0)&(qa!=255)&(cloud!=1)&(cbuffer!=1)&(shadow!=1)&(ice!=1)&(water!=1))[0]
        # water QA within 1km coastal line, calculate VF for water area
        indexWater = np.where((red>0)&(nir>0)&(sw1>0)&(sw2>0)&(qa!=255)&(cloud!=1)&(cbuffer!=1)&(shadow!=1)&(ice!=1)&(water==1)&(matOcean<=1))[0]
        #for QA water and any band<0
        indexQAWaterBand = np.where((qa!=255)&(cloud!=1)&(cbuffer!=1)&(shadow!=1)&(ice!=1)&(water==1)&(matOcean<=1)&((red<=0) + (nir<=0) + (sw1<=0) + (sw2<=0)))[0]
        #land mask and water mask for QA
        indexQALand = np.where((qa!=255)&(cloud!=1)&(cbuffer!=1)&(shadow!=1)&(ice!=1)&(water!=1))[0]
        indexQAWater = np.where((qa!=255)&(cloud!=1)&(cbuffer!=1)&(shadow!=1)&(ice!=1)&(water==1)&(matOcean<=1))[0]

        #write the output
        #get all the metadata
        sourceMetadata = dsred.GetMetadata()
        sensingTime = sourceMetadata['SENSING_TIME']
        spatialCover = sourceMetadata['spatial_coverage']
        cloudCover = sourceMetadata['cloud_coverage']
        if (sensorTag == 'L30'):
            landsatID = sourceMetadata['LANDSAT_PRODUCT_ID']
            if(landsatID[0:4] == 'LC08'):
                sourceSate = 'Landsat-8'
            elif(landsatID[0:4] == 'LC09'):
                sourceSate = 'Landsat-9'
            else: 
                sourceSate = landsatID[0:4]
                print("Landsat satellite unknown: "+landsatID)
            sourceID = landsatID
        elif (sensorTag == 'S30'):
            sourceSate = sourceMetadata['SPACECRAFT_NAME']
            sourceID = sourceMetadata['PRODUCT_URI']
        else:
            print('ERROR: unknown satellite!')
            
        vfpred = [255]*hlsnrow*hlsncol
        vfpred = np.reshape(vfpred,(hlsnrow*hlsncol,1))
        matvfpred = np.reshape(vfpred,(hlsncol,hlsnrow))
        mask = [0]*hlsnrow*hlsncol
        mask = np.reshape(mask,(hlsnrow*hlsncol,1))
        matMask = np.reshape(mask,(hlsncol,hlsnrow))
        if len(indexQALand) ==0:

            #outds = tifDriver.Create(vfOutFileVF, hlsncol, hlsnrow, 1, gdal.GDT_Byte,options = creation_Options)
            outds = tifDriver.Create(vfOutFileVF[0:-4]+"TEMP.tif", hlsncol, hlsnrow, 1, gdal.GDT_Byte,options = creation_Options)
            outds.GetRasterBand(1).WriteArray(matvfpred)
            outds.BuildOverviews("NEAREST",[2,4,8])
            outds.GetRasterBand(1).SetNoDataValue(255)
            outds.GetRasterBand(1).SetDescription("Vegetation_percent")
            outds.SetGeoTransform(dsred.GetGeoTransform())
            outds.SetProjection(dsred.GetProjectionRef())
            
            #write the metadata
            outds.SetMetadata({'cloud_coverage':cloudCover,'HLS_SCENE_ID':sceneName,'SENSING_TIME':sensingTime,'SOURCE_PRODUCT_ID':sourceID,'SOURCE_SATELLITE':sourceSate,'spatial_coverage':spatialCover,'Units':'percent','Valid_max':'100','Valid_min':'0'})
            current_date_and_time = datetime.now()

            #print("Results saved...",current_date_and_time)
            outds = None
            subprocess.run(["gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q "+vfOutFileVF[0:-4]+"TEMP.tif "+vfOutFileVF+" 2>>errorLOG.txt; rm "+vfOutFileVF[0:-4]+"TEMP.tif"],capture_output=True,shell=True)

            if len(indexQAWater)!=0:
                mask[indexQAWater,:] = 2
            matMask = np.reshape(mask,(hlsncol,hlsnrow))
            #outds = tifDriver.Create(vfOutFileMask, hlsncol, hlsnrow, 1, gdal.GDT_Byte,options = creation_Options)
            outds = tifDriver.Create(vfOutFileMask[0:-4]+"TEMP.tif", hlsncol, hlsnrow, 1, gdal.GDT_Byte,options = creation_Options)
            outds.GetRasterBand(1).WriteArray(matMask)
            outds.BuildOverviews("NEAREST",[2,4,8])
            outds.SetGeoTransform(dsred.GetGeoTransform())
            outds.SetProjection(dsred.GetProjectionRef())
            outds.GetRasterBand(1).SetDescription("Data_mask")
            outds.SetMetadata({'Valid_min':'0','Valid_max':'2','Units':'unitless','flag_values':'0,1,2','flag_meanings':'no_data_or_masked,land,water'})

            dsred = None
            dsnir = None
            dssw1 = None
            dssw2 = None
            dsqa = None
            outds = None
            dsOcean = None
            subprocess.run(["gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q "+vfOutFileMask[0:-4]+"TEMP.tif "+vfOutFileMask+" 2>>errorLOG.txt; rm "+vfOutFileMask[0:-4]+"TEMP.tif"],capture_output=True,shell=True)
            return True
        else:
            dfhls = np.transpose(np.vstack([red,nir,sw1,sw2]))
            #calculate PCAs
            dfhlsMean = dfhls-meanBands
            pca1hlsm = dfhlsMean * pca1Cors
            pca1hls = np.sum(pca1hlsm, axis = 1)
            pca2hlsm = dfhlsMean * pca2Cors
            pca2hls = np.sum(pca2hlsm, axis = 1)
            pca3hlsm = dfhlsMean * pca3Cors
            pca3hls = np.sum(pca3hlsm, axis = 1)
            pcahls = np.transpose(np.vstack([pca1hls,pca2hls,pca3hls]))
            #VF calculation for water with positive reflectance
            if len(indexWater) != 0:
                pcaCopy = pcahls[indexWater,:].copy()
                vfpred[indexWater,:]= knn_from_joblib.predict(pcaCopy)
            #water area with negative reflectance
            if len(indexQAWaterBand)!=0:
                vfpred[indexQAWaterBand,:] = 0
            #VF calculation for land
            if len(index) !=0:
                pcaCopy = pcahls[index,:].copy()
                vfpred[index,:]= knn_from_joblib.predict(pcaCopy)+0.49
            vfpred = np.round(vfpred)
            matvfpred = np.reshape(vfpred,(hlsncol,hlsnrow))     
            #write the VF-IND 
            #outds = tifDriver.Create(vfOutFileVF, hlsncol, hlsnrow, 1, gdal.GDT_Byte,options = creation_Options)
            outds = tifDriver.Create(vfOutFileVF[0:-4]+"TEMP.tif", hlsncol, hlsnrow, 1, gdal.GDT_Byte,options = creation_Options)
            outds.GetRasterBand(1).WriteArray(matvfpred)
            outds.BuildOverviews("NEAREST",[2,4,8])
            outds.GetRasterBand(1).SetNoDataValue(255)
            outds.SetGeoTransform(dsred.GetGeoTransform())
            outds.SetProjection(dsred.GetProjectionRef())
            outds.GetRasterBand(1).SetDescription("Vegetation_percent")
            #write the metadata
            outds.SetMetadata({'cloud_coverage':cloudCover,'HLS_SCENE_ID':sceneName,'SENSING_TIME':sensingTime,'SOURCE_PRODUCT_ID':sourceID,'SOURCE_SATELLITE':sourceSate,'spatial_coverage':spatialCover,'Units':'percent','Valid_max':'100','Valid_min':'0'})
            
            outds = None
            subprocess.run(["gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q "+vfOutFileVF[0:-4]+"TEMP.tif "+vfOutFileVF+" 2>>errorLOG.txt; rm "+vfOutFileVF[0:-4]+"TEMP.tif"],capture_output=True,shell=True)

            #print("Results saved...",current_date_and_time)
            #write the data-mask
            if len(indexQALand)!=0:
                mask[indexQALand,:] = 1
            if len(indexQAWater)!=0:
                mask[indexQAWater,:] = 2
            matMask = np.reshape(mask,(hlsncol,hlsnrow))
            #outds = tifDriver.Create(vfOutFileMask, hlsncol, hlsnrow, 1, gdal.GDT_Byte,options = creation_Options)
            outds = tifDriver.Create(vfOutFileMask[0:-4]+"TEMP.tif", hlsncol, hlsnrow, 1, gdal.GDT_Byte,options = creation_Options)
            outds.GetRasterBand(1).WriteArray(matMask)
            outds.BuildOverviews("NEAREST",[2,4,8])
            outds.SetGeoTransform(dsred.GetGeoTransform())
            outds.SetProjection(dsred.GetProjectionRef())
            outds.GetRasterBand(1).SetDescription("Data_mask")
            outds.SetMetadata({'Valid_min':'0','Valid_max':'2','Units':'unitless','flag_values':'0,1,2','flag_meanings':'no_data_or_masked,land,water'})
            #print("Mask results saved...",current_date_and_time)

            dsred = None
            dsnir = None
            dssw1 = None
            dssw2 = None
            dsqa = None
            outds = None
            dsOcean = None
            subprocess.run(["gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q "+vfOutFileMask[0:-4]+"TEMP.tif "+vfOutFileMask+" 2>>errorLOG.txt; rm "+vfOutFileMask[0:-4]+"TEMP.tif"],capture_output=True,shell=True)
            return True


################################### Main ######################################
#                                                                             #
#                                                                             #
###############################################################################
if __name__=='__main__':
    
    sceneName = sys.argv[1]
    timeTag = sceneName[15:29]
    sensorTag = sceneName[4:7]
    tileID = sceneName[9:14]
    UTMTile = tileID[0:2]
    strYear = timeTag[0:4]
    dir1 = tileID[2:3]
    dir2 = tileID[3:4]
    dir3 = tileID[4:5]
    sceneNameOut = "DIST-ALERT_" + timeTag + "_"+sensorTag+"_T"+tileID+"_v1"
    outdir = outbase + "/" + strYear+"/"+ UTMTile+"/"+dir1+"/"+dir2+"/"+dir3+"/"+sceneNameOut+"/"
    #sceneNameOut = sys.argv[2]
    #outdir = sys.argv[3]
    #indir = "/gpfs/glad3/HLS/"
    vfOutFileVF = outdir + sceneNameOut+"_VEG-IND.tif"
    vfOutFileMask = outdir + sceneNameOut+"_DATA-MASK.tif"
    
    if os.path.exists(vfOutFileVF) and os.path.exists(vfOutFileMask):
        #sys.exit()
        subprocess.run(["rm "+vfOutFileVF+"; rm "+vfOutFileMask],capture_output=True,shell=True)
    
    if not os.path.exists(outdir):
        os.makedirs(outdir)

    #parameters for PCA calculation
    meanBands = [ 962.36981326, 2739.72170079, 2507.32144293, 1699.98534611]
    pca1Cors = [0.39171294, 0.13214845, 0.65269708, 0.63488919]
    pca2Cors = [-0.08873281,  0.97900485,  0.03097958, -0.18087639]
    pca3Cors = [ 0.90892619,  0.05643538, -0.36028748, -0.20214144]
    #load the model from the file 
    knn_from_joblib = joblib.load('KNNModel_20230607.pkl')
    tifDriver = gdal.GetDriverByName("GTiff")
    creation_Options = ["COMPRESS=DEFLATE", "TILED=YES",]

    oceanFile = "/gpfs/glad3/HLSDIST/OceanMask/oceanMaskMissingList.txt"
    fileOceanMask = "/gpfs/glad3/HLSDIST/OceanMask/"+UTMTile+"/"+tileID+"_ocean.tif"
    #Check the availability of ocean mask
    if not os.path.exists(fileOceanMask):
        with open(oceanFile, 'a') as TXT: 
            TXT.write(tileID+"\n")
        print("Ocean mask for tile:" + tileID + " doesn't exist!")
        sys.exit()
    #input and output
    indirTile = HLSsource + "/" + sensorTag + "/" + strYear + "/" + UTMTile + "/" + dir1 + "/" + dir2 + "/" + dir3 + "/"+sceneName + "/"
    if sensorTag == "L30":
        redfile = indirTile +'/'+ sceneName + '.B04.tif'
        nirfile = indirTile + '/'+sceneName + '.B05.tif'
        sw1file = indirTile + '/'+sceneName + '.B06.tif'
        sw2file = indirTile +'/'+ sceneName + '.B07.tif'
    else:
        redfile = indirTile +'/'+ sceneName + '.B04.tif'
        nirfile = indirTile + '/'+sceneName + '.B8A.tif'
        sw1file = indirTile + '/'+sceneName + '.B11.tif'
        sw2file = indirTile +'/'+ sceneName + '.B12.tif'

    fmaskfile = indirTile + '/'+sceneName + '.Fmask.tif'

    #check if all the needed bands are available
    if(os.path.exists(redfile) and os.path.exists(nirfile) and os.path.exists(sw1file) and os.path.exists(sw2file) and os.path.exists(fmaskfile)):
        if estimateVF(redfile,nirfile,sw1file,sw2file,fmaskfile,fileOceanMask,vfOutFileVF,vfOutFileMask):
            completed = True
            #print("VF calculation for "+sceneName+" finished.")
        else:
            print("Error in reading files: " + sceneName + ".")
    else:
        print("One of the red,nir,sw1,sw2 or qa bands is not availbable for " + sceneName+".")
        with open("missingHLS.txt","a") as MIS:
            MIS.write(sceneName+"\n")