/**********************************************************************
通过程序读取目录内容
***********************************************************************/

#include <FS.h>

String file_name = "/taichi-maker/myFile.txt"; //被读取的文件位置和名称
String folder_name = "/taichi-maker";          //被读取的文件夹

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

  File dataFile = SPIFFS.open(file_name, "w"); // 建立File对象用于向SPIFFS中的file对象（即myFile.txt）写入信息
  dataFile.println("Hello Taichi-Maker.");     // 向dataFile写入字符串信息
  dataFile.close();                            // 完成文件写入后关闭文件
  Serial.println(F("Finished Writing data to SPIFFS"));

  // 显示目录中文件内容以及文件大小
  Dir dir = SPIFFS.openDir(folder_name); // 建立“目录”对象

  while (dir.next())
  {                                 // dir.next()用于检查目录中是否还有“下一个文件”
    Serial.println(dir.fileName()); // 输出文件名
  }
}

void loop()
{
}