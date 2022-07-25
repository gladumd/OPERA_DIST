######################### IMPORT PACKAGES #####################################
import os
from netrc import netrc
from subprocess import Popen
from subprocess import DEVNULL, STDOUT
from getpass import getpass
from sys import platform

######################
#Create symbolic link to .netrc file on other gladapps (run on each): ln -s /gpfs/glad1/Amy/.netrc /home/hudsona/.netrc

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

################################### Main ######################################
#                                                                             #
#                                                                             #
###############################################################################
if __name__=='__main__':
  earthdata_authentication()
