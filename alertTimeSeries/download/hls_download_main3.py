 # -*- coding: utf-8 -*- 
 
"""
===============================================================================
HLS downloading   - Main module                         
Authors:Cole Krehbiel and Mahsa Jami
Date: 12/16/2021

-------------
Adaptaded by André Lima & Will Byrne
Date: 02/23/2022
Last Updated:                                             
===============================================================================
"""
######################### IMPORT PACKAGES #####################################
import argparse
import sys
from shapely.geometry import box
import geopandas as gp
import pandas as pd
import os
import datetime as dt
import aiohttp
import asyncio
import time
import concurrent.futures

######################### USER-DEFINED VARIABLES ##############################
parser = argparse.ArgumentParser(formatter_class=argparse.ArgumentDefaultsHelpFormatter, description='Customized download code for HLS V2.0 files')
 
# (-tile) Download images listed in *.csv file or (-all) every hls images processed since 04/03/2014 to current day
tiles_gr = parser.add_mutually_exclusive_group(required=True)
tiles_gr.add_argument('-all', action='store_true')
tiles_gr.add_argument('-tile', action='store_true')
# parser.add_argument('-path', required=False, help='Download tiles listed in *.txt/*.csv file')
tiles_gr.add_argument('-area', action='store_true')

# roi: Region of interest as shapefile, geojson, or comma separated LL Lon, LL Lat, UR Lon, UR Lat
parser.add_argument('-roi', type=str, nargs='*', required=False, help="(Required) Region of Interest (ROI) for spatial subset. \
                    Valid inputs are: (1) a geojson or shapefile (absolute path to file required if not in same directory as this script), or \
                    (2) bounding box coordinates: 'LowerLeft_lon,LowerLeft_lat,UpperRight_lon,UpperRight_lat'\
                    NOTE: Negative coordinates MUST be written in single quotation marks '-120,43,-118,48'\
                    NOTE 2: If providing an absolute path with spaces in directory names, please use double quotation marks "" ")

# dir: Directory to save the files to
parser.add_argument('-dir', required=False, help='Directory to export output HLS files to.', default=os.getcwd())

# start: Start Date
parser.add_argument('-start', required=False, help='Start date for time period of interest: valid format is mm/dd/yyyy (e.g. 10/20/2020).', default='04/03/2014')

# end: End Date
parser.add_argument('-end', required=False, help='Start date for time period of interest: valid format is mm/dd/yyyy (e.g. 10/24/2020).', default=dt.datetime.today().strftime ("%m/%d/%Y"))                    

# prod: product(s) desired to be downloaded
parser.add_argument('-prod', choices = ['HLSS30' , 'HLSL30', 'both'] ,required=False, help='Desired product(s) to be subset and processed.', default='both')

# layers: layers desired to be processed within the products selected
parser.add_argument('-bands', required=False, help="Desired layers to be processed. Valid inputs are ALL, COASTAL-AEROSOL, BLUE, GREEN, RED, RED-EDGE1, RED-EDGE2, RED-EDGE3, NIR1, SWIR1, SWIR2, CIRRUS, TIR1, TIR2, WATER-VAPOR, FMASK. To request multiple layers, provide them in comma separated format with no spaces. Unsure of the names for your bands?--check out the README which contains a table of all bands and band names.", default='ALL')

args = parser.parse_args()

######################### Handle Inputs #######################################


# REGION OF INTEREST ----------------------------------------------------------
ROI = args.roi

