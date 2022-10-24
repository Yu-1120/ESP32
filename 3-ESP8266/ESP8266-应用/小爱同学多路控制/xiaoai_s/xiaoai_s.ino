#define BLINKER_PRINT Serial
#define BLINKER_MIOT_LIGHT
#define BLINKER_WIFI

#include <Blinker.h>

//共阳LED  低电平点亮
#define LED0 D0
#define LED1 D7
#define LED2 D6
#define LED3 D5

//秘钥，WiFi名称，WiFi密码
char auth[] = "密钥";
char ssid[] = "WiFi名称";
char pswd[] = "WiFi密码";

// 新建组件对象
BlinkerButton Button0("k0");
BlinkerButton Button1("k1");
BlinkerButton Button2("k2");
BlinkerButton Button3("k3");

bool LED0_Flag = false;
bool LED1_Flag = false;
bool LED2_Flag = false;
bool LED3_Flag = false;

// 按下按键即会执行该函数
void button0_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    if(state == "on")
        {
            Button0.print("on");
            digitalWrite(LED0, LOW);
        }
    else if(state == "off")
        {
            Button0.print("off");
            digitalWrite(LED0, HIGH);
        }
}
void button1_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    if(state == "on")
      {
          Button1.print("on");
          digitalWrite(LED1, LOW);
      }
    else if(state == "off")
      {
          Button1.print("off");
          digitalWrite(LED1, HIGH);
      }
}
void button2_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    if(state == "on")
      {
          Button2.print("on");
          digitalWrite(LED2, LOW);
      }
    else if(state == "off")
      {
          Button2.print("off");
          digitalWrite(LED2, HIGH);
      }
}
void button3_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    if(state == "on")
      {
          Button3.print("on");
          digitalWrite(LED3, LOW);
      }
    else if(state == "off")
      {
          Button3.print("off");
          digitalWrite(LED3, HIGH);
      }
}

void miotMode(uint8_t mode)
{
    BLINKER_LOG("need set mode: ", mode);

    if (mode == BLINKER_CMD_MIOT_DAY) {
        LED0_Flag = !LED0_Flag;
        if(LED0_Flag)
        {
            Button0.print("on");
            digitalWrite(LED0, LOW);
        }
        else
        {
            Button0.print("off");
            digitalWrite(LED0, HIGH);
        }
    }
    else if (mode == BLINKER_CMD_MIOT_NIGHT) {
        LED1_Flag = !LED1_Flag;
        if(LED1_Flag)
        {
            Button1.print("on");
            digitalWrite(LED1, LOW);
        }
        else
        {
            Button1.print("off");
            digitalWrite(LED1, HIGH);
        }
    }
    else if (mode == BLINKER_CMD_MIOT_COLOR) {
        LED2_Flag = !LED2_Flag;
        if(LED2_Flag)
        {
            Button2.print("on");
            digitalWrite(LED2, LOW);
        }
        else
        {
            Button2.print("off");
            digitalWrite(LED2, HIGH);
        }
    }
    else if (mode == BLINKER_CMD_MIOT_WARMTH) {
        LED3_Flag = !LED3_Flag;
        if(LED3_Flag)
        {
            Button3.print("on");
            digitalWrite(LED3, LOW);
        }
        else
        {
            Button3.print("off");
            digitalWrite(LED3, HIGH);
        }
    }
    else if (mode == BLINKER_CMD_MIOT_TV) {
        // Your mode function
    }
    else if (mode == BLINKER_CMD_MIOT_READING) {
        // Your mode function
    }
    else if (mode == BLINKER_CMD_MIOT_COMPUTER) {
        // Your mode function
    }

   // wsMode = mode;

    BlinkerMIOT.mode(mode);
    BlinkerMIOT.print();
}

void setup() {
    // 初始化串口
    Serial.begin(115200);

    #if defined(BLINKER_PRINT)
        BLINKER_DEBUG.stream(BLINKER_PRINT);
    #endif

    // 初始化有LED的IO
    pinMode(D0, OUTPUT);
    pinMode(D7, OUTPUT);
    pinMode(D6, OUTPUT);
    pinMode(D5, OUTPUT);
    digitalWrite(LED0, HIGH);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    // 初始化blinker
    Blinker.begin(auth, ssid, pswd);

    BlinkerMIOT.attachMode(miotMode);
    Button0.attach(button0_callback);//注册回调函数
    Button1.attach(button1_callback);
    Button2.attach(button2_callback);
    Button3.attach(button3_callback);
}

void loop() {
    Blinker.run();
}
