# PHOENIXEngine
开源跨平台 游戏，智能玩具，机器人开发引擎

open soruce cross platform system for Games/Toys/Robot


## 简述
欢迎来到PHOENIXEngine，这是一个可以用来开发游戏，开发机器人的引擎。
引擎支持Windows，ARM，Linux，LinuxARM,iOS平台

众所周知，开发机器人大多用ROS系统，但是因为其Linux环境的限制（虽然支Windows桌面系统，但没有开发板可以装Windows），开发难度很大。游戏领域的众多技术也和机器人领域非常接近，例如他们都广泛使用矩阵数学，A*导航算法，同时在游戏领域也有众多人工智能概念等。

**PHOENIXEngine的目的是为了成为一个便捷的全方位引擎，弥补游戏开发和机器人开发的鸿沟，让游戏开发者，能够平滑过度到机器人开发的领域中，从而缔造出和现实相互结合的智能娱乐体验。**

为了成为一个完整有效的引擎，PHOENIXEngine集成了地形，天空，粒子，动画，UI等系统，并且以朴素经典的**NodeGraph**场景图展示给用户；同时提供一个可以**自动生成控制UI的编辑器**，例似Unity引擎的Inspector；粒子系统更包含了曲线编辑器。

为了成为一个良好的机器人引擎，PHOENIXEngine主要支持最经典的**Arduino**和**Raspberry**，使用单片机和Linux结合，用户可以快速搭建起机器人环境，从而展开对机器人领域的探究。

为了提高开发的效率，PHOENIXEngine使用**Lua**作为逻辑开发语言，支持Lua面向对象的开发方式；同时引擎支持远程空中一件部署，用户可以**通过Wifi一键部署自己的项目**到设备（手机，树莓派等）。

## 示例程序

![](https://github.com/PhoenixCreate/PhoenixCreate/blob/master/Documentation/appplay.png?raw=true)

## 编辑器

![](https://raw.githubusercontent.com/PhoenixCreate/PhoenixCreate/master/Documentation/editor.png)

## 机器人

Arduino 入门机器人

![](https://github.com/PhoenixCreate/PhoenixCreate/blob/master/Documentation/robot0.jpg?raw=true)

借助PhoneixCreate和PhoenixFrame，可以在手机端对Arduino进行编程。

Raspberry 树莓派LinuxARM机器人

![](https://github.com/PhoenixCreate/PhoenixCreate/blob/master/Documentation/robot1.jpg?raw=true)

借助PhoenixCreate系统，使用Lua你可以在树莓派上构建一个高级机器人系统。


## 引擎特性

  	内置EventSystem，通过发送/广播Event，通知EventHandler进行消息相应

  	支持Controller的控制器系统，例似Unity中的Commpont

  	基于Node的场景图管理

  	跨平台材质系统，xml配置不同平台材质

  	支持多个Canvas，并且参与UI组件的排序

  	完善的UI系统，FreeType字体绘制，包含20种UI控件；支持屏幕自适应，满足不同屏幕分辨率布局系统

  	地形系统，支持分页地形，支持LOD地形，支持5层贴图的地表材质

  	6面静态天空盒系统，球形昼夜交替天空系统

  	2D序列帧动画，骨骼动画，蒙皮动画，动画融合，支持一次性，Clamp循环，Circle循环播放模式

  	Autodesk FBX动画模型导入

  	Autodesk 3DMax模型导出插件

  	Autodesk Beast场景烘焙系统

  	特效系统包含，粒子，公告板，条带，波带，模型，震动，声音；支持Curve曲线编辑

  	和FMod良好集成的跨平台音频系统

  	和VLC良好集成的视频系统

  	集成Google ProtoBuf

  	内置网络通信模块，Windows IOCP，Linux epoll/select服务器框架

  	语音识别框架，集成Baidu语音SDK

  	插架架构，支持从Plugin派生的第三方插件扩展

  	内置多语言版本解决方案

  	Linux Serial，GPIO操作

  	蓝牙2.0，4.0通信

  	摄像头拍摄，远程视频传输功能

  	两款图形编程系统BlueBlock和BluePrint，满足初学者和专业级智能编程需求

  	完备的Project项目管理系统，一键远程部署项目，免去打包等中间环节

  	可用的，基于自身UI系统的集成开发环境 Nirvana编辑器

  	脚本系统支持，支持面向对象的Lua开发

  	跨平台运行于Windows，Android，IOS，Linux/LinuxARM


## 使用方法


- 首先Clone项目到你想要运行的目标机器人的目录，

	下载ThirdPartiesLibs.zip [http://pan.baidu.com/s/1o86u2QQ](http://pan.baidu.com/s/1o86u2QQ)
	
	将其放在Phoenix/Phoenix 目录下进行解压
	
	如果需要编译编辑器，需要预先编译ThirdPartiesLibs/wxWidgets-3.0.2/build/msw/wx_vc12.sln
	
	如果需要使用FBX导出插件，需要下载FBX.zip 

- Bin/Dat/General 是一个空项目

	Data下的boost.xml决定从哪个项目启动
	boost.lua可以对启动项二次修改
	
	项目运行前，执行，General/lua/start.lua中的prestart
	紧接着运行，执行，General/lua/start.lua中的start

## 编译

### 依赖库

ThirdPartiesLibs.zip：[http://pan.baidu.com/s/1gfjA2QZ](http://pan.baidu.com/s/1gfjA2QZ)
密码：omz3

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

5.执行
	
	在Phoenix/Phoenix/Bin目录执行 AppPlayer.ReleaseDynamic
	
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


5.执行
	
	在Phoenix/Phoenix/Bin目录执行 AppPlayer.ReleaseARMDynamic

### Android

目前我们使用的还是旧的Android编译方法，使用Crygwin进行编译。

如何将用C++编写Android的代码库：

	[http://www.opengpu.org/forum.php?mod=viewthread&tid=17177](http://www.opengpu.org/forum.php?mod=viewthread&tid=17177)

下载安装Cygwin：[http://pan.baidu.com/s/1i4BFJzZ](http://pan.baidu.com/s/1i4BFJzZ)

![](https://github.com/PhoenixCreate/PhoenixCreate/blob/master/Documentation/img/cygwin.png?raw=true)

### iOS
	打开PHOENIXEngine/Phoenix/Phoenix.xcworkspace使用XCode进行编译