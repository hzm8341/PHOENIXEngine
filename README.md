PHOENIX IoT
=====
open soruce cross platform system for Games/AR/AI/IOT

use game technology to develop IoT

欢迎
----

欢迎来到PhoenixIOT，这是一个可以用来开发游戏，AR应用，开发机器人等很多应用的引擎。

引擎底层使用C++作为开发语言，上层使用Lua作为项目逻辑语言，支持Lua的面向对象编程。得益于脚本语言的自由和灵活，
你不需要等待，就可以立即部署你的项目到移动设备，支持Linux的物联网设备等。立即发布的模式免去了繁琐的打包过程，提高开发效率。

众所周知，开发机器人大多用ROS系统，但是因为其Linux环境的限制（虽然支持Windows桌面系统，但没有开发板可以装Windows），开发难度很大。我们希望借助游戏开发中的先进技术，通过脚本编程，让机器人开发更加快速。

引擎使用插件架构，第三方应用都可以作为Plugin集成进来，同时引擎支持两款图形编程插件BlueBlock和BluePrint。

经过作者的努力，引擎可以运行字Windows上，ARM，Linux，LinuxARM上。
因为作者开发经费紧张，没有续费Mac开发者，新版本IOS一直还未移植。

特性
----
 - 内置EventSystem，通过发送/广播Event，通知EventHandler进行消息相应
 - 支持Controller的控制器系统，例似Unity中的Commpont
 - 基于Node的场景图管理
 - 跨平台材质系统，xml配置不同平台材质
 - 支持多个Canvas，并且参与UI组件的排序
 - 完善的UI系统，FreeType字体绘制，包含20种UI控件；支持屏幕自适应，满足不同屏幕分辨率布局系统
 - 地形系统，支持分页地形，支持LOD地形，支持5层贴图的地表材质
 - 6面静态天空盒系统，球形昼夜交替天空系统
 - 2D序列帧动画，骨骼动画，蒙皮动画，动画融合，支持一次性，Clamp循环，Circle循环播放模式
 - Autodesk FBX动画模型导入
 - Autodesk 3DMax模型导出插件
 - Autodesk Beast场景烘焙系统
 - 特效系统包含，粒子，公告板，条带，波带，模型，震动，声音；支持Curve曲线编辑
 - 和FMod良好集成的跨平台音频系统
 - 和VLC良好集成的视频系统
 - 集成Google ProtoBuf
 - 内置网络通信模块，Windows IOCP，Linux epoll/select服务器框架
 - 语音识别框架，集成Baidu语音SDK
 - 插架架构，支持从Plugin派生的第三方插件扩展
 - 内置多语言版本解决方案
 - Linux Serial，GPIO操作
 - 蓝牙2.0通信
 - 摄像头拍摄，远程视频传输功能
 - 两款图形编程系统BlueBlock和BluePrint，满足初学者和专业级智能编程需求
 - 完备的Project项目管理系统，一件远程部署项目，免去打包等中间环节
 - 可用的，基于自身UI系统的集成开发环境 Nirvana编辑器
 - 脚本系统支持，支持面向对象的Lua开发
 - 跨平台运行于Windows，Android，IOS，Linux/LinuxARM
编译
----
依赖库

ThirdPartiesLibs.zip：[http://url.cn/49EuKAU](http://url.cn/49EuKAU)

下载放置Phoenix/Phoenix目录下，解压。

如需编译编辑器NIRVANA2，预先编译ThirdPartiesLibs/wxWidgets-3.0.2/build/msw/wx_vc12.sln

windows

  - 使用visualstudio打开Phoenix/Phoenix.sln，编译

  - 运行：AppPlayer.exe，NIRVANA2.exe

linux

  - 编译引擎库libPX2Engine.so:

	在目录Phoenix/Phoenix中执行:make CFG=ReleaseDynamic -f makefile.px2

  - 安装引擎库:

	在目录Phoenix/Phoenix中执行:sudo make CFG=ReleaseDynamic -f makefile.px2 install

  - 编译项目库General.so:

	在目录Phoenix/Phoenix/Projects/Client/General中执行:make CFG=ReleaseDynamic -f makefile.px2

  - 运行：
  
  	AppPlayer.ReleaseDynamic

Linux Raspberry

  - 编译引擎库libPX2Engine.so:

	在目录Phoenix/Phoenix中执行:make CFG=ReleaseARMDynamic -f makefile.px2

  - 安装引擎库:

	在目录Phoenix/Phoenix中执行:sudo make CFG=ReleaseARMDynamic -f makefile.px2 install

  - 编译项目库General.so:

	在目录Phoenix/Phoenix/Projects/Client/General中执行:make CFG=ReleaseARMDynamic -f makefile.px2

  - 运行：
  
  	AppPlayer.ReleaseARMDynamic

Android

目前我们使用的还是旧的Android编译方法，使用Crygwin进行编译。编译环境配置方法，我还在写。

项目
----

Bin/Dat/General 是一个空项目

Data下的boost.xml决定从哪个项目启动

boost.lua可以对启动项二次修改

项目运行前，执行，General/lua/start.lua中的prestart
紧接着运行，执行，General/lua/start.lua中的start