if ROI is not None:

    # Verify ROI is valid
    if type(ROI) == list:
        # if submitted as a list, reformat to a comma separated string
        ROI_s = ''
        for c in ROI: ROI_s += f'{c},'
        ROI = ROI_s[:-1]
        
    if ROI.endswith(('json', 'shp')): 
        # Read file in and grab bounds
        try:
            bbox = gp.GeoDataFrame.from_file(ROI)
            
            # Check if ROI is in Geographic CRS, if not, convert to it
            if bbox.crs.is_geographic:
                bbox.crs = 'EPSG:4326'
            else:
                bbox.to_crs("EPSG:4326", inplace=True)
                print("Note: ROI submitted is being converted to Geographic CRS (EPSG:4326)")
            # Check for number of features included in ROI
            if len(bbox) > 1:                                                            
                print('Multi-feature polygon detected. Only the first feature will be used.')
                bbox = bbox[0:1]
        except:
            sys.exit(f"The GeoJSON/shapefile is either not valid or could not be found.\nPlease double check the name and provide the absolute path to the file or make sure that it is located in {os.getcwd()}")     
        
        # Verify the geometry is valid and convert to comma separated string
        if  bbox['geometry'][0].is_valid:
            bounding_box = [b for b in bbox['geometry'][0].bounds]
            bbox_string = ''
            for b in bounding_box: bbox_string += f"{b},"
            bbox_string = bbox_string[:-1]
        else:
            sys.exit(f"The GeoJSON/shapefile: {ROI} is not valid.")
            
    # Verify bounding box coords
    else:
        if len(ROI.split(',')) != 4:
            sys.exit("Valid roi options include: geojson (.json or .geojson), shapefile (.shp), or a comma separated string containing bounding box coordinates: 'LL-Lon,LL-Lat,UR-Lon,UR-Lat' (single quotes included)")
        else:
            try:
                bbox = [float(rr.strip(']').strip('[').strip("'").strip('"').strip(' ')) for rr in ROI.split(',')]
            except ValueError:
                sys.exit('Invalid coordinate detected in roi provided. Valid bbox coordinates must be numbers (int or float).')
            
            # Check that bbox coords are within the bounds of geographic CRS
            if bbox[0] < -180 or bbox[0] > 180:
                sys.exit(f"{bbox[0]} is not a valid entry for LL-lon (valid range is -180 to 180)")
            if bbox[2] < -180 or bbox[2] > 180:
                sys.exit(f"{bbox[2]} is not a valid entry for UR-lon (valid range is -180 to 180)")
            if bbox[1] < -90 or bbox[1] > 90:
                sys.exit(f"{bbox[1]} is not a valid entry for LL-lat (valid range is -90 to 90)")
            if bbox[3] < -90 or bbox[3] > 90:
                sys.exit(f"{bbox[3]} is not a valid entry for UR-lat (valid range is -90 to 90)")
            
            # Shapely automatically flips coords based on min/max x, y
            bbox_shape = box(bbox[0],bbox[1],bbox[2],bbox[3]) 
            if  bbox_shape.is_valid:
                bounding_box = [b for b in bbox_shape.bounds]
                bbox_string = ''
                for b in bounding_box: bbox_string += f"{b},"
                bbox_string = bbox_string[:-1]
            else:
                sys.exit(f"The GeoJSON/shapefile: {ROI} is not valid.")     

# OUTPUT DIRECTORY ------------------------------------------------------------
# Set working directory from user-defined arg
if args.dir is not None:
    outDir = os.path.normpath(args.dir.strip("'").strip('"')) + os.sep  
else: 
    outDir = os.getcwd() + os.sep     # Defaults to the current directory 

# Verify that the directory either exists or can be created and accessed
try:
    if not os.path.exists(outDir): os.makedirs(outDir)
    os.chdir(outDir)
except:
    sys.exit(f'{args.dir} is not a valid directory.')

# Set log directory from user-defined arg
    # Create 'log' Dir. if don't exist
    # loglog = 
    # if not os.path.exists(path_out):
    #     os.makedirs(path_out)

# DATES -----------------------------------------------------------------------
start_date = args.start.strip("'").strip('"')  # Assign start date to variable 
end_date = args.end.strip("'").strip('"')      # Assign end date to variable

# Validate the format of the dates submitted
def date_validate(date):
    try:
        dated = dt.datetime.strptime(date, '%m/%d/%Y')
    except:
        sys.exit(f"The date: {date} is not valid. The valid format is mm/dd/yyyy (e.g. 10/20/2020)")
    return dated

start, end = date_validate(start_date),  date_validate(end_date)

# Verify that start date is either the same day or before end date
if start > end:
    sys.exit(f"The Start Date requested: {start} is after the End Date Requested: {end}.")
else:      
    # Change the date format to match CMR-STAC requirements
    dates = f'{start.year}-{start.month}-{start.day}T00:00:00Z/{end.year}-{end.month}-{end.day}T23:59:59Z'                  

# PRODUCTS --------------------------------------------------------------------
prod = args.prod

# Create dictionary of shortnames for HLS products
shortname = {'HLSS30': 'HLSS30.v2.0', 'HLSL30': 'HLSL30.v2.0'}   

# Create a dictionary with product name and shortname
if prod == 'both':
    prods = shortname
else:
    prods = {prod: shortname[prod]}

# BANDS/LAYERS ----------------------------------------------------------------
# Strip spacing, quotes, make all upper case and create a list
bands = args.bands.strip(' ').strip("'").strip('"').upper() 
band_list = bands.split(',')

# Create a LUT dict including the HLS product bands mapped to names
lut = {'HLSS30': {'COASTAL-AEROSOL':'B01', 'BLUE':'B02', 'GREEN':'B03', 'RED':'B04', 'RED-EDGE1':'B05', 'RED-EDGE2':'B06', 'RED-EDGE3':'B07', 'NIR-Broad':'B08', 'NIR1':'B8A', 'WATER-VAPOR':'B09', 'CIRRUS':'B10', 'SWIR1':'B11', 'SWIR2':'B12', 'FMASK':'Fmask'},
       'HLSL30': {'COASTAL-AEROSOL':'B01', 'BLUE':'B02', 'GREEN':'B03', 'RED':'B04', 'NIR1':'B05', 'SWIR1':'B06','SWIR2':'B07', 'CIRRUS':'B09', 'TIR1':'B10', 'TIR2':'B11', 'FMASK':'Fmask'}}

