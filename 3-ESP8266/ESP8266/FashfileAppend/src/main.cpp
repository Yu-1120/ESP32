
#include <FS.h>

String file_name = "/taichi-maker/notes.txt"; //被读取的文件位置和名称

void setup()
{
  Serial.begin(9600);
  Serial.println("");

  if (SPIFFS.begin())
  { // 启动闪存文件系统
    Serial.println("SPIFFS Started.");
  }
  else
  {
    Serial.println("SPIFFS Failed to Start.");
  }

  //确认闪存中是否有file_name文件
  if (SPIFFS.exists(file_name))
  {

    Serial.print(file_name);
    Serial.println(" FOUND.");

    File dataFile = SPIFFS.open(file_name, "a"); // 建立File对象用于向SPIFFS中的file对象（即/notes.txt）写入信息
    dataFile.println("This is Appended Info.");  // 向dataFile添加字符串信息
    dataFile.close();                            // 完成文件操作后关闭文件
    Serial.println("Finished Appending data to SPIFFS ");
    Serial.println("OK");
  }
  else
  {
    Serial.print(file_name);
    Serial.print(" NOT FOUND.");
  }
}

void loop()
{
}