
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
//***************************************************************/
//
//           -------------------------------------------
//           board: ESP8266 Dev Module
//           Flash Mode: "DIO"
//           -------------------------------------------
//
//***************************************************************/

#ifndef STASSID
#define STASSID "qwer"
#define STAPSK  "asdfghjkl"
#endif

const char *ssid = STASSID;
const char *password = STAPSK;

ESP8266WebServer server(80);
bool LED_Flag = false;
String str = "<!DOCTYPE html>\n"
             "<html lang=\"en\">\n"
             "\n"
             "<head>\n"
             "    <meta charset=\"UTF-8\">\n"
             "    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n"
             "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
             "    <title>登录界面</title>\n"
             "    <!-- 引入样式 -->\n"
             "    <style>\n"
             "        html {\n"
             "            height: 100%;\n"
             "        }\n"
             "\n"
             "        body {\n"
             "            /* 去除浏览器的默认样式 */\n"
             "            /* 外边距 */\n"
             "\n"
             "            margin: 0;\n"
             "            /* 内边距 */\n"
             "            padding: 0;\n"
             "            /* 字体 */\n"
             "            font-family: sans-serif;\n"
             "            /* 背景颜色 */\n"
             "            background: linear-gradient(#141e30, #243b55);\n"
             "        }\n"
             "\n"
             "        .login-box {\n"
             "            /* 登录框剧中  绝对定位,下面4个属性实现居中*/\n"
             "            position: absolute;\n"
             "            left: 50%;\n"
             "            top: 50%;\n"
             "            transform: translate(-50%, -50%);\n"
             "\n"
             "            width: 400px;\n"
             "            /* 内边距 */\n"
             "            padding: 40px;\n"
             "            /* 背景颜色 */\n"
             "            background: rgba(0, 0, 0, .6);\n"
             "            /* 标准盒模型 */\n"
             "            box-sizing: border-box;\n"
             "            /* 设置盒子阴影 */\n"
             "            box-shadow: 0 15px 25px rgba(0, 0, 0, .6);\n"
             "            /* 边框圆角 */\n"
             "            border-radius: 10px;\n"
             "        }\n"
             "\n"
             "        /* 登录框标题 */\n"
             "        .login-box h2 {\n"
             "            /* 外边距 上0 右0 左右30px  */\n"
             "            margin: 0 0 30px;\n"
             "            padding: 0;\n"
             "            color: #fff;\n"
             "            /* 文字居中 */\n"
             "            text-align: center;\n"
             "        }\n"
             "\n"
             "        .login-box .user-box {\n"
             "            /* 账号输入框相对定位 */\n"
             "            position: relative;\n"
             "        }\n"
             "\n"
             "        .login-box .user-box input {\n"
             "            width: 100%;\n"
             "            padding: 10px 0;\n"
             "            font-size: 16px;\n"
             "            color: #fff;\n"
             "            margin-bottom: 30px;\n"
             "            /* 去掉所有边框 */\n"
             "            border: none;\n"
             "            /* 保留下边框 */\n"
             "            border-bottom: 1px solid #fff;\n"
             "            outline: none;\n"
             "            /* 背景颜色透明 */\n"
             "            background: transparent;\n"
             "\n"
             "        }\n"
             "\n"
             "        .login-box .user-box label {\n"
             "            /* 绝对定位 */\n"
             "            position: absolute;\n"
             "            top: 0;\n"
             "            left: 0;\n"
             "            /* 内边距 */\n"
             "            padding: 10px 0;\n"
             "            font-size: 16px;\n"
             "            color: #fff;\n"
             "            pointer-events: none;\n"
             "            /* 过度效果 */\n"
             "            transition: .5s;\n"
             "        }\n"
             "\n"
             "        /* 输入框鼠标聚焦\\移开时 */\n"
             "        /* 兄弟选择器 */\n"
             "        .login-box .user-box input:focus~label,\n"
             "        .login-box .user-box input:valid~label {\n"
             "            /* 这里的效果时当鼠标放在输入框时,username和password会有一个位置的挪动 */\n"
             "            top: -20px;\n"
             "            left: 0;\n"
             "            color: #03e9f4;\n"
             "            font-size: 12px;\n"
             "        }\n"
             "\n"
             "        .login-box form a {\n"
             "            /* 相对定位 */\n"
             "            position: relative;\n"
             "            /* 行内块元素 */\n"
             "            display: inline-block;\n"
             "            /* 内边距 */\n"
             "            padding: 10px 20px;\n"
             "            font-size: 16px;\n"
             "            color: #03e9f4;\n"
             "            /* 去掉a 的下划线 */\n"
             "            text-decoration: none;\n"
             "            /* 文字间距增大 */\n"
             "            letter-spacing: 4px;\n"
             "            overflow: hidden;\n"
             "            /* 过渡效果 */\n"
             "            transition: .5s;\n"
             "            margin-top: 40px;\n"
             "            /* 全部转大写 */\n"
             "            text-transform: uppercase;\n"
             "        }\n"
             "\n"
             "        /* 鼠标移上去会有一个发光的效果 */\n"
             "        .login-box a:hover {\n"
             "            background: #03e9f4;\n"
             "            color: #fff;\n"
             "            border-radius: 5px;\n"
             "            /* 盒子阴影 */\n"
             "            box-shadow: 0 0 5px #03e9f4,\n"
             "                0 0 25px #03e9f4,\n"
             "                0 0 50px #03e9f4,\n"
             "                0 0 100px #03e9f4;\n"
             "        }\n"
             "\n"
             "        /* 开始画动画 */\n"
             "\n"
             "        .login-box a span {\n"
             "            /* 绝对定位 */\n"
             "            position: absolute;\n"
             "            /* 块元素 */\n"
             "            display: block;\n"
             "        }\n"
             "\n"
             "        /* 第一根线,上侧,从左至右 */\n"
             "        .login-box a span:nth-child(1) {\n"
             "            top: 0;\n"
             "            left: -100%;\n"
             "            width: 100%;\n"
             "            height: 2px;\n"
             "            /* 背景颜色 */\n"
             "            background: linear-gradient(90deg, transparent, #03e9f4);\n"
             "            /* 动画   持续1S  匀速,无限次运行 */\n"
             "            animation: an-1 1s linear infinite;\n"
             "        }\n"
             "\n"
             "        /* 第一根线,上侧,从左至右 */\n"
             "        @keyframes an-1 {\n"
             "            0% {\n"
             "                left: -100%;\n"
             "            }\n"
             "\n"
             "            50%,\n"
             "            100% {\n"
             "                left: 100%;\n"
             "            }\n"
             "        }\n"
             "\n"
             "\n"
             "        /* 第三根线,下侧,从右至左 */\n"
             "        .login-box a span:nth-child(3) {\n"
             "            bottom: 0;\n"
             "            right: -100%;\n"
             "            width: 100%;\n"
             "            height: 2px;\n"
             "            /* 背景颜色 */\n"
             "            background: linear-gradient(270deg, transparent, #03e9f4);\n"
             "            /* 动画   持续1S  匀速,无限次运行 */\n"
             "            animation: an-3 1s linear infinite;\n"
             "            animation-delay: .5s;\n"
             "\n"
             "        }\n"
             "\n"
             "        /* 第三根线,下侧,从右至左 */\n"
             "        @keyframes an-3 {\n"
             "            0% {\n"
             "                right: -100%;\n"
             "            }\n"
             "\n"
             "            50%,\n"
             "            100% {\n"
             "                right: 100%;\n"
             "            }\n"
             "        }\n"
             "\n"
             "        /* 第二根先,右侧,从上至下 */\n"
             "\n"
             "\n"
             "        .login-box a span:nth-child(2) {\n"
             "            top: -100%;\n"
             "            right: 0;\n"
             "            height: 100%;\n"
             "            width: 2px;\n"
             "            background: linear-gradient(180deg, transparent, #03e9f4);\n"
             "            /* 动画 */\n"
             "            animation: an-2 1s linear infinite;\n"
             "            /* 延迟 */\n"
             "            animation-delay: .25s;\n"
             "        }\n"
             "\n"
             "        /* 第二根先,右侧,从上至下 */\n"
             "        @keyframes an-2 {\n"
             "            0% {\n"
             "                top: -100%;\n"
             "            }\n"
             "\n"
             "            50%,\n"
             "            100% {\n"
             "                top: 100%;\n"
             "            }\n"
             "        }\n"
             "\n"
             "\n"
             "        /* 第四根线,左侧,从下至上 */\n"
             "\n"
             "        .login-box a span:nth-child(4) {\n"
             "            bottom: -100%;\n"
             "            left: 0;\n"
             "            height: 100%;\n"
             "            width: 2px;\n"
             "            background: linear-gradient(360deg, transparent, #03e9f4);\n"
             "            /* 动画 */\n"
             "            animation: an-4 1s linear infinite;\n"
             "            /* 延迟 */\n"
             "            animation-delay: .75s;\n"
             "        }\n"
             "\n"
             "        /* 第四根线,左侧,从下至上 */\n"
             "        @keyframes an-4 {\n"
             "            0% {\n"
             "                bottom: -100%;\n"
             "            }\n"
             "\n"
             "            50%,\n"
             "            100% {\n"
             "                bottom: 100%;\n"
             "            }\n"
             "        }\n"
             "    </style>\n"
             "</head>\n"
             "\n"
             "<body>\n"
             "    <div class=\"login-box\">\n"
             "        <h2>Login</h2>\n"
             "        <form name=\"my\">\n"
             "            <!-- 账号输入框 -->\n"
             "            <div class=\"user-box\">\n"
             "                <input type=\"text\" name=\"s\" required=\"\" id=\"aa\">\n"
             "                <label for=\"\">WiFi名称：</label>\n"
             "            </div>\n"
             "            <!-- 密码输入框 -->\n"
             "            <div class=\"user-box\">\n"
             "                <input type=\"password\" name=\"p\" required=\"\" id=\"bb\">\n"
             "                <label for=\"\">WiFi密码：</label>\n"
             "            </div>\n"
             "            <!-- 提交按钮 -->\n"
             "            <a href=\"\">\n"
             "                <!-- <span></span>\n"
             "                <span></span>\n"
             "                <span></span>\n"
             "                <span></span> -->\n"
             "                <input type=\"button\" value=\"连接\" style=\" border:0 none;  background: transparent;  ;opacity: 1; color:#fff;font-size: 15px;\n"
             "                \" onclick=\"wifi()\">\n"
             "            </a>\n"
             "        </form>\n"
             "    </div>\n"
             "    <script language=\"javascript\">\n"
             "\n"
             "        function wifi() {\n"
             "            var ssid = my.s.value;\n"
             "            var password = bb.value;\n"
             "            if (ssid == 0 || password == 0) {\n"
             "                alert(\"账号或者密码为空,请重新输入账号和密码\");\n"
             "                alert(\"The account or password is blank, please re-enter the account and password\");\n"
             "            } else {\n"
             "                var xmlhttp = new XMLHttpRequest();\n"
             "                xmlhttp.open(\"GET\", \"/HandleVal?ssid=\" + ssid + \"&password=\" + password, true);\n"
             "                xmlhttp.send()\n"
             "                alert(\"用户名为：\" + ssid + ' ' + \"密码为：\" + password);\n"
             "\n"
             "            }\n"
             "\n"
             "\n"
             "        }\n"
             "    </script>\n"
             "</body>\n"
             "\n"
             "</html>";

