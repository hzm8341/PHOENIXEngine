pxframeDict = {
    'Connect PXFrame':
        '连接到PXFrame Arduino板',

    'Disconnect PXFrame':
        '断开与PXFrame Arduino的连接',

    'Connect PXFrame Wifi':
        '连接到PXFrame Arduino Wifi板',

    'An board has been connected. Happy prototyping!':
        '接上PHOENIXFrame Arduino板了，祝你玩得愉快！',

    'Board was disconnected from port\n':
        '控制板已中断连接，引脚：\n',

    'Board is not connected':
        '没有连接控制板',

    'Connecting board at port\n':
        '连接控制板在端口',

    'Connecting board\n':
        '连接控制板',

    'PHOENIXFrame Arduino board not connected':
        'PHOENIXFrame Arduino 板没有连接',

    'Could not talk to board in port\n':
        '无法连接到PHOENIXFrame Arduino板端口\n',
    
    'Could not talk to board\n':
        '无法连接到PHOENIXFrame Arduino板\n',
    
    'Check if PHOENIXFrameFirewall is loaded.':
        '检测PHOENIXFrame防火墙代码是否已经加载',

    'select a port': '选择一个端口',
		
    'PinMode %pxf_Pin as %pxf_PinMode': '引脚 %pxf_Pin 设为 %pxf_PinMode',
    
    'input': '输入',
    'output': '输出',

    'DigitalWrite %pxf_Pin as %b': '引脚 %pxf_Pin 输出 %b',
    'PwmWrite %pxf_PwmPin as %n': '引脚 %pxf_PwmPin PWM输出 %n',
    'DigitalRead %pxf_Pin': '引脚 %pxf_Pin 数字值',

    'AnalogWrite %pxf_AnalogPin as %n': '引脚 %pxf_AnalogPin 模拟写入 %n',    
    'AnalogRead %pxf_AnalogPin': '引脚 %pxf_AnalogPin 模拟值',

    'Server index %n init at pin %pxf_Pin' : '私服舵机 %n 初始化在引脚 %pxf_Pin',
    'Server index %n write value %n': '私服舵机 %n 写入 %n',

    'DistInit at pin0 %pxf_Pin and pin1 %pxf_Pin' : '超声波初始化在 触发引脚 %pxf_Pin 和 回声引脚 %pxf_Pin',
    'DistTest' : '超声波测试',
    'GetDist' : '获得超声波距离',

    'forward': '前进',
    'backward': '后退',
    'left': '左',
    'right': '右',

    'VehicleInitMotoBoard' : '电机驱动板初始化',
    'VehicleInitMotoBoard4567': '电机驱动板初始化4567',
    'VehicleInitMotoBoard298N': '电机驱动板初始化298N',

    'VehicleInitMotoBoard298N at pinLA %pxf_Pin and pinLB %pxf_Pin and pinLS %pxf_Pin and pinRA %pxf_Pin and pinRB %pxf_Pin pinRS %pxf_Pin': '电机驱动板298N初始化在 控制脚pinLA %pxf_Pin 控制脚pinLB %pxf_Pin 速度脚pinLS %pxf_Pin 控制脚pinRA %pxf_Pin 控制脚pinRB %pxf_Pin 速度脚pinLS %pxf_Pin',

    'moto %n run %pxf_dirtype at speed %n': '电机 %n 以 %pxf_dirtype 方向 %n 速度运行',
    'moto run %pxf_simpledirtype at speed %n': '以 %pxf_simpledirtype 方向 %n 速度运行',
    'stop motos': '电机停止',
    'VehicleSpeedEncorderInit at pinLA %pxf_Pin and pinLB %pxf_Pin and pinRA %pxf_Pin and pinRB %pxf_Pin':'电机速度编码器初始化在pinLA %pxf_Pin pinLB %pxf_Pin pinRA %pxf_Pin pinRB %pxf_Pin',
    'GetSpeed of moto %n': '获得 %n 的电机马达转速',

    'MP3 init at pinR %pxf_Pin pinT %pxf_Pin': 'MP3初始化在接收引脚 %pxf_Pin 和 发射引脚 %pxf_Pin',
    'MP3 play' : 'MP3 播放',
    'MP3 play at index %n': 'MP3播放第 %n 首',
    'MP3 stop': 'MP3停止',
    'MP3 set volume at %n': 'MP3设置声音大小为 %n',
    'MP3 next': 'MP3播放下一首',

    'infrared recviver init at pin %pxf_Pin': '红外接收器初始化在端口 %pxf_Pin',
    'infrared send value %n': '红外发射器发送 %n',
	
	'weight tester %n init at pinOut %pxf_Pin pinClk %pxf_Pin':'称重模块 %n 初始化在输出端口 %pxf_Pin 和时钟端口 %pxf_Pin',
	'test the weight of %n':'检测第 %n 称重模块的重量',
	
	'get weight of %n':'获得第 %n 称重模块的重量',
};

for (var attrname in pxframeDict) { SnapTranslator.dict.zh_CN[attrname] = pxframeDict[attrname]; }
