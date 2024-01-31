from joblib import Parallel, delayed
import os, sys, math, csv, subprocess, shutil, glob
from sys import argv
import numpy as np
import numpy.ma as ma
import csv
import pandas

start = int(sys.argv[1])
end = int(sys.argv[2])

for i in range(start,end):
    strcmd = "python /gpfs/glad3/HLSDIST/System/report/generateReport.py " + str(i)
    print("Processing..."+str(i))
    subprocess.call(strcmd.replace('\n', ''), shell=True)	   