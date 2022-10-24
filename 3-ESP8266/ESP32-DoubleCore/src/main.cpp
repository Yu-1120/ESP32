#include <Arduino.h>
#include <Ticker.h>

Ticker ticker; // 建立Ticker用于实现定时功能
int count;     // 计数用变量
void sayHi()
{
    count++;
    Serial.print("Hi ");
    Serial.println(count);
}

void setup()
{
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);

    // 每隔一秒钟调用sayHi函数一次，attach函数的第一个参数
    // 是控制定时间隔的变量。该参数的单位为秒。第二个参数是
    // 定时执行的函数名称。
    ticker.attach(1, sayHi);
}

void loop()
{
    // 用LED呼吸灯效果来演示在Tinker对象控制下，ESP8266可以定时
    // 执行其它任务
    for (int fadeValue = 0; fadeValue <= 1023; fadeValue += 5)
    {
        analogWrite(LED_BUILTIN, fadeValue);
        delay(10);
    }

    for (int fadeValue = 1023; fadeValue >= 0; fadeValue -= 5)
    {
        analogWrite(LED_BUILTIN, fadeValue);
        delay(10);
    }
    delay(3000);
}

// 在Tinker对象控制下，此函数将会定时执行。
