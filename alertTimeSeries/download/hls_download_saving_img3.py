# -*- coding: utf-8 -*- 

"""
===============================================================================
HLS downloading   - Main module                         
Authors:Cole Krehbiel and Mahsa Jami
Date: 12/16/2021

-------------
Adaptaded by André Lima
Date: 02/23/2022
Last Updated:                                             
===============================================================================
"""
######################### IMPORT PACKAGES #####################################
import argparse
import os
import re
import requests
import time
import concurrent.futures
from netrc import netrc
from subprocess import Popen
from subprocess import DEVNULL, STDOUT
from getpass import getpass
from datetime import datetime
import warnings
from sys import platform



def earthdata_authentication():
    #Verify a netrc is set up with Earthdata Login Username and password
    urs = 'urs.earthdata.nasa.gov'    # Earthdata URL to call for authentication
    prompts = ['Enter NASA Earthdata Login Username \n(or create an account at urs.earthdata.nasa.gov): ','Enter NASA Earthdata Login Password: ']

  
    # Determine if netrc file exists, and if it includes NASA Earthdata Login Credentials
    if 'win' in platform:
        nrc = '_netrc'
    else:
        nrc = '.netrc'
    try:
        netrcDir = os.path.expanduser(f"~/{nrc}")
        netrc(netrcDir).authenticators(urs)[0]
        del netrcDir

    # If not, create a netrc file and prompt user for NASA Earthdata Login Username/Password
    except FileNotFoundError:
        print("run")
        homeDir = os.path.expanduser("~")

        # Windows OS won't read the netrc unless this is set
        Popen(f'setx HOME {homeDir}', shell=True, stdout=DEVNULL);

        if nrc == '.netrc':
            Popen(f'touch {homeDir + os.sep}{nrc} | chmod og-rw {homeDir + os.sep}{nrc}', shell=True, stdout=DEVNULL, stderr=STDOUT);

        # Unable to use touch/chmod on Windows OS
        Popen(f'echo machine {urs} >> {homeDir + os.sep}{nrc}', shell=True)
        Popen(f'echo login {getpass(prompt=prompts[0])} >> {homeDir + os.sep}{nrc}', shell=True)
        Popen(f'echo password {getpass(prompt=prompts[1])} >> {homeDir + os.sep}{nrc}', shell=True)
        del homeDir

    # Determine OS and edit netrc file if it exists but is not set up for NASA Earthdata Login
    except TypeError:
        homeDir = os.path.expanduser("~")
        Popen(f'echo machine {urs} >> {homeDir + os.sep}{nrc}', shell=True)
        Popen(f'echo login {getpass(prompt=prompts[0])} >> {homeDir + os.sep}{nrc}', shell=True)
        Popen(f'echo password {getpass(prompt=prompts[1])} >> {homeDir + os.sep}{nrc}', shell=True)
        del homeDir
    del urs, prompts


# Saving URLs downloaded to *.txt file
def logupdate(oldlst, updatelst):
    with open(oldlst, 'a') as txt:
        txt.writelines('\n'.join(updatelst))


def download_image(img_url, basepath):

    # download a url and return the raw data
    # Acrescentar maneira de gerar execoes mais consistentes!!!!
    fcall = requests.get(img_url, stream=True)

    # Extract file name from url
    img_name = img_url.split('/')[6]
    # Extract subdir name from url
    subdir = img_url.split('/')[5]
    # Extract info (sensor, tile, year) from img_name using regex
    slices = re.search(r"\.(\w\d{2})\.T(\d{2})(\w)(\w)(\w).(\d{4})", img_name)
    # Handle path and name
    path_out = basepath+slices.group(1)+'/'+slices.group(6)+'/'+\
              slices.group(2)+'/'+slices.group(3)+'/'+slices.group(4)+'/'+\
              slices.group(5)+'/'+subdir+'/'

    # Path/File output
    img_out = path_out + img_name
    
    # Create target Dir. if don't exist
    if not os.path.isdir(path_out):
        os.makedirs(path_out)

     # Empty list to be fullfill with url downloaded
    # log_url = []

    # if fcall.status_code == 200 and fcall.headers.get('Content-Type') == 'image/tiff':
    if fcall.status_code == 200:
        print(f'downloading {img_url}')
        with open(img_out, 'wb') as fdisk:
            for chunk in fcall.iter_content(1024):
                _ = fdisk.write(chunk)
    elif fcall.status_code == 404:
        print(f'Could not find data at: {img_url}')
    else:
        print(fcall.reason)
    
    fcall.close()
    return img_out


if __name__ == "__main__":

    t1 = time.perf_counter()

    basepath = '/gpfs/glad1/Andre/temp/'
    # URLs to test
    img_urls = ('https://data.lpdaac.earthdatacloud.nasa.gov/lp-prod-protected/HLSS30.020/HLS.S30.T55MDU.2022001T003711.v2.0/HLS.S30.T55MDU.2022001T003711.v2.0.B58.tif',
                 'https://data.lpdaac.earthdatacloud.nasa.gov/lp-prod-protected/HLSS30.020/HLS.S30.T55MDU.2022001T003711.v2.0/HLS.S30.T55MDU.2022001T003711.v2.0.B07.tif',
                 'https://data.lpdaac.earthdatacloud.nasa.gov/lp-prod-protected/HLSS30.020/HLS.S30.T55MDU.2022001T003711.v2.0/HLS.S30.T55MDU.2022001T003711.v2.0.B09.tif')
    
    # Empty list to be fullfill with url downloaded
    log_url = []

    with concurrent.futures.ThreadPoolExecutor() as executor:
        for url in img_urls:
            executor.submit(download_image, url, basepath)
            log_url.append(url)
            # print(url)


    
    t2 = time.perf_counter()
    
    print(f'Finished in {t2-t1} seconds')
