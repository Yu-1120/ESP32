#define BLINKER_PRINT Serial
#define BLINKER_WIFI
#define BLINKER_MIOT_LIGHT
#define RGB_1 "RGBKey"

#include <Blinker.h>
/***************此处要修改******************/
char auth[] = "************";/****秘钥****/
char ssid[] = "MI";         /*WiFi名称***/
char pswd[] = "asdfghjkl"; /***WiFi密码*/
/***************以上要修改**************/
// 新建组件对象
BlinkerButton Button1("key");
BlinkerNumber Number1("num-abc");
BlinkerRGB RGB1(RGB_1);

int counter = 0;
int LED_R=0,LED_G=0,LED_B=0,LED_Bright=80;// RGB和亮度
bool LED_Flag = false;
// 按下按键即会执行该函数
void button1_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    //digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    LED_Flag = !LED_Flag;
    if(LED_Flag) SET_RGB(255,255,255,LED_Bright);
    else SET_RGB(0,0,0,0);
}

// 如果未绑定的组件被触发，则会执行其中内容
void dataRead(const String & data)
{
    BLINKER_LOG("Blinker readString: ", data);
    counter++;
    Number1.print(counter);
}
void SET_RGB(int R,int G,int B,int bright)
{
    R = R*bright/100;
    G = G*bright/100;
    B = B*bright/100;
    
    LED_R = map(R,0,255,0,1024);
    LED_G = map(G,0,255,0,1024);
    LED_B = map(B,0,255,0,1024);
    Serial.printf("R=%d G=%d B=%d bright=%d\n",LED_R,LED_G,LED_B,bright);
    analogWrite(D7,1024-LED_R);  
    analogWrite(D6,1024-LED_G); 
    analogWrite(D5,1024-LED_B); 
}
//APP RGB颜色设置回调
void rgb1_callback(uint8_t r_value, uint8_t g_value, 
                    uint8_t b_value, uint8_t bright_value)
{
    
    //digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    BLINKER_LOG("R value: ", r_value);
    BLINKER_LOG("G value: ", g_value);
    BLINKER_LOG("B value: ", b_value);
    BLINKER_LOG("Rrightness value: ", bright_value);
    LED_Bright = map(bright_value,0,255,0,100);
    SET_RGB(r_value,g_value,b_value,LED_Bright);
}
//小爱电源类回调
void miotPowerState(const String & state)
{
    BLINKER_LOG("need set power state: ", state);

    if (state == BLINKER_CMD_ON) {
        //digitalWrite(LED_BUILTIN, LOW);
        SET_RGB(255,255,255,LED_Bright);        
        BlinkerMIOT.powerState("on");
        BlinkerMIOT.print();
    }
    else if (state == BLINKER_CMD_OFF) {
        //digitalWrite(LED_BUILTIN, HIGH);
        SET_RGB(0,0,0,0);
        BlinkerMIOT.powerState("off");
        BlinkerMIOT.print();
    }
}
//小爱设置颜色回调
void miotColor(int32_t color)
{
    BLINKER_LOG("need set color: ", color);
    int colorR,colorG,colorB;
    colorR = color >> 16 & 0xFF;
    colorG = color >>  8 & 0xFF;
    colorB = color       & 0xFF;

    BLINKER_LOG("colorR: ", colorR, ", colorG: ", colorG, ", colorB: ", colorB);
    SET_RGB(colorR,colorG,colorB,LED_Bright);
    //pixelShow();

    BlinkerMIOT.color(color);//反馈小爱控制状态
    BlinkerMIOT.print();
}
//小爱调亮度回调
void miotBright(const String & bright)
{
    BLINKER_LOG("need set brightness: ", bright);

    int colorW = bright.toInt();

    BLINKER_LOG("now set brightness: ", colorW);
    LED_Bright = colorW;
    SET_RGB(LED_R,LED_G,LED_B,LED_Bright);
    Serial.printf("亮度调节中...%d",colorW);
    
    BlinkerMIOT.brightness(colorW);//反馈小爱控制状态
    BlinkerMIOT.print();
}
void setup() {
    // 初始化串口
    Serial.begin(115200);

    #if defined(BLINKER_PRINT)
        BLINKER_DEBUG.stream(BLINKER_PRINT);
    #endif

    // 初始化有LED的IO
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(D7, OUTPUT);//红
    pinMode(D6, OUTPUT);//绿色
    pinMode(D5, OUTPUT);//蓝色
    SET_RGB(0,0,0,0);
    digitalWrite(LED_BUILTIN, HIGH);
    // 初始化blinker
    Blinker.begin(auth, ssid, pswd);//连接WiFi和设备上线
    Blinker.attachData(dataRead);//如果没有被绑定的组件被触发就执行这个回调
    Button1.attach(button1_callback);//Button1这个组件被触发就执行这个回调
    RGB1.attach(rgb1_callback);//注册调节颜色的回调函数
    BlinkerMIOT.attachPowerState(miotPowerState);
    BlinkerMIOT.attachColor(miotColor);//小爱调节颜色
    BlinkerMIOT.attachBrightness(miotBright);//小爱调节RGB亮度
}

void loop() {
    Blinker.run();
}
