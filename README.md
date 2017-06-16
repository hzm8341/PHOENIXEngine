# PHOENIX IoT
open soruce cross platform system for Games/AR/VR/AI/IOT

## 简述

	欢迎来到PhoenixIOT，这是一个可以用来开发游戏，开发机器人的引擎。
	经过作者的努力，引擎可以运行字Windows上，ARM，Linux，LinuxARM上。
	因为作者开发经费紧张，没有续费Mac开发者，新版本IOS一直还未移植。

	PhoniexIOT的目的是为了解决机器人开发中的大难题，众所周知，开发机器人大多用ROS系统，但是因为其Linux环境的限制（虽然支	
	Windows桌面系统，但没有开发板可以装Windows），开发难度很大。我们希望借助游戏开发中的先进技术，通过脚本编程，让机器人开发更加快速。

## 使用方法


- 首先Clone项目到你想要运行的目标机器人的目录，

	下载ThirdPartiesLibs.zip https://share.weiyun.com/fcdf4d57fad2d266faea280d974c8ebe
	
	将其放在Phoenix/Phoenix 目录下进行解压
	
	如果需要编译编辑器，需要预先编译ThirdPartiesLibs/wxWidgets-3.0.2/build/msw/wx_vc12.sln
	
	如果需要使用FBX导出插件，需要下载FBX.zip https://share.weiyun.com/f658ffc5112bb8f8b7b4258753655abd

- Bin/Dat/General 是一个空项目

	Data下的boost.xml决定从哪个项目启动
	boost.lua可以对启动项二次修改
	
	项目运行前，执行，General/lua/start.lua中的prestart
	紧接着运行，执行，General/lua/start.lua中的start

## 编译

### 依赖库

ThirdPartiesLibs.zip：[http://url.cn/49EuKAU](http://url.cn/49EuKAU)

下载放置Phoenix/Phoenix目录下，解压。

如需编译编辑器NIRVANA2，预先编译ThirdPartiesLibs/wxWidgets-3.0.2/build/msw/wx_vc12.sln

### windows

使用visualstudio打开Phoenix/Phoenix.sln编译

### Linux

1.安装依赖库

- 	拷贝FMOD:

	进入目录 Phoenix/trunk/Phoenix/ThirdPartiesLibs/

	sudo cp -fr FMOD /usr/local/lib/ 

	sudo chmod 777 /usr/local/lib/FMOD
	
	进入目录 /usr/local/lib/FMOD/linux/lib/x86

	sudo cp -f libfmod.so.9 /usr/local/lib/

- 	安装OpenGL:

	sudo apt-get install freeglut3-dev

2.编译引擎库libPX2Engine.so:

	在目录Phoenix/Phoenix中执行:make CFG=ReleaseDynamic -f makefile.px2

3.安装引擎库:

	在目录Phoenix/Phoenix中执行:sudo make CFG=ReleaseDynamic -f makefile.px2 install

4.编译项目库General.so:

	在目录Phoenix/Phoenix/Projects/Client/General中执行:make CFG=ReleaseDynamic -f makefile.px2
	
#### Linux Raspberry

1.安装依赖库

	
- 拷贝FMOD:

	进入目录 Phoenix/trunk/Phoenix/ThirdPartiesLibs/

	sudo cp -fr FMOD /usr/local/lib/ 

	sudo chmod 777 /usr/local/lib/FMOD
	
	进入目录 /usr/local/lib/FMOD/linux/lib/armhf

	sudo cp -f libfmod.so.9 /usr/local/lib/

- 	安装OpenGLES
	
	sudo apt-get install libgles2-mesa-dev

2.编译引擎库libARMPX2Engine.so:

	在目录Phoenix/Phoenix中执行:make CFG=ReleaseARMDynamic -f makefile.px2

3.安装引擎库:

	在目录Phoenix/Phoenix中执行:sudo make CFG=ReleaseARMDynamic -f makefile.px2 install

4.编译项目库General.so:

	在目录Phoenix/Phoenix/Projects/Client/General中执行:make CFG=ReleaseARMDynamic -f makefile.px2

### Android

目前我们使用的还是旧的Android编译方法，使用Crygwin进行编译。编译环境配置方法，我还在写。


