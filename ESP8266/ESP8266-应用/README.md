# My_ESP8266

#### 介绍
这个仓库是我通过arduino IDE写的ESP8266的一些程序
我的bilibili主页：https://space.bilibili.com/389851522?spm_id_from=333.788.b_765f7570696e666f.1

程序说明：带有智能配网功能的程序，有部分程序在断电后还是需要重新配网，遇到这样的情况把程序中定义WiFi账号和密码的变量去掉就可以了（如：char ssid[] = "MI";//WiFi名称
char pswd[] = "asdfghjkl";//WiFi密码
把他们删除或者注释都行）。因为8266会自动保存已连接的WiFi，当断电后程序是从头运行的所以会连接以前的WiFi而需要重新配网。

#### 软件架构
软件架构说明

