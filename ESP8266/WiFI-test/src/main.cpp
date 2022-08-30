

#include <ESP8266WiFi.h>

const char *ssid = "72B319";

const char *password = "xiao760914aa";

void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

    Serial.print(i++);
    Serial.print(' ');
  }
  digitalWrite(LED_BUILTIN, LOW); //低电平点亮
  Serial.println("");
  Serial.println("Connection established!");
  Serial.print("IP address:    ");
  Serial.println(WiFi.localIP());
}

void loop()
{
}