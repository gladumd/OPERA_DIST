""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
To capture current python set up run: pip freeze > requirements.txt
To create a virtual environment run (make sure dist-py-env is in the same directory as the scripts): python -m venv dist-py-env 
To activate python env run: source dist-py-env/bin/activate
Once activated can install required packages by running: pip install -r requirements.txt
If install new libraries create new requirements file: pip freeze > requirements.txt

CMRsearchdownload.py 
  -modules to load: python/3.7/anaconda, sqlite; activate python env, source dist-py-env/bin/activate
  -input: none
  -prints status (capture all in processLOG.txt, capture errors in errorLOG.txt)
  -output files: downloaded files, wgetlog.txt (captures successes), wgeterrors.txt (captures errors)
  -database statusFlag codes: initialize row for HLS_ID, set to 1 for potential requested download, 2 for successful download, 102 for failed download
  1. search
  2. download
  3. check downloads
02_scene_manager.pl 
  -input granule list (one per line) (all files with statusFlag == 3), mode: "VEG_IND" or "ALL"
  -prints status (capture all in processLOG.txt, capture errors in errorLOG.txt)
  -output files: VEG_ANOM and GEN_ANOM images
  -database statusFlag codes: input files = 2, successful only VEG_IND = 3, successful ANOM granules = 4, failed VEG_IND granules = 103, failed ANOM granules = 104
  1. VEG_IND
  2. VEG_ANOM
  3. GEN_ANOM
03_DIST_UPD.pl
  -input granule list (one per line) (all files with statusFlag == 4), mode "RESTART" or "UPDATE"
  -prints status (capture all in processLOG.txt, capture errors in errorLOG.txt)
  -output files: all VEG and GEN ALERT images, metadata file
  -database statusFlag codes: input files = 4, successful granules = 5, failed granules = 105
  1. VEG ALERT time-series layers (must be run sequentially per tile)
  2. GEN ALERT time-series layers (must be run sequentially per tile)
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

https://data.lpdaac.earthdatacloud.nasa.gov/lp-prod-protected/HLSL30.020/HLS.L30.T38RLS.2022184T073503.v2.0/HLS.L30.T38RLS.2022184T073503.v2.0.SZA.tif
https://data.lpdaac.earthdatacloud.nasa.gov/lp-prod-protected/HLSL30.020/HLS.L30.T38RLS.2022184T073503.v2.0/HLS.L30.T38RLS.2022184T073503.v2.0.B01.tif
https://data.lpdaac.earthdatacloud.nasa.gov/lp-prod-protected/HLSL30.020/HLS.L30.T38RLS.2022184T073503.v2.0/HLS.L30.T38RLS.2022184T073503.v2.0.B06.tif
https://data.lpdaac.earthdatacloud.nasa.gov/lp-prod-protected/HLSL30.020/HLS.L30.T38RLS.2022184T073503.v2.0/HLS.L30.T38RLS.2022184T073503.v2.0.B10.tif
https://data.lpdaac.earthdatacloud.nasa.gov/lp-prod-protected/HLSL30.020/HLS.L30.T38RLS.2022184T073503.v2.0/HLS.L30.T38RLS.2022184T073503.v2.0.VAA.tif
https://data.lpdaac.earthdatacloud.nasa.gov/lp-prod-protected/HLSL30.020/HLS.L30.T38RLS.2022184T073503.v2.0/HLS.L30.T38RLS.2022184T073503.v2.0.B07.tif
https://data.lpdaac.earthdatacloud.nasa.gov/lp-prod-protected/HLSL30.020/HLS.L30.T38RLS.2022184T073503.v2.0/HLS.L30.T38RLS.2022184T073503.v2.0.SAA.tif
https://data.lpdaac.earthdatacloud.nasa.gov/lp-prod-protected/HLSL30.020/HLS.L30.T38RLS.2022184T073503.v2.0/HLS.L30.T38RLS.2022184T073503.v2.0.B04.tif
https://data.lpdaac.earthdatacloud.nasa.gov/lp-prod-protected/HLSL30.020/HLS.L30.T38RLS.2022184T073503.v2.0/HLS.L30.T38RLS.2022184T073503.v2.0.VZA.tif
https://data.lpdaac.earthdatacloud.nasa.gov/lp-prod-protected/HLSL30.020/HLS.L30.T38RLS.2022184T073503.v2.0/HLS.L30.T38RLS.2022184T073503.v2.0.B11.tif
https://data.lpdaac.earthdatacloud.nasa.gov/lp-prod-protected/HLSL30.020/HLS.L30.T38RLS.2022184T073503.v2.0/HLS.L30.T38RLS.2022184T073503.v2.0.B03.tif
https://data.lpdaac.earthdatacloud.nasa.gov/lp-prod-protected/HLSL30.020/HLS.L30.T38RLS.2022184T073503.v2.0/HLS.L30.T38RLS.2022184T073503.v2.0.B02.tif
https://data.lpdaac.earthdatacloud.nasa.gov/lp-prod-protected/HLSL30.020/HLS.L30.T38RLS.2022184T073503.v2.0/HLS.L30.T38RLS.2022184T073503.v2.0.Fmask.tif
https://data.lpdaac.earthdatacloud.nasa.gov/lp-prod-protected/HLSL30.020/HLS.L30.T38RLS.2022184T073503.v2.0/HLS.L30.T38RLS.2022184T073503.v2.0.B05.tif
https://data.lpdaac.earthdatacloud.nasa.gov/lp-prod-protected/HLSL30.020/HLS.L30.T38RLS.2022184T073503.v2.0/HLS.L30.T38RLS.2022184T073503.v2.0.B09.tif
