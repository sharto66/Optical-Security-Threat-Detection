import json
import os
import time

start = time.time()
with open('getGunDetectResults.py') as f:
    code = compile(f.read(), 'getGunDetectResults.py', 'exec')
    exec(code)
end = time.time()

#start = time.time()
#Optical Security Threat Detection application ran here
#end = time.time()

print('\nRetrieved GunDetect results in ' + str(float("{0:.2f}".format(end - start))) + ' seconds')

file1 = open('opticalSecDetectResults.json', 'r')
file2 = open('gundetectResults.json', 'r')

ostdResults = json.load(file1)
gundetectResults = json.load(file2)

ostdTrue = 0
gdTrue = 0

for i in ostdResults:
	if ostdResults[i] == True:
		ostdTrue += 1

for i in gundetectResults:
	if gundetectResults[i] == True:
		gdTrue += 1

ostdAccuracy = float("{0:.2f}".format((ostdTrue / len(ostdResults)) * 100))
gdAccuracy = float("{0:.2f}".format((gdTrue / len(gundetectResults)) * 100))

print('\nAccuracy of Optical Security Threat Detection: ' + str(ostdAccuracy) + '%')
print('Accuracy of GunDetect: ' + str(gdAccuracy) + '%')