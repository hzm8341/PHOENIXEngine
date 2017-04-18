# Phoenix
Phoenix system for IoT

欢迎来到PhoenixIOT，这是一个可以用来开发游戏，开发机器人的引擎。
经过作者的努力，引擎可以运行字Windows上，ARM，Linux，LinuxARM上。
因为作者开发经费紧张，没有续费Mac开发者，新版本IOS一直还未移植。

PhoniexIOT的目的是为了解决机器人开发中的大难题，
众所周知，开发机器人大多用ROS系统，但是因为其Linux环境的限制（虽然支持
Windows桌面系统，但没有开发板可以装Windows），开发难度很大。我们希望
借助游戏开发中的先进技术，通过脚本编程，让机器人开发更加快速。

下面是一些简单使用说明，我会逐步更新：

下载ThirdPartiesLibs.zip http://url.cn/47RBPDi 
将其放在Phoenix/Phoenix 目录下进行解压
如果需要编译编辑器，需要预先编译ThirdPartiesLibs/wxWidgets-3.0.2/build/msw/wx_vc12.sln
如果需要使用FBX导出插件，需要下载FBX.zip http://url.cn/47borsx
将其解压到ThirdPartiesLibs中

Bin/Dat/General 是一个空项目

Data下的boost.xml决定从哪个项目启动
boost.lua可以对启动项二次修改

项目运行前，执行，General/lua/start.lua中的prestart
紧接着运行，执行，General/lua/start.lua中的start
