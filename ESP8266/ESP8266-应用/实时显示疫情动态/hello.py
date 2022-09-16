import socket
import time

host="121.42.180.30"
port=8282
SendTime = 0
GetTime = 0
month =''
day=''
hour=''
min=''
qzr=''
swr=''
zyr = ''
s = socket.socket() 

#WiFi连接函数
def do_connect():
  import network
  wlan = network.WLAN(network.STA_IF)
  wlan.active(True)
  if not wlan.isconnected():
    print('connecting to network...')
    wlan.connect('MI', 'asdfghjkl')
    while not wlan.isconnected():
        pass
  print('network config:', wlan.ifconfig())
strd_f = 0
strd = " "   #接收总的数据
#处理接受的数据
def http_dat(dat):
  global strd_f
  global strd
  a=dat.decode('utf8')#bytes按utf8的方式解码成str  
  strsart = a.find('<ul')
  strend = a.find('</u')
  if(strd_f == 1):
    strd += a
  if((strd_f == 0)and(strsart != -1)):
    strd = a
    strd_f = 1   
  if((strd_f == 1)and(strend != -1)):
    strd_f = 0
#向网页发送get请求  
def http_get(url):
  import socket
  global strd
  _, _, host, path = url.split('/', 3)
  addr = socket.getaddrinfo(host, 80)[0][-1]
  s = socket.socket()
  s.connect(addr)
  s.send(bytes('GET /%s HTTP/1.0\r\nHost: %s\r\n\r\n' % (path, host), 'utf8'))
  print('STAT')
  while True:
    data = s.recv(600)
    if data:
        http_dat(data)  
    else:
        break
  #print(strd)
  print('END')
  s.close()  
#数据处理
def get_epidemic(dat):
  global month,day,hour,min,qzr,swr,zyr
  qz = dat.find('#FF5B5C')
  sw = dat.find('#8E939D')
  zy = dat.find('#59C697')
  tm = dat.find('2020-')
  if((qz != -1)and(sw != -1)and(zy != -1)):
    qzr = dat[(dat.find('>',qz))+1 : (dat.find('<',qz))]
    swr = dat[(dat.find('>',sw))+1 : (dat.find('<',sw))]
    zyr = dat[(dat.find('>',zy))+1 : (dat.find('<',zy))]
    month = dat[tm+5:tm+6]
    day = dat[tm+7:tm+9]
    hour = dat[tm+10:tm+12]
    min = dat[tm+13:tm+15]
    #print(month,day,hour,min,qzr,swr,zyr)
do_connect()
#设备登陆函数
def beike_checkin():
  #s = socket.socket()                                   #create socket
  s.connect((host,port))                                #send require for connect
  time.sleep(2)
  s.send('{"M":"checkin","ID":"设备id,"K":"8697e7008"}\n')               #send data
  while True:
    data = s.recv(100)                               #Receive 1024 byte of data from the socket
    if data:                               #if there is no data,close
      print(str(data, 'utf8'), end='')
      break
  print("ok checkin")
  #s.close()
#向设备发送数据函数
def beike_say():
  #s = socket.socket()                                   #create socket
  #s.connect((host,port))                                #send require for connect
  time.sleep(2)
  s.send('{"M":"say","ID":"这里修改为发送设备的id","C":["'+month+'","'+day+'","'+hour+'","'+min+'","'+qzr+'","'+swr+'","'+zyr+'"],"SIGN":"xx3"}\n')               #send data
  '''while True:
    data = s.recv(100)                               #Receive 1024 byte of data from the socket
    if data:                               #if there is no data,close
      print(str(data, 'utf8'), end='')

      break'''
  print("ok say")
  #s.close()
do_connect()
beike_checkin()
http_get('http://m.medsci.cn/wh.asp')
get_epidemic(strd)
#print(month,day,hour,min,qzr,swr,zyr)
while True:
  if((time.time()) - SendTime >= 30):#30s
    print(SendTime)
    print(time.time())
    SendTime = time.time()
    beike_say()
    #time.sleep(30)
  if((time.time()) - GetTime >=300):#300S
    GetTime = time.time()
    http_get('http://m.medsci.cn/wh.asp')
    get_epidemic(strd)
    '''
    data = s.recv(100)                               #Receive 1024 byte of data from the socket
    if data:                               #if there is no data,close
      print(str(data, 'utf8'), end='')
      break'''




