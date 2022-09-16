#include <ESP8266WiFi.h>
int count=0;
bool WIFI_Status = true;

void smartConfig()
{
  WiFi.mode(WIFI_STA);
  Serial.println("\r\nWait for Smartconfig...");
  WiFi.beginSmartConfig();//等待手机端发出的用户名与密码
  while (1)
  {
    Serial.print(".");
    digitalWrite(LED_BUILTIN, HIGH);  
    delay(1000);                      
    digitalWrite(LED_BUILTIN, LOW);    
    delay(1000);                      
    if (WiFi.smartConfigDone())//退出等待
    {
      Serial.println("SmartConfig Success");
      Serial.printf("SSID:%s\r\n", WiFi.SSID().c_str());
      Serial.printf("PSW:%s\r\n", WiFi.psk().c_str());
      break;
    }
  }
}
void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.println("\r\n正在连接");
  while(WiFi.status()!=WL_CONNECTED)
  {
      if(WIFI_Status)
      {
          Serial.print(".");
          digitalWrite(LED_BUILTIN, HIGH);  
          delay(500);                       
          digitalWrite(LED_BUILTIN, LOW);    
          delay(500);                 
          count++;
          if(count>=5)//5s
          {
              WIFI_Status = false;
              Serial.println("WiFi连接失败，请用手机进行配网"); 
          }
      }
      else
      {
          smartConfig();  //微信智能配网
      }
   }  
   Serial.println("连接成功");  
   Serial.print("IP:");
   Serial.println(WiFi.localIP());
  
}
void loop() {
  
}