# List of all available/acceptable band names
all_bands = ['ALL', 'COASTAL-AEROSOL', 'BLUE', 'GREEN', 'RED', 'RED-EDGE1', 'RED-EDGE2', 'RED-EDGE3', 'NIR1', 'SWIR1', 'SWIR2', 'CIRRUS', 'TIR1', 'TIR2', 'WATER-VAPOR', 'FMASK']

# Validate that bands are named correctly
for b in band_list:
    if b not in all_bands:
        sys.exit(f"Band: {b} is not a valid input option. Valid inputs are ALL, COASTAL-AEROSOL, BLUE, GREEN, RED, RED-EDGE1, RED-EDGE2, RED-EDGE3, NIR1, SWIR1, SWIR2, CIRRUS, TIR1, TIR2, WATER-VAPOR, FMASK. To request multiple layers, provide them in comma separated format with no spaces. Unsure of the names for your bands?--check out the README which contains a table of all bands and band names.")

# Set up a dictionary of band names and numbers by product
band_dict = {}
for p in prods:
    band_dict[p] = {}
    for b in band_list:
        if b == 'ALL':
            band_dict[p] = lut[p]
        else:
            try:
                band_dict[p][b] = lut[p][b]
            except:
                print(f"Product {p} does not contain band {b}")

# URLs FILE LIST --------------------------------------------------------------
fileList = f"{outDir}HLS_url_links.txt"

# Checking for HLS_url_links.txt file, create it if doesn't exist.
if not os.path.isfile(fileList):
    with open(fileList, "w") as urlwrite:
        pass

# URLs DOWNLOADED (PROVISIONAL) -----------------------------------------------
# Reading file with urls pointing to data previously dowloaded
with open(fileList, 'r') as urlread:
    curr = urlread.read()
    current = curr.split("\n")

    # inserir opcao para caso o arquivo seja vazio!!!!


################################# SEARCH DATA #################################
os.chdir(sys.path[0])  # Switch back to the script directory to execute

# SEARCH FOR EVERY DATA AVAILABLE ---------------------------------------------
if args.all:
    # Call hls_url_search.py using inputs provided
    from hls_url_search3 import get_cmr_pages_urls
    from hls_url_search3 import get_url
    # Call download_image function to use ulr list from hls_url_search.py
    # from hls_download_saving_img import download_main
    
    # How to declare collection in a more explict way, like 'HLSS30.v2.0', 'HLSL30': 'HLSL30.v2.0'????????
    collections = ['C2021957657-LPCLOUD', 'C2021957295-LPCLOUD']

    # Query CMR-STAC, parallelizing process
    # Getting CMR URLs pages
    cmr_pg = get_cmr_pages_urls(collections, dates)
    # List url hls data - parallel approach
    urls = asyncio.run(get_url(cmr_pg, current))

    t1 = time.perf_counter()
    # THREADS APPROACH --------------------------------------------------------
    from hls_download_saving_img3 import download_image
    from hls_download_saving_img3 import logupdate
    #Creating
    log_url = []

    # Download hls data using download_image function - concurrent approach
    with concurrent.futures.ThreadPoolExecutor() as executor:
        for url in urls:
            executor.submit(download_image, url, outDir)
            log_url.append(url)
    # Calling function to update log file
    logupdate(fileList, log_url)

    # -------------------------------------------------------------------------
    # asyncio.run(download_main(urls, args.dir, fileList))



    t2 = time.perf_counter()

    print(f'Finished in {t2-t1} seconds')
'''
# SEARCH FOR DATA IN REGION OF INTEREST (ROI) ---------------------------------
if args.area:
    # Call HLS_Su.py using inputs provided
    from HLS_Su import hls_subset
    # Query CMR-STAC
    dl = hls_subset(bbox_string, outDir, dates, prods, band_dict, cc)  

# SEARCH FOR TILE LIST DATA ---------------------------------------------------
if args.tile:
    flist = args.path
    df_tiles = pd.read_table(flist, names=['TILE'])

#################### PROCESS AND EXPORT REFORMATTED ###########################
# If user decides to continue downloading the intersecting files:
if dl[0].lower() == 'y': 
    os.chdir(sys.path[0])  # Switch back to the script directory to execute
    
    # Call HLS_PER.py using inputs provided and output text file from HLS_Su.py
    from HLS_PER import hls_process
    hls_process(outDir, ROI, qf, scale, of, fileList)  # Access Data, Scale/QF, Export

#################### PROCESS AND EXPORT REFORMATTED (2) #######################
# If any of the downloads failed, retry processing one more time
fileList = f"{outDir}HLS_SuPER_links_failed.txt"

if os.path.exists(fileList):
    os.chdir(sys.path[0])  # Switch back to the script directory to execute
   
    # Call HLS_PER.py using inputs provided and output text file from HLS_Su.py
    from HLS_PER import hls_process

    hls_process(outDir, ROI, qf, scale, of, fileList)  # Access Data, Scale/QF, Export

###############################################################################
# Delete the failed downloads if exist (the ones that ended up DLing successfully)
'''