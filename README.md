# PHOENIXEngine

## 跨平台应用开发引擎

open soruce cross platform system for Games/AR/VR/AI/IOT/Robots

![robot](https://github.com/manykits/PHOENIXEngine/blob/master/docs/img/robot.png?raw=true)

##目录

[TOC]

## 简述

	欢迎来到PHOENIXEngine，这是一个可以用来开发游戏，机器人，物联网项目，的开发引擎。集成了ORB-Slam2，更可以开发AR增强现实等应用。
	引擎已经支持Windows上，ARM，Linux，LinuxARM，IOS平台，使用简洁高效的Lua作为主要逻辑开发，使用C++/C作为底层构建语言，通过跨平台编译，可以将项目运行在所需要的平台上。
	借助Arduino，ESP8266/32等芯片，使用PHOENIXFrameWireWall，引擎可以支持一般的物联设备开发。
	当需要更高级的嵌入式方案时，我们可以选择LINUXArm作为开发环境，打造高级的物联网系统。
	PHOENIXEngine注重实用，构建上手的容易度，因此只选择了最基本的两种语言，降低使用者的门槛。引擎致力于打造容易实用，典雅优美的开发体验。


##  编译/Compile

### 依赖库

ThirdPartiesLibs.zip：[http://url.cn/49EuKAU](http://url.cn/49EuKAU)

下载放置PHOENIXEngine\Phoenix目录下，解压。

如需编译编辑器NIRVANA2，预先编译ThirdPartiesLibs/wxWidgets-3.0.2/build/msw/wx_vc12.sln

### Windows

使用visualstudio打开PHOENIXEngine/Phoenix.sln编译

### Linux

**1.安装依赖库**

- 	拷贝FMOD:

	进入目录 Phoenix/trunk/Phoenix/ThirdPartiesLibs/

	sudo cp -fr FMOD /usr/local/lib/ 

	sudo chmod 777 /usr/local/lib/FMOD
	
	进入目录 /usr/local/lib/FMOD/linux/lib/x86
	如果是64位系统环境进入 /usr/local/lib/FMOD/linux/lib/x86_64目录

	sudo cp -f libfmod.so.9 /usr/local/lib/

- 	安装OpenGL:

	sudo apt-get install freeglut3-dev

**2.编译引擎库libPX2Engine.so:**

	在目录PHOENIXEngine/Phoenix中执行:make CFG=ReleaseDynamic -f makefile.px2

**3.安装引擎库:**

	在目录PHOENIXEngine/Phoenix中执行:sudo make CFG=ReleaseDynamic -f makefile.px2 install

4.如果具体的项目是动态链接库，需要编译c++源文件，例如如果项目名称为Sample编译项目库为Sample.so
如果想要运行引擎，进行快速查看，可以不需要编译，跳过此项

	在目录PHOENIXEngine/Phoenix/Projects/Client/Sample中执行:make CFG=ReleaseDynamic -f makefile.px2

**5.运行最终的可执行程序**
	
	在PHOENIXEngine/Phoenix/Bin目录执行 ./AppPlayer.ReleaseDynamic
	
### Linux Raspberry

**1.安装依赖库**

- 拷贝FMOD:

	进入目录 Phoenix/trunk/Phoenix/ThirdPartiesLibs/

	sudo cp -fr FMOD /usr/local/lib/ 

	sudo chmod 777 /usr/local/lib/FMOD
	
	进入目录 /usr/local/lib/FMOD/linux/lib/armhf

	sudo cp -f libfmod.so.9 /usr/local/lib/

- 	安装OpenGLES
	
	sudo apt-get install libgles2-mesa-dev

**2.编译引擎库libARMPX2Engine.so:**

	在目录PHEONIXEngine/Phoenix中执行:make CFG=ReleaseARMDynamic -f makefile.px2

**3.安装引擎库:**

	在目录PHEONIXEngine/Phoenix中执行:sudo make CFG=ReleaseARMDynamic -f makefile.px2 install

**4.编译项目库General.so:**

	在目录PHEONIXEngine/Phoenix/Projects/Client/General中执行:make CFG=ReleaseARMDynamic -f makefile.px2

**5.执行**
	
	在PHEONIXEngine/Phoenix/Bin目录执行 AppPlayer.ReleaseARMDynamic

### Android

目前我们使用的还是旧的Android编译方法，使用Crygwin进行编译。

	下载Cygwin:
	安装Cygwin:
	使用Cygwin进行编译:
	使用Ecplise打开项目进行发布:
	导出Ecplise Android项目:

### IOS

	使用XCode打开项目Phoenix/Phoenix.xcworkspace编译项目

## 使用方法/General Use

- Bin/Data/Sample 是一个空项目

	Data下的boost.xml决定从哪个项目启动
	boost.lua可以对启动项二次修改
	
	项目运行前，执行，Sample/lua/start.lua中的prestart
	紧接着运行，执行，Sample/lua/start.lua中的start
	用户的项目逻辑在presstart和start函数中写就可以
