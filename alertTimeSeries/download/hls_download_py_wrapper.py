import sys, os, getopt
import subprocess
from calendar import isleap
import datetime

################################## Functions ##################################
#                                                                             #
#                                                                             #
###############################################################################
def conv_jday (jday):
    fmt = '%Y%j'
    datestd = datetime.datetime.strptime(jday, fmt).date()
    return(datestd)


def hls_download(gethls_py, outdir, dt_ini, dt_end):
    # os.system("echo running " + gethls_py)
    # hls_download_main.py -all -dir /gpfs/glad3/HLS/ -start 01/11/2016 -end 01/31/2016
    os.system("python "+gethls_py+' -all -dir '+ outdir+' -start '+dt_ini+' -end '+dt_end)

    os.system("echo python "+gethls_py+' -all -dir '+ outdir+' -start '+dt_ini+' -end '+dt_end)
    # os.system("echo ./"+gethls_py +' '+hls_lst+' '+dt_ini+' '+dt_end+' '+outfolder)
    # os.system("echo -------------------")
#################################### Inputs ###################################
#                                                                             #
#                                                                             #
############################################################################### 
outdir = '/gpfs/glad3/HLS/'
# getHLS = 'hls_download_main_provisional.py'
getHLS = 'hls_download_main3.py'
print(getHLS)
#Processing year interval data
year_ini = 2016
year_end = 2016
# Leap year number of days
leap_yr = 366
# Non-leap year number of days
nleap_yr = 365

# python hls_download_main.py -all -dir /gpfs/glad3/HLS/ -start 2022-12-31 -end 2022-12-31
# python hls_download_main.py -all -dir /gpfs/glad3/HLS/ -start 03/01/2020 -end 03/31/2020


################################### Main ######################################
#                                                                             #
#                                                                             #
###############################################################################
if __name__=='__main__':
    for year in range(year_ini, (year_end + 1), 1):
        x_isleap = isleap(year)
        if x_isleap == True:
            n_days = leap_yr
        else:
            n_days = nleap_yr
    
        for jday in range(1, (n_days + 1), 1): # jday 273 = october 1 - mudar para 1
            print(str(jday)+'/'+str(year))
            jday_y = str(year)+str(jday)
            stdate = (conv_jday(jday_y))
            stdate = '{:%m/%d/%Y}'.format(stdate)

            # Runing
            hls_download(getHLS, outdir, stdate, stdate)
            # print(getHLS,  outdir, stdate, stdate)