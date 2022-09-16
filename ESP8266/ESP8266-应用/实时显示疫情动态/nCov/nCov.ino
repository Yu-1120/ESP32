#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include "font.h"
#define OLED_address  0x3c                           // OLED I2C bus address
#ifndef STASSID
#define STASSID "MI"//----------WiFi名称和密码
#define STAPSK  "asdfghjkl"
#endif
//============WiFi名称和密码==================
const char* ssid     = STASSID;
const char* password = STAPSK;
//==========目标服务器网址和端口================
const char* host = "www.bigiot.net";
const uint16_t port = 8282 ;
//============设备的ID和KEY===================
String DEVICEID = "设备id";  
String APIKEY = "设备key";
//=================变量======================
int rdat[8];
bool RX_Flag=false;
String inputString="";
unsigned long ScrollTime = 0;
unsigned long lastCheckStatusTime = 0;         //记录上次报到时间
const unsigned long postingInterval = 40000;   // 每隔40秒向服务器报到一次
unsigned long checkoutTime = 0;                //登出时间
unsigned long Dat_up_Time = 0;
WiFiClient client;                             //使用WiFiClient类创建TCP连接

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println();
  Serial.println();
  Serial.print("即将连接WiFi：");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) //等待连接
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi连接成功");
  Serial.println("IP : ");
  Serial.println(WiFi.localIP());

  while(!client.connect(host, port)) {
    Serial.println("连接服务器失败");
    delay(5000);
    return;
  }
  checkIn();//发送设备上线命令
  Wire.begin(0,2);                                   // I2C for ESP-01: (SDA,SCL) 
  
  init_OLED();
  reset_display();
  displayOff();
  clear_display();
  displayOn();

  sendStr16X16(2,2,1);//确诊
  sendStr16X16(3,2,3);
  sendStr8X16(10,2,5);
  //sendNum8X16(34655,2,6);
  sendStr16X16(4,4,1);//死亡
  sendStr16X16(5,4,3);
  sendStr8X16(10,4,5);
  //sendNum8X16(3246,4,6);
  sendStr16X16(6,6,1);//治愈
  sendStr16X16(7,6,3);
  sendStr8X16(10,6,5);
  //sendNum8X16(6542,6,6);
}
void loop() {
  while (client.available()) 
  {
    char ch = static_cast<char>(client.read());
   //Serial.print(ch);
   inputString += ch;
   if(ch == '\n')//一帧JSON数据接收完成
    RX_Flag=true;
  }
  if(RX_Flag)//处理一帧JSON数据
  {
    RX_Flag=false;
    //检测json数据是否完整
    int i = inputString.indexOf("[");
    int j = inputString.lastIndexOf("]");
    if (i != -1 && j != -1) 
    {
      Serial.print(inputString);
      int dd = inputString.indexOf("[");
      rdat[0] = (inputString.substring(dd+2, dd+3)).toInt();
      rdat[1] = (inputString.substring(dd+6, dd+8)).toInt();
      rdat[2] = (inputString.substring(dd+11, dd+13)).toInt();
      rdat[3] = (inputString.substring(dd+16, dd+18)).toInt();
      rdat[4] = (inputString.substring(dd+21, dd+26)).toInt();
      rdat[5] = (inputString.substring(dd+29, dd+32)).toInt();
      rdat[6] = (inputString.substring(dd+35, dd+40)).toInt();
      sendNum8X16(rdat[4],2,6);
      sendNum8X16(rdat[5],4,6);
      sendNum8X16(rdat[6],6,6);
      for(int k=0;k<8;k++)
        Serial.println(rdat[k]);
      inputString="";
    }
    //Serial.print(inputString);
  }
  //每一定时间查询一次设备在线状态，同时替代心跳
  if (millis() - lastCheckStatusTime > postingInterval) {
    checkStatus();
  }
  //自动重连功能：断开50ms后自动连接
  if ( checkoutTime != 0 && millis() - checkoutTime > 50 ) {
    checkIn();
    checkoutTime = 0;
  }
  if(millis() - ScrollTime >500)
  {
      ScrollTime = millis() ;
      display_scroll(rdat[0],rdat[1],rdat[2],rdat[3]);//OLED滚动显示
  }
  

}
/***********************************************贝壳函数*******************************************************/
//设备登录
//{"M":"checkin","ID":"xx1","K":"xx2"}\n
void checkIn() {
  //client.println("{\"M\":\"checkin\",\"ID\":\"15235\",\"K\":\"d880a176e\"}");
  client.print("{\"M\":\"checkin\",\"ID\":\"");
  client.print(DEVICEID);
  client.print("\",\"K\":\"");
  client.print(APIKEY);
  client.println("\"}");
}
//发送say指令，用于设备与用户、设备与设备间通讯
//{"M":"say","ID":"xx1","C":"xx2","SIGN":"xx3"}\n
void say(String ID, String c) {
  client.print("{\"M\":\"say\",\"ID\":\"");
  client.print(ID);
  client.print("\",\"C\":\"");
  client.print(c);
  client.println("\"}");
}
//上传实时数据========设备ID====数据接口ID：val============//
//{"M":"update","ID":"xx1","V":{"id1":"value1",...}}\n
void up_date(String ID, String ID1, int val) {
  client.print("{\"M\":\"update\",\"ID\":\"");
  client.print(ID);
  client.print("\",\"V\":{\"");
  client.print(ID1);
  client.print("\":\"");
  client.print(val);
  client.println("\"}}");
}
//强制设备下线，用消除设备掉线延时
//{"M":"checkout","ID":"xx1","K":"xx2"}\n
void checkOut() {
  client.print("{\"M\":\"checkout\",\"ID\":\"");
  client.print(DEVICEID);
  client.print("\",\"K\":\"");
  client.print(APIKEY);
  client.println("\"}");
}
//查询设备在线状态
//{"M":"status"}\n
void checkStatus() {
  client.println("{\"M\":\"status\"}");
  lastCheckStatusTime = millis();
}

