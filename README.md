#PHOENIX IoT
open soruce cross platform system for Games/AR/AI/IOT

##简述

欢迎来到PhoenixIOT，这是一个可以用来开发游戏，AR应用，开发机器人等很多应用的引擎。

引擎底层使用C++作为开发语言，上层使用Lua作为项目逻辑语言，支持Lua的面向对象编程。得益于脚本语言的自由和灵活，
你不需要等待，就可以立即部署你的项目到移动设备，支持Linux的物联网设备等。立即发布的模式免去了繁琐的打包过程，提高开发效率。

众所周知，开发机器人大多用ROS系统，但是因为其Linux环境的限制（虽然支持Windows桌面系统，但没有开发板可以装Windows），开发难度很大。我们希望借助游戏开发中的先进技术，通过脚本编程，让机器人开发更加快速。

引擎使用插件架构，第三方应用都可以作为Plugin集成进来，同时引擎支持两款图形编程插件BlueBlock和BluePrint。

经过作者的努力，引擎可以运行字Windows上，ARM，Linux，LinuxARM上。
因为作者开发经费紧张，没有续费Mac开发者，新版本IOS一直还未移植。

##使用方法
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

##编译

###依赖库

ThirdPartiesLibs.zip：[http://url.cn/49EuKAU](http://url.cn/49EuKAU)

下载放置Phoenix/Phoenix目录下，解压。

如需编译编辑器NIRVANA2，预先编译ThirdPartiesLibs/wxWidgets-3.0.2/build/msw/wx_vc12.sln

###windows

使用visualstudio打开Phoenix/Phoenix.sln编译

###Linux
1.编译引擎库libPX2Engine.so:

	在目录Phoenix/Phoenix中执行:make CFG=ReleaseDynamic -f makefile.px2

2.安装引擎库:

	在目录Phoenix/Phoenix中执行:sudo make CFG=ReleaseDynamic -f makefile.px2 install

3.编译项目库General.so:

	在目录Phoenix/Phoenix/Projects/Client/General中执行:make CFG=ReleaseDynamic -f makefile.px2
	
####Linux Raspberry
1.编译引擎库libPX2Engine.so:

	在目录Phoenix/Phoenix中执行:make CFG=ReleaseARMDynamic -f makefile.px2

2.安装引擎库:

	在目录Phoenix/Phoenix中执行:sudo make CFG=ReleaseARMDynamic -f makefile.px2 install

3.编译项目库General.so:

	在目录Phoenix/Phoenix/Projects/Client/General中执行:make CFG=ReleaseARMDynamic -f makefile.px2

###Android

目前我们使用的还是旧的Android编译方法，使用Crygwin进行编译。编译环境配置方法，我还在写。


