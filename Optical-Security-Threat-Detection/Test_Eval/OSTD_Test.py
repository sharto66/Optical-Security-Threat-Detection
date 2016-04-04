import json
import os
import sys
import time
import subprocess
from multiprocessing import Process

def gunDetectProcess():
	arg = '-Threat'
	if sys.argv[1] == '-Non_Threat':
		arg = '-Non_Threat'
	print('\nGetting results from GunDetect...\n')
	gd_start = time.time()
	with open('getGunDetectResults.py') as f:
		code = compile(f.read(), str('getGunDetectResults.py ' + arg), 'exec')
		exec(code)
	gd_end = time.time()
	gd_time = float("{0:.2f}".format(gd_end - gd_start))
	print('\nRetrieved GunDetect results in ' + str(gd_time) + ' seconds')

def ostdProcess():
	arg = '-Threat'
	if sys.argv[1] == '-Threat':
		arg = '-Threat'
	elif sys.argv[1] == '-Non_Threat':
		arg = '-Non_Threat'
	print('Getting results from Optical Security Threat Detection...\n')
	ostd_start = time.time()
	subprocess.call([r"..\dist\Release\MinGW-Windows\optical-security-threat-detection.exe", arg]
					,stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
	ostd_end = time.time()
	ostd_time = float("{0:.2f}".format(ostd_end - ostd_start))
	print('\nRetrieved Optical Security Threat Detection results in ' + str(ostd_time) + ' seconds')

if __name__=='__main__':
	if sys.argv[1] == '-Threat':
		print('\nAnalysing Threat images:\n')
	elif sys.argv[1] == '-Non_Threat':
		print('\nAnalysing Non-Threat images:\n')
	p1 = Process(target=gunDetectProcess)
	p1.start()
	p2 = Process(target=ostdProcess)
	p2.start()
	p1.join()
	p2.join()

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