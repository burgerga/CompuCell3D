import rrPython
import os
import csv
os.chdir('C:\\RoadRunner\\bin')

function = 'setCapabilities'

try:
    caps = rrPython.setCapabilities('aaa')
    if str(caps) is not False:
        result = 'True'
    else:
        result = 'False'
except:
    result = 'False'


PythonTestResults = open('C:\\RoadRunner\\PythonTestResults.csv','a')
writer = csv.writer(PythonTestResults)
writevar = function + '=' + result
writer.writerow([writevar])
PythonTestResults.close()