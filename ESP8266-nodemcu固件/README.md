硬件：

NodeMCU开发板*1（某宝指导价15.8元！）

![img](https://hongecho.oss-cn-hangzhou.aliyuncs.com/images/1917743-20200329152335095-121155949.jpg)



准备直接做一块

---

软件

**ESP8266Flasher：https://github.com/nodemcu/nodemcu-flasher**

## 第一步 烧写固件

首先我们将板子连接好，然后双击打开esp8266flasher.exe

![img](https://hongecho.oss-cn-hangzhou.aliyuncs.com/images/1917743-20200329153006174-1851356427.png)

 

打开后一般都可以自动识别到端口号，如果没有识别出来的可以试试，重新拔插一下板子或者手动安装一下板子的驱动。因为我的板子的驱动之前就已经装好的，所以在这里就不给大家演示了。

识别到端口号后我们就可以点击Config栏来选择我们要下载的固件，按照如图所示就可以。

![img](https://hongecho.oss-cn-hangzhou.aliyuncs.com/images/1917743-20200329153617408-1725461205.png)

在这里要说一下，我们现在要烧写不带DEBUG的固件，如果烧写了带DEBUG的固件可能会出现这个问题：[nodeMCU无限打印wifi event monitor handle event cb is called ](http://www.xjtudll.cn/Exp/507/  )[

](http://www.xjtudll.cn/Exp/507/)

选择完固件后我们还要修改一下比特率，如图

![img](https://hongecho.oss-cn-hangzhou.aliyuncs.com/images/1917743-20200329154440924-1513934333.png)

这样就配置完了，接下来就可以开始下载固件了，返回到Operation界面，点击fiash,等待下载完成即可

![img](https://hongecho.oss-cn-hangzhou.aliyuncs.com/images/1917743-20200329154647821-794940665.png)

 `这里有个小细节就是上电后按flash,之前手按着复位,按下flash的同时收开复位键`

---

这样就下载完成了

![img](https://hongecho.oss-cn-hangzhou.aliyuncs.com/images/1917743-20200329155146869-783291412.png)
