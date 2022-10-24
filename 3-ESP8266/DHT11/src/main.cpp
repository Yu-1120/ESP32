#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); // 128*64像素，逐行式
#define DHTPIN 14                                                 //定义引脚D5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
void setup()
{
    Serial.begin(115200);
    dht.begin();
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) // 扫描OLED的地址，默认0x3c
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ;
    }
    delay(2000);
    display.clearDisplay();      //  清屏
    display.setTextColor(WHITE); //开像素点发光
}
void loop()
{
    delay(5000);
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    if (isnan(h) || isnan(t)) // 如果都没有采集到数据，则打印失败
    {
        Serial.println("Failed to read from DHT sensor!");
    }
    Serial.println(t, 2);
    display.clearDisplay();  // 清屏
    display.setTextSize(1);  // 字体
    display.setCursor(0, 0); //显示位置在第一行第一个
    display.print("Temp: ");
    display.setTextSize(2);
    display.print(t);
    display.print(" ");
    display.setTextSize(1);
    display.cp437(true); //使用cp437符号集
    display.write(167);  //对应的温度符号
    display.setTextSize(2);
    display.print("C"); // display humidity
    display.setTextSize(1);
    display.setCursor(0, 25);
    display.print("Humi: ");
    display.setTextSize(2);
    display.print(h);
    display.print(" %");
    display.display();
}
