// all information

#include <FS.h>

FSInfo fs_info;

void setup()
{
  Serial.begin(9600);

  SPIFFS.begin(); //启动SPIFFS
  Serial.println("");
  Serial.println("SPIFFS Started.");

  // 闪存文件系统信息
  SPIFFS.info(fs_info);

  // 可用空间总和（单位：字节）
  Serial.print("totalBytes: ");
  Serial.print(fs_info.totalBytes);
  Serial.println(" Bytes");

  // 已用空间（单位：字节）
  Serial.print("usedBytes: ");
  Serial.print(fs_info.usedBytes);
  Serial.println(" Bytes");

  // 最大文件名字符限制（含路径和'\0'）
  Serial.print("maxPathLength: ");
  Serial.println(fs_info.maxPathLength);

  // 最多允许打开文件数量
  Serial.print("maxOpenFiles: ");
  Serial.println(fs_info.maxOpenFiles);

  // 存储块大小
  Serial.print("blockSize: ");
  Serial.println(fs_info.blockSize);

  // 存储页大小
  Serial.print("pageSize: ");
  Serial.println(fs_info.pageSize);
}

void loop()
{
}