/*****************************************************
 * 函数名称：handleRoot()
 * 函数说明：客户端请求回调函数
 * 参数说明：无
******************************************************/
void handleRoot() {
    server.send(200, "text/html", str);
}

/*****************************************************
 * 函数名称：HandleVal()
 * 函数说明：对客户端请求返回值处理
 * 参数说明：无
******************************************************/
void HandleVal() {
    String wifis = server.arg("ssid"); //从JavaScript发送的数据中找ssid的值
    String wifip = server.arg("password"); //从JavaScript发送的数据中找password的值
    Serial.println(wifis);
    Serial.println(wifip);
    WiFi.begin(wifis, wifip);
}

/*****************************************************
 * 函数名称：handleNotFound()
 * 函数说明：响应失败函数
 * 参数说明：无
******************************************************/
void handleNotFound() {
    digitalWrite(LED_BUILTIN, 0);
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";
    for (uint8_t i = 0; i < server.args(); i++) {
        message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }
    server.send(404, "text/plain", message);
    digitalWrite(LED_BUILTIN, 1);
}

/*****************************************************
 * 函数名称：autoConfig()
 * 函数说明：自动连接WiFi函数
 * 参数说明：无
 * 返回值说明:true：连接成功 false：连接失败
******************************************************/
bool autoConfig() {
    WiFi.mode(WIFI_STA);
    WiFi.begin();
    Serial.print("AutoConfig Waiting......");
    for (int i = 0; i < 20; i++) {
        if (WiFi.status() == WL_CONNECTED) {
            Serial.println("AutoConfig Success");
            Serial.printf("SSID:%s\r\n", WiFi.SSID().c_str());
            Serial.printf("PSW:%s\r\n", WiFi.psk().c_str());
            WiFi.printDiag(Serial);
            return true;
            //break;
        } else {
            Serial.print(".");
            LED_Flag = !LED_Flag;
            if (LED_Flag)
                digitalWrite(LED_BUILTIN, HIGH);
            else
                digitalWrite(LED_BUILTIN, LOW);
            delay(500);
        }
    }
    Serial.println("AutoConfig Faild!");
    return false;
    //WiFi.printDiag(Serial);
}

