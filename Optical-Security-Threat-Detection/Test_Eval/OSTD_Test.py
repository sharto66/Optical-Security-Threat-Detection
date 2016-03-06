import json

file1 = open('opticalSecDetectResults.json', 'r')
file2 = open('gundetectResults.json', 'r')

ostdResults = json.load(file1)
gundetectResults = json.load(file2)

ostdTrue = 0
gdTrue = 0

for i in ostdResults:
	if ostdResults[i] == 'True':
		ostdTrue += 1

for i in gdTrue:
	if gundetectResults[i] == 'True':
		gdTrue += 1

ostdAccuracy = ostdTrue / len(ostdResults)
gdAccuracy = gdTrue / len(gundetectResults)

print('Accuracy of Optical Security Threat Detection: ' + str(ostsAccuracy))
print('Accuracy of GunDetect: ' + str(gdAccuracy))