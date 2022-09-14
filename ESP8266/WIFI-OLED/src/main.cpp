
/*
 * oled
 * ESP8266驱动OLED屏
 * // ESP8266的GPIO4(D2)和GPIO5(1)分别通过跳线帽连接到OLED屏的SDA和SCL引脚。
 * GPIP0(D3)下拉
 */
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//烧写不进去,刷一些固件

const char *ssid = "72B319";           // 连接WiFi名（此处使用taichi-maker为示例）
// 请将您需要连接的WiFi名填入引号中
const char *password = "xiao760914aa"; // 连接WiFi密码（此处使用12345678为示例）

Adafruit_SSD1306 oled(128, 64, &Wire, -1);

void setup() {
    oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    oled.setTextColor(WHITE); //开像素点发光
    oled.clearDisplay();      //清屏

    oled.setTextSize(1);   //设置字体大小
    oled.setCursor(15, 5); //设置显示位置
    oled.println("WiFi Information");
    oled.setCursor(2, 20); //设置显示位置

    WiFi.begin(ssid, password); //启动网络连接

    while (WiFi.status() != WL_CONNECTED) //检测网络是否连接成功
    {
        delay(500);
        oled.print("."); //设置显示位置
        oled.display();  // 开显示
    }

    oled.setTextSize(1);   //设置字体大小
    oled.setCursor(2, 35); //设置显示位置
    oled.println("Connected,IP address:");
    oled.println();
    oled.println(WiFi.localIP());
    oled.display(); // 开显示
}

void loop() {}
