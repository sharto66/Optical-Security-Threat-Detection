import requests
import base64

with open("image1.jpg", "rb") as image_file:
    encoded_image = base64.b64encode(image_file.read())

url = "http://169.55.143.119:8999/_classify_upload"
#f = {'image1.jpg': open('image1.jpg', 'rb')}
image = {'file_data': ('image4.jpg', open('image4.jpg', 'rb'), 'image/jpeg')}

headers = {
		   'User-Agent': 'Mozilla/5.0 (Windows NT 6.3; WOW64; rv:44.0) Gecko/20100101 Firefox/44.0',
		   #'Host': '169.55.143.119:8999',
		   'Accept': 'application/json, text/javascript, */*; q=0.01',
		   #'Accept-Encoding': 'gzip, deflate',
		   #'Accept-Language': 'en-US,en;q=0.5',
		   'Referer': 'http://169.55.143.119:8999/?user_id=0&user_name=',
		   #'DNT': '1',
		   #'X-Requested-With': 'XMLHttpRequest',
		   #'Connection': 'keep-alive'
		   'Content-Type': 'multipart/form-data; boundary=--253619342284rf0--',
		   #'Content-Type': 'application/x-www-form-urlencoded; charset=UTF-8'
		   }

r = requests.post(url, files=image, headers=headers)
file1 = open('gundetect.json', 'w')
print(r.text, file=file1)
print(r.text)
print(r.headers)