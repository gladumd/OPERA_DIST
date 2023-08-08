import datetime
import subprocess
import sys
import os
import traceback

currdir = os.getcwd()

def makeBrowse(OUT_ID,outdir):
  try:
    inputfile = outdir+"/"+OUT_ID+"_VEG-DIST-STATUS.tif"
    colorRamp = currdir+"/browseColorRamp.clr"
    hiresFile=outdir+"/"+OUT_ID+"_VEG-DIST-STATUS_browse.tif"
    pngFile=outdir+"/"+OUT_ID+"_VEG-DIST-STATUS.png"
    if not os.path.exists(pngFile):
      tmpTif=outdir+"/"+OUT_ID+"_VEG-DIST-STATUS_tmp.tif"

      # Create a temporary GeoTIFF file, subsampling to 1024 samples on the
      # x-axis, with subsampling on the y-axis maintained to the aspect ratio of
      # the source data. Force it to remember the nodata value is 255.
      # E.g., if you wanted a higher subsampling rate, you could try a number like
      # 512, or for less subsampling, you could try 2048. You can also play with
      # values like 50%. For data like SNWG, I'd start with 1024, and play
      # with it as needed.
      response = subprocess.run(["ssh gladapp17 'gdal_translate -of GTiff -outsize 1024 0 -a_nodata 255 " + outdir+"/"+OUT_ID+"_VEG-DIST-STATUS.tif "+tmpTif+"'"],capture_output=True,shell=True)

      ## Create a colorized PNG, with a transparent alpha band. The "nv" line in
      ## the color ramp includes a fourth dimension to specify full transparency
      ## for nodata values.
      response = subprocess.run(["ssh gladapp17 'gdaldem color-relief -of PNG -alpha "+tmpTif+" "+ colorRamp +" "+pngFile+"'"],capture_output=True,shell=True)
      os.system("rm "+tmpTif+"; rm "+pngFile+".aux.xml")

    if not os.path.exists(hiresFile):
      response = subprocess.run(["gdal_calc.py -A "+inputfile+" --outfile="+outdir+"/temp.tif --calc=\"A+(A==0)*255\" --quiet"],capture_output=True,shell=True)
      response = subprocess.run(["gdalbuildvrt "+outdir+"/temp.vrt "+outdir+"/temp.tif"],capture_output=True,shell=True)
      with open(outdir+"/temp.vrt",'r') as vrtin:
        lines = vrtin.readlines()
      with open(outdir+"/temp2.vrt",'w') as vrtout:
        for line in lines:
          if "ColorInterp" in line:
            vrtout.write("<ColorInterp>Palette</ColorInterp>\n<ColorTable>")
            with open("browseColorRamp.clr",'r') as ramp:
              entries = ramp.readlines()[1:]
            for entry in entries:
              v = entry.strip().split(" ")
              vrtout.write("<Entry c1=\""+v[1]+"\" c2=\""+v[2]+"\" c3=\""+v[3]+"\" c4=\""+v[4]+"\"/>\n")
            vrtout.write("</ColorTable>")
          else:
            vrtout.write(line)
      response = subprocess.run(["gdal_translate -co COMPRESS=DEFLATE -co TILED=YES "+outdir+"/temp2.vrt "+hiresFile],capture_output=True,shell=True)
      response = subprocess.run(["gdaladdo "+hiresFile+" 2 4 8"],capture_output=True,shell=True)
      response = subprocess.run(["rm "+outdir+"/temp*"],capture_output=True,shell=True)
      #gdal.Calc("A+(A==0)*255",A=inputfile,outfile=hiresFile,creation_option="COMPRESS=DEFLATE")

  except:
    with open("errorLOG.txt", 'a') as ERR:
      ERR.write(OUT_ID+" error in creating browse"+str(datetime.datetime.now()))
    traceback.print_exc()
    return("fail")

if __name__ == "__main__":
  OUT_ID = sys.argv[1]
  outdir = sys.argv[2]
  makeBrowse(OUT_ID,outdir)
