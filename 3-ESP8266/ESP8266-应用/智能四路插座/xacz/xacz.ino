#define BLINKER_MIOT_MULTI_OUTLET    //设置为小爱多个插座的模式#define BLINKER_PRINT Serial
#define BLINKER_PRINT Serial
#define BLINKER_WIFI
#include <Blinker.h>
#define Socket1 D5
#define Socket2 D6
#define Socket3 D7
#define Socket4 D8
char auth[] = "***********";/****秘钥****/
/*char ssid[] = "MI";
char pswd[] = "asdfghjkl";*/
char Port;
int Feedback = 0;
int OnorOff = 0;
long F_time = 0;
int count=0;
bool WIFI_Status = true;


// 新建组件对象
BlinkerButton Button1("k1");     //设置blinkerapp内数据键名
BlinkerButton Button2("k2");
BlinkerButton Button3("k3");
BlinkerButton Button4("k4");


void smartConfig()//配网函数
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
void WIFI_Set()//
{
    //Serial.println("\r\n正在连接");
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
    /* Serial.println("连接成功");  
     Serial.print("IP:");
     Serial.println(WiFi.localIP());*/
}



void Set_Butt(int num) //on反馈
{
    if (num == 1) {
        Button1.print("on");      
    } else if (num == 2) {
        Button2.print("on");
    } else if (num == 3) {
        Button3.print("on");
    } else if (num == 4) {
        Button4.print("on");
    }   
}
void Reset_Butt(int num) //off反馈
{
    if (num == 1) {
        Button1.print("off");      
    } else if (num == 2) {
        Button2.print("off");
    } else if (num == 3) {
        Button3.print("off");
    } else if (num == 4) {
        Button4.print("off");
    }   
}


void miotPowerState(const String & state, uint8_t num)     //小爱控制函数
{
  BLINKER_LOG("need set outlet: ", num, ", power state: ", state);
  if (num == 1) {
    Feedback = 1;
    Port = Socket1;        //指定每一路开关对应在开发板上的通道接口
  } else if (num == 2) {
    Feedback = 2;
    Port = Socket2;
  } else if (num == 3) {
    Feedback = 3;
    Port = Socket3;
  } else if (num == 4) {
    Feedback = 4;
    Port = Socket4;
  }

  if (state == BLINKER_CMD_ON) {
    OnorOff = 1;
    if(num == 0)
    {
        Feedback = 5;
        digitalWrite(Socket1, HIGH);
        digitalWrite(Socket2, HIGH);
        digitalWrite(Socket3, HIGH);
        digitalWrite(Socket4, HIGH);
    }
    else
    {
        digitalWrite(Port, HIGH);
    }

    BlinkerMIOT.powerState("on", num);
    BlinkerMIOT.print();
  }
  else if (state == BLINKER_CMD_OFF) {
    OnorOff = 2;
    if(num == 0)
    {
        Feedback = 5;
        digitalWrite(Socket1, LOW);
        digitalWrite(Socket2, LOW);
        digitalWrite(Socket3, LOW);
        digitalWrite(Socket4, LOW);
    }
    else
    {
        digitalWrite(Port, LOW);
    }

    BlinkerMIOT.powerState("off", num);
    BlinkerMIOT.print();
  }
}


void button1_callback(const String & state)     //点灯app内控制按键触发
{
  BLINKER_LOG("get button state: ", state);
  if (state == "on")
  {
    digitalWrite(Socket1, HIGH);
    Button1.print("on");
  }
  if (state == "off")
  {
    digitalWrite(Socket1, LOW);
    Button1.print("off");
  }
}
void button2_callback(const String & state)     //点灯app内控制按键触发
{
  BLINKER_LOG("get button state: ", state);
  if (state == "on")
  {
    digitalWrite(Socket2, HIGH);
    Button2.print("on");
  }
  if (state == "off")
  {
    digitalWrite(Socket2, LOW);
    Button2.print("off");
  }
}
void button3_callback(const String & state)     //点灯app内控制按键触发
{
  BLINKER_LOG("get button state: ", state);
  if (state == "on")
  {
    digitalWrite(Socket3, HIGH);
    Button3.print("on");
  }
  if (state == "off")
  {
    digitalWrite(Socket3, LOW);
    Button3.print("off");
  }
}
void button4_callback(const String & state)     //点灯app内控制按键触发
{
  BLINKER_LOG("get button state: ", state);
  if (state == "on")
  {
    digitalWrite(Socket4, HIGH);
    Button4.print("on");
  }
  if (state == "off")
  {
    digitalWrite(Socket4, LOW);
    Button4.print("off");
  }
}

void setup() {
  // 初始化串口
  Serial.begin(115200);

#if defined(BLINKER_PRINT)
  BLINKER_DEBUG.stream(BLINKER_PRINT);
#endif

  // 初始化有LED的IO
  pinMode(Socket1, OUTPUT);
  digitalWrite(Socket1, LOW);
  pinMode(Socket2, OUTPUT);
  digitalWrite(Socket2, LOW);
  pinMode(Socket3, OUTPUT);
  digitalWrite(Socket3, LOW);
  pinMode(Socket4, OUTPUT);
  digitalWrite(Socket4, LOW);//初始化输出低电平
  pinMode(LED_BUILTIN, OUTPUT);
  WIFI_Set();
  // 初始化blinker
  Blinker.begin(auth, WiFi.SSID().c_str(), WiFi.psk().c_str());
  Button1.attach(button1_callback);//注册按键回调函数
  Button2.attach(button2_callback);
  Button3.attach(button3_callback);
  Button4.attach(button4_callback);

  BlinkerMIOT.attachPowerState(miotPowerState);
  //    BlinkerMIOT.attachPowerState(miotPowerState);
  digitalWrite(LED_BUILTIN, HIGH);
}
int i=0;
void loop() {
  Blinker.run();
    if(OnorOff == 0)
    {
      
    }
    else if(OnorOff == 1)//如果是ON状态
    {
        delay(1500);
        if(Feedback < 5)//小于5 是单独控制 1-4
        {
            Set_Butt(Feedback);//反馈1-4
            OnorOff = 0;
        }else if(Feedback == 5)//等于5 是打开所有然后1.2s每个的速度反馈所有
        {
            if(millis() - F_time >=1200)
            {
                 F_time = millis();
                 i++;
                 Set_Butt(i);
                 i%=4;
                 if(i == 0) //当所有状态反馈完毕则退出
                 {
                     Feedback = 0;
                     OnorOff = 0;
                 }
            }   
        }
    }
    else if(OnorOff == 2)
    {
        delay(1500);
        if(Feedback < 5)//小于5 是单独控制 1-4
        {
            Reset_Butt(Feedback);//反馈1-4
            OnorOff = 0;
        }else if(Feedback == 5)//等于5 是 关闭 所有然后1.2s每个的速度反馈所有
        {
            if(millis() - F_time >=1200)
            {
                 F_time = millis();
                 i++;
                 Reset_Butt(i);
                 i%=4;
                 if(i == 0) //当所有状态反馈完毕则退出
                 {
                     Feedback = 0;
                     OnorOff = 0;
                 }
            }   
        }
    }
}
