
/*
 * oled
 * ESP8266����OLED��
 * // ESP8266��GPIO4(D2)��GPIO5(1)�ֱ�ͨ������ñ���ӵ�OLED����SDA��SCL���š�
 * GPIP0(D3)����
 */
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//��д����ȥ,ˢһЩ�̼�

const char *ssid = "72B319"; // ����WiFi�����˴�ʹ��taichi-makerΪʾ����
// �뽫����Ҫ���ӵ�WiFi������������
const char *password = "xiao760914aa"; // ����WiFi���루�˴�ʹ��12345678Ϊʾ����

Adafruit_SSD1306 oled(128, 64, &Wire, -1);

void setup()
{
    oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    oled.setTextColor(WHITE); //�����ص㷢��
    oled.clearDisplay();      //����

    oled.setTextSize(1);   //���������С
    oled.setCursor(15, 5); //������ʾλ��
    oled.println("WiFi Information");
    oled.setCursor(2, 20); //������ʾλ��

    WiFi.begin(ssid, password); //������������

    while (WiFi.status() != WL_CONNECTED) //��������Ƿ����ӳɹ�
    {
        delay(500);
        oled.print("."); //������ʾλ��
        oled.display();  // ����ʾ
    }

    oled.setTextSize(1);   //���������С
    oled.setCursor(2, 35); //������ʾλ��
    oled.println("Connected,IP address:");
    oled.println();
    oled.println(WiFi.localIP());
    oled.display(); // ����ʾ
}

void loop() {}
