#include <FS.h>
// ESP8266
//有1MB的储存和相同文件和文件系统加起来3MB的空间
//所以文件系统只有小于3MB的大小
String file_name = "/taichi-maker/notes.txt"; //被读取的文件位置和名称

void setup()
{
  Serial.begin(9600);
  Serial.println("");

  Serial.println("SPIFFS format start");
  SPIFFS.format(); // 格式化SPIFFS
  Serial.println("SPIFFS format finish");

  if (SPIFFS.begin())
  { // 启动SPIFFS
    Serial.println("SPIFFS Started.");
  }
  else
  {
    Serial.println("SPIFFS Failed to Start.");
  }

  File dataFile = SPIFFS.open(file_name, "w"); // 建立File对象用于向SPIFFS中的file对象（即/notes.txt）写入信息
  dataFile.println("Hello IOT World.");        // 向dataFile写入字符串信息
  dataFile.close();                            // 完成文件写入后关闭文件
  Serial.println("Finished Writing data to SPIFFS");
}

void loop()
{
}