/**************************************************OLED显示函数**********************************************************/
/*void OLED_Scroll()
{
    if(millis() - ScrollTime >= 400)
    {
        ScrollTime = millis();
        display_scroll();
    }
}*/
void display_scroll(int m,int d,int h,int f)
{
    static int x=14;
    sendStr16X16(10,0,x);//全国新型冠状病毒疫情实时数据
    sendStr16X16(11,0,x+2);
    sendStr16X16(12,0,x+4);
    sendStr16X16(13,0,x+6);
    sendStr16X16(14,0,x+8);
    sendStr16X16(15,0,x+10);
    sendStr16X16(16,0,x+12);
    sendStr16X16(17,0,x+14);
    
    sendStr16X16(18,0,x+16);
    sendStr16X16(19,0,x+18);
    sendStr16X16(20,0,x+20);
    sendStr16X16(21,0,x+22);
    sendStr16X16(22,0,x+24);
    sendStr16X16(23,0,x+26);
    sendStr16X16(24,0,x+28); //，
    sendStr16X16(0,0,x+30);//截至
    
    sendStr16X16(1,0,x+32);
    sendNum8X16(2020,0,x+34);//年
    sendStr8X16(11,0,x+38);//  -
    sendNum8X16(m,0,x+39);//月
    sendStr8X16(11,0,x+41);//  -
    sendNum8X16(d,0,x+42);//日
    sendStr8X16(12,0,x+44);//空格
    
    sendNum8X16(h,0,x+45);//时
    sendStr8X16(10,0,x+47);//  ：
    sendNum8X16(f,0,x+48);//分
    sendStr8X16(12,0,x+50);//空格
    sendStr16X16(22,0,x+51);//数据统计
    sendStr16X16(23,0,x+53);
    sendStr16X16(26,0,x+55);
    sendStr16X16(27,0,x+57);
    sendStr16X16(28,0,x+59);
    sendStr8X16(12,0,x+61);//空格
    /*
    sendStr16X16(24,0,x+38);
    sendStr16X16(24,0,x+40);
    sendStr16X16(24,0,x+42);*/
    x--;
    if(x < -62)x = 14;
}

