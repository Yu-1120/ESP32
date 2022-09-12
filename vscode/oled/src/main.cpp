// ESP8266的GPIO4和GPIO5分别通过跳线帽连接到OLED屏的SDA和SCL引脚。
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 oled(128, 64, &Wire, -1);

void setup()
{
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.setTextColor(WHITE); //开像素点发光
  oled.clearDisplay();      //清屏
  //一行最多放10个字,字体大小2

  oled.setTextSize(1);   //设置字体大小
  oled.setCursor(15, 5); //设置显示位置X,Y   oled整个屏是128*64
  oled.println("你好世界");

  oled.setTextSize(1);    //设置字体大小
  oled.setCursor(15, 15); //设置显示位置
  oled.println("你好世界");

  oled.setTextSize(1);    //设置字体大小
  oled.setCursor(15, 25); //设置显示位置
  oled.println("TEST");

  oled.setTextSize(1);    //设置字体大小
  oled.setCursor(15, 35); //设置显示位置
  oled.println("TEST");

  oled.setTextSize(1);    //设置字体大小
  oled.setCursor(15, 55); //设置显示位置
  oled.println("Hello world");

  oled.display(); // 开显示
}

void loop() {}