/*****************************************************
 * 函数名称：htmlConfig()
 * 函数说明：web配置WiFi函数
 * 参数说明：无
******************************************************/
void htmlConfig() {
    WiFi.mode(WIFI_AP_STA);//设置模式为AP+STA
    digitalWrite(LED_BUILTIN, LOW);
    WiFi.softAP(ssid, password);
    Serial.println("AP设置完成");

    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);

    if (MDNS.begin("esp8266")) {
        Serial.println("MDNS responder started");
    }

    server.on("/", handleRoot);
    server.on("/HandleVal", HTTP_GET, HandleVal);
    server.onNotFound(handleNotFound);//请求失败回调函数

    server.begin();//开启服务器
    Serial.println("HTTP server started");
    while (1) {
        server.handleClient();
        MDNS.update();
        if (WiFi.status() == WL_CONNECTED) {
            Serial.println("HtmlConfig Success");
            Serial.printf("SSID:%s\r\n", WiFi.SSID().c_str());
            Serial.printf("PSW:%s\r\n", WiFi.psk().c_str());
            Serial.println("HTML连接成功");
            break;
        }
    }
}

void setup(void) {
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH); //灭

    bool wifiConfig = autoConfig();

    if (wifiConfig == false) {
        htmlConfig();//HTML配网
    }
    //配置成功才会往下走

}

void loop(void) {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); //点亮
    delay(500);
}