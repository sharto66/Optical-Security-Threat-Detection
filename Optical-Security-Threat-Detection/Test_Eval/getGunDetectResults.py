import requests
import json
import glob
import sys

url = 'http://169.55.143.119:8999/_classify_upload'

headers = {
		   'User-Agent': 'Mozilla/5.0 (Windows NT 6.3; WOW64; rv:44.0) Gecko/20100101 Firefox/44.0',
		   'Host': '169.55.143.119:8999',
		   'Accept': 'application/json, text/javascript, */*; q=0.01',
		   'Accept-Encoding': 'gzip, deflate',
		   'Accept-Language': 'en-US,en;q=0.5',
		   'Referer': 'http://169.55.143.119:8999/?user_id=0&user_name=',
		   'DNT': '1',
		   'X-Requested-With': 'XMLHttpRequest',
		   'Connection': 'keep-alive'
}

detectedTrue = 0
list = {}

dirName = '../images/Threat/'

if sys.argv[1] == "-Threat":
	dirName = '../images/Threat/'
elif sys.argv[1] == "-Non_Threat":
	dirName = '../images/Non_Threat/'

numImages = len(glob.glob1(dirName, 'image*.jpg'))

for i in range(1, numImages):
	fileName = 'image%d.jpg' %(i)
	image = {'file_data': (fileName, open(dirName + fileName, 'rb'), 'image/jpeg')}
	r = requests.post(url, files=image, headers=headers)
	jsonData = json.loads(r.text)
	if jsonData.get('gun_detected') == True:
		detectedTrue += 1
		list[fileName] = True
	else:
		list[fileName] = False

file1 = open('gundetectResults.txt', 'w')
file2 = open('gundetectResults.json', 'w')

for i in list:
	print(i + ' = ' + str(list[i]), file=file1)
summary = 'Accuracy of GunDetect: ' + str(float("{0:.2f}".format((detectedTrue / numImages) * 100)))
print(summary, file=file1)

json.dump(list, file2)


