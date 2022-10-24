#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//
/*
 * oled
 * ESP8266����OLED��
 * // ESP8266��GPIO4(D2)��GPIO5(1)�ֱ�ͨ������ñ���ӵ�OLED����SDA��SCL���š�
 * GPIP0(D3)����
 */
//��д����ȥ,ˢһЩ�̼�
void parseInfo(WiFiClient client);

const char *ssid = "72B319";           // ����WiFi�����˴�ʹ��taichi-makerΪʾ����
// �뽫����Ҫ���ӵ�WiFi������������
const char *password = "xiao760914aa"; // ����WiFi���루�˴�ʹ��12345678Ϊʾ����

const char *host = "api.seniverse.com"; // ��Ҫ���ӵķ�������ַ
const int httpPort = 80;                // ��Ҫ���ӵķ������˿�
Adafruit_SSD1306 oled(128, 64, &Wire, -1);
// ��֪����HTTP����������Ϣ
String reqUserKey = "SfGSzf23A2Ftdkzei"; // ˽Կ
String reqLocation = "Jieyang";          // ����
String reqUnit = "c";                    // ����/����

// ����֪����������������������Ϣ������Ϣ���н���
void httpRequest(String reqRes) {
    WiFiClient client;

    // ����http������Ϣ
    String httpRequest = String("GET ") + reqRes + " HTTP/1.1\r\n" +
                         "Host: " + host + "\r\n" +
                         "Connection: close\r\n\r\n";
    Serial.println("");
    Serial.print("Connecting to ");
    Serial.print(host);

    // �������ӷ�����
    if (client.connect(host, 80)) {
        Serial.println(" Success!");

        // �����������http������Ϣ
        client.print(httpRequest);
        Serial.println("Sending request: ");
        Serial.println(httpRequest);

        // ��ȡ����ʾ��������Ӧ״̬��
        String status_response = client.readStringUntil('\n');
        Serial.print("status_response: ");
        Serial.println(status_response);

        // ʹ��find����HTTP��Ӧͷ
        if (client.find("\r\n\r\n")) {
            Serial.println("Found Header End. Start Parsing.");
        }

        // ����ArduinoJson�������֪������Ӧ��Ϣ
        parseInfo(client);
    } else {
        Serial.println(" connection failed!");
    }
    //�Ͽ��ͻ�������������ӹ���
    client.stop();
}

// ����WiFi
void connectWiFi() {
    WiFi.begin(ssid, password);     // ������������
    Serial.print("Connecting to "); // ���ڼ������������������Ϣ
    Serial.print(ssid);
    Serial.println(" ..."); // ��֪�û�NodeMCU���ڳ���WiFi����
    oled.setCursor(2, 20); //������ʾλ��
    int i = 0; // ��һ�γ���������ڼ��WiFi�Ƿ����ӳɹ�
    while (WiFi.status() != WL_CONNECTED) {                // WiFi.status()�����ķ���ֵ����NodeMCU��WiFi����״̬�������ġ�
        delay(500); // ���WiFi���ӳɹ��򷵻�ֵΪWL_CONNECTED
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        oled.print("."); //������ʾλ��
        oled.display();  // ����ʾ
        Serial.print(i++);
        Serial.print(' ');                     // �˴�ͨ��Whileѭ����NodeMCUÿ��һ���Ӽ��һ��WiFi.status()��������ֵ
    }                                          // ͬʱNodeMCU��ͨ�����ڼ������������ʱ�����롣
    digitalWrite(LED_BUILTIN, LOW);
//    oled.setTextSize(1);   //���������С
//    oled.setCursor(2, 35); //������ʾλ��
//    oled.println("Connected,IP address:");
//    oled.println();
//    oled.println(WiFi.localIP());
    // ���������ͨ������iÿ��һ���Լ�1��ʵ�ֵġ�
    Serial.println("");                        // WiFi���ӳɹ���
    Serial.println("Connection established!"); // NodeMCU��ͨ�����ڼ��������"���ӳɹ�"��Ϣ��
    Serial.print("IP address:    ");           // ͬʱ�������NodeMCU��IP��ַ����һ������ͨ������
    Serial.println(WiFi.localIP());            // WiFi.localIP()������ʵ�ֵġ��ú����ķ���ֵ��NodeMCU��IP��ַ��
}

// ����ArduinoJson�������֪������Ӧ��Ϣ
void parseInfo(WiFiClient client) {
    const size_t capacity =
            JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 2 * JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(6) + 230;
    DynamicJsonDocument doc(capacity);

    deserializeJson(doc, client);

    JsonObject results_0 = doc["results"][0];

    JsonObject results_0_now = results_0["now"];
    const char *results_0_now_text = results_0_now["text"]; // "Sunny"
    const char *results_0_now_code = results_0_now["code"]; // "0"
    const char *results_0_now_temperature = results_0_now["temperature"]; // "32"

    const char *results_0_last_update = results_0["last_update"]; // "2020-06-02T14:40:00+08:00"

    // ͨ�����ڼ�������ʾ������Ϣ
    String results_0_now_text_str = results_0_now["text"].as<String>();
    int results_0_now_code_int = results_0_now["code"].as<int>();
    int results_0_now_temperature_int = results_0_now["temperature"].as<int>();

    String results_0_last_update_str = results_0["last_update"].as<String>();

    Serial.println(F("======Weahter Now======="));
    Serial.print(F("Weather Now: "));
    Serial.print(results_0_now_text_str);
    Serial.print(F(" "));
    Serial.println(results_0_now_code_int);
    Serial.print(F("Temperature: "));
    Serial.println(results_0_now_temperature_int);
    Serial.print(F("Last Update: "));
    Serial.println(results_0_last_update_str);
    Serial.println(F("========================"));
    oled.clearDisplay();      //����
    oled.setTextSize(2);   //���������С
    oled.setCursor(15, 5); //������ʾλ��
    oled.print(F("temp: "));
    oled.println(results_0_now_temperature_int);  //�¶�
    oled.display(); // ����ʾ
}

void setup() {
    Serial.begin(9600);
    Serial.println("");
    pinMode(LED_BUILTIN, OUTPUT);

    oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    oled.setTextColor(WHITE); //�����ص㷢��
    oled.clearDisplay();      //����


    // ����WiFi
    connectWiFi();
}

void loop() {
    // ������֪����API��ǰ����������Դ��ַ
    String reqRes = "/v3/weather/now.json?key=" + reqUserKey +
                    +"&location=" + reqLocation +
                    "&language=en&unit=" + reqUnit;

    // ����֪����������������������Ϣ������Ϣ���н���
    httpRequest(reqRes);
    delay(3000);
}
