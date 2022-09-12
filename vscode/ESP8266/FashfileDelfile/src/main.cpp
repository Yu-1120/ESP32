//从闪存文件系统中删除文件
#include <FS.h>

String file_name = "/"; //被读取的文件位置和名称  删除掉根文件的所有内存

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

  //从闪存中删除file_name文件
  if (SPIFFS.remove(file_name))
  {

    Serial.print(file_name);
    Serial.println(" remove sucess");
  }
  else
  {
    Serial.print(file_name);
    Serial.println(" remove fail");
  }
}

void loop()
{
}