// Resets display depending on the actual mode.
static void reset_display(void)
{
  displayOff();
  clear_display();
  displayOn();
}
// Turns display on.
void displayOn(void)
{
  sendcommand(0xaf);        //display on
}
// Turns display off.
void displayOff(void)
{
  sendcommand(0xae);    //display off
}
// Clears the display by sendind 0 to all the screen map.
static void clear_display(void)
{
  unsigned char i,k;
  for(k=0;k<8;k++)
  { 
    setXY(k,0);    
    {
      for(i=0;i<128;i++)     //clear all COL
      {
        SendChar(0);         //clear all COL
        //delay(10);
      }
    }
  }
}
// Actually this sends a byte, not a char to draw in the display. 
// Display's chars uses 8 byte font the small ones and 96 bytes
// for the big number font.
static void SendChar(unsigned char data) 
{
  //if (interrupt && !doing_menu) return;   // Stop printing only if interrupt is call but not in button functions
  Wire.beginTransmission(OLED_address); // begin transmitting
  Wire.write(0x40);//data mode
  Wire.write(data);
  Wire.endTransmission();    // stop transmitting
}
static void sendStr16X16(unsigned char data,int x,int y)
{    
    setXY(x,y);
    for(int i=0;i<16;i++)
    {   
          if(y<0 or y>15)break;
          SendChar(font_16X16[32*data+i]);
    }
    setXY(x+1,y);
    for(int i=0;i<16;i++)
    {
          if(y<0 or y>15)break;
          SendChar(font_16X16[32*data+16+i]);
    }

}
static void sendStr8X16(unsigned char data,int x,int y)
{
     setXY(x,y);
    for(int i=0;i<8;i++)
    {
       if(y<0 or y>15)break;
       SendChar(font_8X16[16*data+i]);
    }
    setXY(x+1,y);
    for(int i=0;i<8;i++)
    {
        if(y<0 or y>15)break;
       SendChar(font_8X16[16*data+8+i]);
    } 
}
static void sendNum8X16(long num,int x,int y)
{
    long dat=num,dat_num[10];
    int count=0;
    while(num!=0)
    {
        num/=10;
        count++;  
    }
    switch(count)
    {
        case 1:dat_num[0] = 0;
               dat_num[1] = dat;break;
        case 2:dat_num[0] = dat/10;
               dat_num[1] = dat%10;break;
        case 3:dat_num[0] = dat/100;
               dat_num[1] = dat/10%10;
               dat_num[2] = dat%10;break;
        case 4:dat_num[0] = dat/1000;
               dat_num[1] = dat/100%10;
               dat_num[2] = dat/10%10;
               dat_num[3] = dat%10;break;
        case 5:dat_num[0] = dat/10000;
               dat_num[1] = dat/1000%10;
               dat_num[2] = dat/100%10;
               dat_num[3] = dat/10%10;
               dat_num[4] = dat%10;break;
        case 6:dat_num[0] = dat/100000;
               dat_num[1] = dat/10000%10;
               dat_num[2] = dat/1000%10;
               dat_num[3] = dat/100%10;
               dat_num[4] = dat/10%10;
               dat_num[5] = dat%10;break;
    }
    if(count == 1)
    {
        for(int i=0;i<2;i++)
        {
            sendStr8X16(dat_num[i],x,y+i);
        }
    }
    else
    {
        for(int i=0;i<count;i++)
        {
            sendStr8X16(dat_num[i],x,y+i);
        }
    }
}
// Prints a display char (not just a byte) in coordinates X Y,
// being multiples of 8. This means we have 16 COLS (0-15) 
// and 8 ROWS (0-7).
static void sendCharXY(unsigned char data, int X, int Y)
{
  setXY(X, Y);
  Wire.beginTransmission(OLED_address); // begin transmitting
  Wire.write(0x40);//data mode
  
  for(int i=0;i<8;i++)
    Wire.write(pgm_read_byte(myFont[data-0x20]+i));
    
  Wire.endTransmission();    // stop transmitting
}
// Used to send commands to the display.
static void sendcommand(unsigned char com)
{
  Wire.beginTransmission(OLED_address);     //begin transmitting
  Wire.write(0x80);                          //command mode
  Wire.write(com);
  Wire.endTransmission();                    // stop transmitting
}
// Set the cursor position in a 16 COL * 8 ROW map.
static void setXY(unsigned char row,unsigned char col)
{
  sendcommand(0xb0+row);                //set page address
  sendcommand(0x00+(8*col&0x0f));       //set low col address
  sendcommand(0x10+((8*col>>4)&0x0f));  //set high col address
}
// Prints a string regardless the cursor position.
static void sendStr(unsigned char *string)
{
  unsigned char i=0;
  while(*string)
  {
    for(i=0;i<8;i++)
    {
      SendChar(pgm_read_byte(myFont[*string-0x20]+i));
    }
    *string++;
  }
}
// Prints a string in coordinates X Y, being multiples of 8.
// This means we have 16 COLS (0-15) and 8 ROWS (0-7).
static void sendStrXY( char *string, int X, int Y)
{
  setXY(X,Y);
  unsigned char i=0;
  while(*string)
  {
    for(i=0;i<8;i++)
    {
      SendChar(pgm_read_byte(myFont[*string-0x20]+i));
    }
    *string++;
  }
}
// Inits oled and draws logo at startup
static void init_OLED(void)
{
   sendcommand(0xae);   //display off
  sendcommand(0xa6);            //Set Normal Display (default)
    // Adafruit Init sequence for 128x64 OLED module
    sendcommand(0xAE);             //DISPLAYOFF
    sendcommand(0xD5);            //SETDISPLAYCLOCKDIV
    sendcommand(0x80);            // the suggested ratio 0x80
    sendcommand(0xA8);            //SSD1306_SETMULTIPLEX
    sendcommand(0x3F);
    sendcommand(0xD3);            //SETDISPLAYOFFSET
    sendcommand(0x0);             //no offset
    sendcommand(0x40 | 0x0);      //SETSTARTLINE
    sendcommand(0x8D);            //CHARGEPUMP
    sendcommand(0x14);
    sendcommand(0x20);             //MEMORYMODE
    sendcommand(0x00);             //0x0 act like ks0108
    
    //sendcommand(0xA0 | 0x1);      //SEGREMAP   //Rotate screen 180 deg
    sendcommand(0xA0);
    
    //sendcommand(0xC8);            //COMSCANDEC  Rotate screen 180 Deg
    sendcommand(0xC0);
    
    sendcommand(0xDA);            //0xDA
    sendcommand(0x12);           //COMSCANDEC
    sendcommand(0x81);           //SETCONTRAS
    sendcommand(0xCF);           //
    sendcommand(0xd9);          //SETPRECHARGE 
    sendcommand(0xF1); 
    sendcommand(0xDB);        //SETVCOMDETECT                
    sendcommand(0x40);
    sendcommand(0xA4);        //DISPLAYALLON_RESUME        
    sendcommand(0xA6);        //NORMALDISPLAY             

  clear_display();
  sendcommand(0x2e);            // stop scroll
  //----------------------------REVERSE comments----------------------------//
    sendcommand(0xa0);    //seg re-map 0->127(default)
    sendcommand(0xa1);    //seg re-map 127->0
    sendcommand(0xc8);
    delay(1000);
  //----------------------------REVERSE comments----------------------------//
  // sendcommand(0xa7);  //Set Inverse Display  
  // sendcommand(0xae);   //display off
  sendcommand(0x20);            //Set Memory Addressing Mode
  sendcommand(0x00);            //Set Memory Addressing Mode ab Horizontal addressing mode
  //  sendcommand(0x02);         // Set Memory Addressing Mode ab Page addressing mode(RESET)  

}
