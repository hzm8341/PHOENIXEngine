// objects.js

SpriteMorph.prototype.originalInit = SpriteMorph.prototype.init;
SpriteMorph.prototype.init = function(globals) {
    this.originalInit(globals);
	this.pxframe = new PXFrame(this);
};

SpriteMorph.prototype.categories.push('PXFrame');
SpriteMorph.prototype.blockColor['PXFrame'] = new Color(0, 151, 156);

// makerclock
SpriteMorph.prototype.categories.push('MakerClock');
SpriteMorph.prototype.blockColor['MakerClock'] = new Color(0, 151, 200);

SpriteMorph.prototype.originalInitBlocks = SpriteMorph.prototype.initBlocks;
SpriteMorph.prototype.initPXFBlocks = function () {

    this.blocks.pxf_GetServerMessage =
    {
        only: SpriteMorph,
        type: 'predicate',
        category: 'PXFrame',
        spec: 'GetServerMessage',
        transpilable: true
    };

    this.blocks.pxf_PinMode =
    {
        only: SpriteMorph,
        type: 'command',
        category: 'PXFrame',
        spec: 'PinMode %pxf_Pin as %pxf_PinMode',
        defaults: ["2", 'output'],
        transpilable: true
    };
	
	this.blocks.pxf_DigitalWrite =
    {
        only: SpriteMorph,
        type: 'command',
        category: 'PXFrame',
        spec: 'DigitalWrite %pxf_Pin as %b',
        defaults: ["2", true],
        transpilable: true
    };

    this.blocks.pxf_PwmWrite =
    {
        only: SpriteMorph,
        type: 'command',
        category: 'PXFrame',
        spec: 'PwmWrite %pxf_PwmPin as %n',
        defaults: ["2", 255],
        transpilable: true
    };

    this.blocks.pxf_AnalogWrite =
    {
        only: SpriteMorph,
        type: 'command',
        category: 'PXFrame',
        spec: 'AnalogWrite %pxf_AnalogPin as %n',
        defaults: ["A0", 255],
        transpilable: true
    };

    this.blocks.pxf_DigitalRead =
    {
        only: SpriteMorph,
        type: 'predicate',
        category: 'PXFrame',
        spec: 'DigitalRead %pxf_Pin',
        defaults: ["2"],
        transpilable: true
    };

    this.blocks.pxf_AnalogRead =
    {
        only: SpriteMorph,
        type: 'reporter',
        category: 'PXFrame',
        spec: 'AnalogRead %pxf_AnalogPin',
        defaults: ["A0"],
        transpilable: true
    };

    this.blocks.pxf_ServerInit =
    {
        only: SpriteMorph,
        type: 'command',
        category: 'PXFrame',
        spec: 'Server index %n init at pin %pxf_Pin',
        defaults: [0, "A0"],
        transpilable: true
    };

    this.blocks.pxf_ServerWrite =
    {
        only: SpriteMorph,
        type: 'command',
        category: 'PXFrame',
        spec: 'Server index %n write value %n',
        defaults: [0, 90],
        transpilable: true
    };

    this.blocks.pxf_DistInit =
    {
        only: SpriteMorph,
        type: 'command',
        category: 'PXFrame',
        spec: 'DistInit at pin0 %pxf_Pin and pin1 %pxf_Pin',
        defaults: ["A4", "A5"],
        transpilable: true
    };

    this.blocks.pxf_DistTest =
    {
        only: SpriteMorph,
        type: 'command',
        category: 'PXFrame',
        spec: 'DistTest',
        transpilable: true
    };

    this.blocks.pxf_GetDist =
    {
        only: SpriteMorph,
        type: 'reporter',
        category: 'PXFrame',
        spec: 'GetDist',
        transpilable: true
    };

    this.blocks.pxf_VehicleInit_MotoBoard =
    {
        only: SpriteMorph,
        type: 'command',
        category: 'PXFrame',
        spec: 'VehicleInitMotoBoard',
        transpilable: true
    };

    this.blocks.pxf_VehicleInit_MotoBoard4567 =
    {
        only: SpriteMorph,
        type: 'command',
        category: 'PXFrame',
        spec: 'VehicleInitMotoBoard4567',
        transpilable: true
    };

    this.blocks.pxf_VehicleInit_MotoBoard298N =
    {
        only: SpriteMorph,
        type: 'command',
        category: 'PXFrame',
        spec: 'VehicleInitMotoBoard298N at pinLA %pxf_Pin and pinLB %pxf_Pin and pinLS %pxf_Pin and pinRA %pxf_Pin and pinRB %pxf_Pin pinRS %pxf_Pin',
        defaults: [4, 5, 6, 7, 8, 9],
        transpilable: true
    };

    this.blocks.pxf_VehicleRun =
    {
        only: SpriteMorph,
        type: 'command',
        category: 'PXFrame',
        spec: 'moto %n run %pxf_dirtype at speed %n',
        defaults: [0, "forward", 255],
        transpilable: true
    };

    this.blocks.pxf_VehicleSimpleRun =
    {
        only: SpriteMorph,
        type: 'command',
        category: 'PXFrame',
        spec: 'moto run %pxf_simpledirtype at speed %n',
        defaults: ["forward", 255],
        transpilable: true
    };

    this.blocks.pxf_VehicleStop =
    {
        only: SpriteMorph,
        type: 'command',
        category: 'PXFrame',
        spec: 'stop motos',
        transpilable: true
    };

    this.blocks.pxf_VehicleSpeedEncorderInit =
    {
        only: SpriteMorph,
        type: 'command',
        category: 'PXFrame',
        spec: 'VehicleSpeedEncorderInit at pinLA %pxf_Pin and pinLB %pxf_Pin and pinRA %pxf_Pin and pinRB %pxf_Pin',
        defaults: [2, "A0", 3, "A1"],
        transpilable: true
    };

    this.blocks.pxf_VehicleGetSpeed =
    {
        only: SpriteMorph,
        type: 'reporter',
        category: 'PXFrame',
        spec: 'GetSpeed of moto %n',
        defaults: [0],
        transpilable: true
    };

    this.blocks.pxf_MP3Init =
    {
        only: SpriteMorph,
        type: 'command',
        category: 'PXFrame',
        spec: 'MP3 init at pinR %pxf_Pin pinT %pxf_Pin',
        defaults: [7, 8],
        transpilable: true
    };

    this.blocks.pxf_MP3Play =
    {
        only: SpriteMorph,
        type: 'command',
        category: 'PXFrame',
        spec: 'MP3 play',
        transpilable: true
    };

    this.blocks.pxf_MP3PlayIndex =
    {
        only: SpriteMorph,
        type: 'command',
        category: 'PXFrame',
        spec: 'MP3 play at index %n',
        defaults: [1],
        transpilable: true
    };

    this.blocks.pxf_MP3PlayStop =
    {
        only: SpriteMorph,
        type: 'command',
        category: 'PXFrame',
        spec: 'MP3 stop',
        transpilable: true
    };
    
    this.blocks.pxf_MP3SetVolume =
    {
        only: SpriteMorph,
        type: 'command',
        category: 'PXFrame',
        spec: 'MP3 set volume at %n',
        defaults: [25],
        transpilable: true
    };

    this.blocks.pxf_MP3Next =
    {
        only: SpriteMorph,
        type: 'command',
        category: 'PXFrame',
        spec: 'MP3 next',
        transpilable: true
    };

    this.blocks.pxf_IRInit =
    {
        only: SpriteMorph,
        type: 'command',
        category: 'PXFrame',
        spec: 'infrared recviver init at pin %pxf_Pin',
        defaults: [7],
        transpilable: true
    };

    this.blocks.pxf_IRSend =
    {
        only: SpriteMorph,
        type: 'command',
        category: 'PXFrame',
        spec: 'infrared send value %n',
        defaults: [100],
        transpilable: true
    };
	
	this.blocks.pxf_WeightInit =
    {
        only: SpriteMorph,
        type: 'command',
        category: 'PXFrame',
        spec: 'weight tester %n init at pinOut %pxf_Pin pinClk %pxf_Pin',
        defaults: [0, 7, 8],
        transpilable: true
    };
	
	this.blocks.pxf_WeightTest =
    {
        only: SpriteMorph,
        type: 'command',
        category: 'PXFrame',
        spec: 'test the weight of %n',
        defaults: [0],
        transpilable: true
    };
	
	this.blocks.pxf_GetWeight =
    {
        only: SpriteMorph,
        type: 'reporter',
        category: 'PXFrame',
        spec: 'get weight of %n',
		defaults: [0],
        transpilable: true
    };

    // makerclock
    this.blocks.pxf_MC_LightInternal =
    {
        only: SpriteMorph,
        type: 'command',
        category: 'MakerClock',
        spec: 'LED internal as %b',
        defaults: [true],
        transpilable: true
    };

    this.blocks.pxf_MC_LED =
    {
        only: SpriteMorph,
        type: 'command',
        category: 'MakerClock',
        spec: 'LED %pxf_Pin_mc as %b',
        defaults: ["1", true],
        transpilable: true
    };

    this.blocks.pxf_MC_Buzzer =
    {
        only: SpriteMorph,
        type: 'command',
        category: 'MakerClock',
        spec: 'Buzzer %pxf_Pin_mc as %b',
        defaults: ["1", true],
        transpilable: true
    };

    this.blocks.pxf_MC_Segment =
    {
        only: SpriteMorph,
        type: 'command',
        category: 'MakerClock',
        spec: 'LEDSegment %pxf_Pin_mc as %n',
        defaults: ["3", 100],
        transpilable: true
    };

    this.blocks.pxf_MC_Moto =
    {
        only: SpriteMorph,
        type: 'command',
        category: 'MakerClock',
        spec: 'Moto %pxf_PinMoto_mc as speed %n',
        defaults: ["1", 100],
        transpilable: true
    };

    this.blocks.pxf_MC_DistTest =
    {
        only: SpriteMorph,
        type: 'command',
        category: 'MakerClock',
        spec: 'UltraSensor %pxf_Pin_mc Get dist',
        defaults: ["1"],
        transpilable: true
    };

    this.blocks.pxf_MC_GetDist =
    {
        only: SpriteMorph,
        type: 'reporter',
        category: 'MakerClock',
        spec: 'UltraSensor getDist',
        transpilable: true
    };

    StageMorph.prototype.codeMappings['pxf_GetServerMessage'] = 'manykit.pxf_GetServerMessage();';

	StageMorph.prototype.codeMappings['pxf_PinMode'] = 'manykit.pxf_PinMode(<#1>, <#2>);';
	StageMorph.prototype.codeMappings['pxf_DigitalWrite'] = 'manykit.pxf_DigitalWrite(<#1>, <#2>);';
    StageMorph.prototype.codeMappings['pxf_PwmWrite'] = 'manykit.pxf_PwmWrite(<#1>, <#2>);';
    StageMorph.prototype.codeMappings['pxf_DigitalRead'] = 'manykit.pxf_DigitalRead(<#1>);';
    StageMorph.prototype.codeMappings['pxf_AnalogWrite'] = 'manykit.pxf_AnalogWrite(<#1>, <#2>);';
    StageMorph.prototype.codeMappings['pxf_AnalogRead'] = 'manykit.pxf_AnalogRead(<#1>);';
	
	StageMorph.prototype.codeMappings['pxf_ServerInit'] = 'manykit.pxf_ServerInit(<#1>, <#2>);';
    StageMorph.prototype.codeMappings['pxf_ServerWrite'] = 'manykit.pxf_ServerWrite(<#1>, <#2>);';
    
    StageMorph.prototype.codeMappings['pxf_DistInit'] = 'manykit.pxf_DistInit(<#1>, <#2>);';
    StageMorph.prototype.codeMappings['pxf_DistTest'] = 'manykit.pxf_DistTest();';
    StageMorph.prototype.codeMappings['pxf_GetDist'] = 'manykit.pxf_GetDist();';
    
    StageMorph.prototype.codeMappings['pxf_VehicleInit_MotoBoard'] = 'manykit.pxf_VehicleInit_MotoBoard();';
    StageMorph.prototype.codeMappings['pxf_VehicleInit_MotoBoard4567'] = 'manykit.pxf_VehicleInit_MotoBoard4567();';
	StageMorph.prototype.codeMappings['pxf_VehicleRun'] = 'manykit.pxf_VehicleRun(<#1>, <#2>, <#3>);';
	StageMorph.prototype.codeMappings['pxf_VehicleSimpleRun'] = 'manykit.pxf_VehicleSimpleRun(<#1>,<#2>);';
    StageMorph.prototype.codeMappings['pxf_VehicleStop'] = 'manykit.pxf_VehicleStop();';
    StageMorph.prototype.codeMappings['pxf_VehicleSpeedEncorderInit'] = 'manykit.pxf_VehicleSpeedEncorderInit(<#1>, <#2>, <#3>, <#4>);';
    StageMorph.prototype.codeMappings['pxf_VehicleGetSpeed'] = 'manykit.pxf_VehicleGetSpeed(<#1>);';

    StageMorph.prototype.codeMappings['pxf_MP3Init'] = 'manykit.pxf_MP3Init(<#1>, <#2>);';
    StageMorph.prototype.codeMappings['pxf_MP3Play'] = 'manykit.pxf_MP3Play();';
    StageMorph.prototype.codeMappings['pxf_MP3PlayIndex'] = 'manykit.pxf_MP3PlayIndex(<#1>);';
    StageMorph.prototype.codeMappings['pxf_MP3PlayStop'] = 'manykit.pxf_MP3PlayStop();';
    StageMorph.prototype.codeMappings['pxf_MP3SetVolume'] = 'manykit.pxf_MP3SetVolume(<#1>);';
    StageMorph.prototype.codeMappings['pxf_MP3Next'] = 'manykit.pxf_MP3Next();';

    StageMorph.prototype.codeMappings['pxf_IRInit'] = 'manykit.pxf_IRInit(<#1>);';
    StageMorph.prototype.codeMappings['pxf_IRSend'] = 'manykit.pxf_IRSend();';
	
	StageMorph.prototype.codeMappings['pxf_WeightInit'] = 'manykit.pxf_WeightInit(<#1>, <#2>, <#3>);';
    StageMorph.prototype.codeMappings['pxf_WeightTest'] = 'manykit.pxf_WeightTest(<#1>);';
	StageMorph.prototype.codeMappings['pxf_GetWeight'] = 'manykit.pxf_GetWeight(<#1>);';

    StageMorph.prototype.codeMappings['pxf_MC_LightInternal'] = 'manykit.pxf_MC_LightInternal(<#1>)';
    StageMorph.prototype.codeMappings['pxf_MC_LED'] = 'manykit.pxf_MC_LED(<#1>, <#2>)';
    StageMorph.prototype.codeMappings['pxf_MC_Buzzer'] = 'manykit.pxf_MC_Buzzer(<#1>, <#2>)';
    StageMorph.prototype.codeMappings['pxf_MC_Segment'] = 'manykit.pxf_MC_Segment(<#1>, <#2>)';
    StageMorph.prototype.codeMappings['pxf_MC_DistTest'] = 'manykit.pxf_MC_DistTest(<#1>)';
    StageMorph.prototype.codeMappings['pxf_MC_GetDist'] = 'manykit.pxf_MC_GetDist()';
}

SpriteMorph.prototype.initBlocks =  function() {
    this.originalInitBlocks();
    this.initPXFBlocks();
};

SpriteMorph.prototype.initBlocks();

SpriteMorph.prototype.originalBlockTemplates = SpriteMorph.prototype.blockTemplates;
SpriteMorph.prototype.blockTemplates = function (category) {
    var myself = this,
        blocks = myself.originalBlockTemplates(category); 
		
	function blockBySelector (selector) {
        if (StageMorph.prototype.hiddenPrimitives[selector]) {
            return null;
        }
        var newBlock = SpriteMorph.prototype.blockForSelector(selector, true);
        newBlock.isTemplate = true;
        return newBlock;
    };

    //  Button that triggers a connection attempt 
    this.arduinoConnectPXLauncher = new PushButtonMorph(
        null,
        function () {
            myself.pxframe.attemptConnectPXLauncher();
        },
        'Connect PXLauncher'
        );

    this.arduinoDisConnectPXLauncher = new PushButtonMorph(
        null,
        function () {
            myself.pxframe.attemptDisConnectPXLauncher();
        },
        'DisConnect PXLauncher'
        );

    this.arduinoConnectButton = new PushButtonMorph(
            null,
            function () {
                myself.pxframe.attemptConnection();
            },
            'Connect PXFrame'
            );
    
    this.arduinoConnectWifiButton = new PushButtonMorph(
        null,
        function () {
            myself.pxframe.attemptWifiConnection();
        },
        'Connect PXFrame Wifi'
    );

    //  Button that triggers a disconnection from board
    this.arduinoDisconnectButton = new PushButtonMorph(
            null,
            function () {
                myself.pxframe.disconnect();
            },
            'Disconnect PXFrame'
            );

    if (category === 'PXFrame') {
        //blocks.push(this.arduinoConnectPXLauncher);
        //blocks.push(this.arduinoDisConnectPXLauncher);
        //blocks.push('-'); 
        blocks.push(this.arduinoConnectButton);
        blocks.push(this.arduinoConnectWifiButton);
        blocks.push(this.arduinoDisconnectButton);
        blocks.push('-'); 
        blocks.push(blockBySelector('pxf_GetServerMessage'));
        blocks.push('-'); 
        blocks.push(blockBySelector('pxf_PinMode'));
		blocks.push(blockBySelector('pxf_DigitalWrite'));
		blocks.push(blockBySelector('pxf_PwmWrite'));
		blocks.push(blockBySelector('pxf_DigitalRead'));
		blocks.push(blockBySelector('pxf_AnalogWrite'));
		blocks.push(blockBySelector('pxf_AnalogRead'));
        blocks.push('-');      
		blocks.push(blockBySelector('pxf_ServerInit'));
		blocks.push(blockBySelector('pxf_ServerWrite'));
		blocks.push('-');
		blocks.push(blockBySelector('pxf_DistInit'));	
		blocks.push(blockBySelector('pxf_DistTest'));	
		blocks.push(blockBySelector('pxf_GetDist'));
		blocks.push('-');
        blocks.push(blockBySelector('pxf_VehicleInit_MotoBoard'));
        blocks.push(blockBySelector('pxf_VehicleInit_MotoBoard4567'));
        blocks.push(blockBySelector('pxf_VehicleInit_MotoBoard298N'));
		blocks.push(blockBySelector('pxf_VehicleRun'));
		blocks.push(blockBySelector('pxf_VehicleSimpleRun'));
        blocks.push(blockBySelector('pxf_VehicleStop'));
        blocks.push(blockBySelector('pxf_VehicleSpeedEncorderInit'));
        blocks.push(blockBySelector('pxf_VehicleGetSpeed'));
        blocks.push('-');
        blocks.push(blockBySelector('pxf_MP3Init'));
        blocks.push(blockBySelector('pxf_MP3Play'));
        blocks.push(blockBySelector('pxf_MP3PlayIndex'));
        blocks.push(blockBySelector('pxf_MP3PlayStop'));
        blocks.push(blockBySelector('pxf_MP3SetVolume'));
        blocks.push(blockBySelector('pxf_MP3Next'));
		blocks.push('-');
		blocks.push(blockBySelector('pxf_WeightInit'));
        blocks.push(blockBySelector('pxf_WeightTest'));
		blocks.push(blockBySelector('pxf_GetWeight'));
        blocks.push('-');
        blocks.push(blockBySelector('pxf_IRInit'));
        blocks.push(blockBySelector('pxf_IRSend'));
    }

    if (category === 'MakerClock') {
        blocks.push(this.arduinoConnectPXLauncher);
        blocks.push(this.arduinoDisConnectPXLauncher);
        blocks.push('-');
        blocks.push(this.arduinoConnectButton);
        blocks.push(this.arduinoConnectWifiButton);
        blocks.push(this.arduinoDisconnectButton);
        blocks.push('-');
        blocks.push(blockBySelector('pxf_MC_LightInternal'));
        blocks.push(blockBySelector('pxf_MC_LED'));
        blocks.push(blockBySelector('pxf_MC_Buzzer'));
        blocks.push(blockBySelector('pxf_MC_Segment'));
        blocks.push(blockBySelector('pxf_MC_Moto'));
        blocks.push(blockBySelector('pxf_MC_DistTest'));
        blocks.push(blockBySelector('pxf_MC_GetDist'));   
    }

    return blocks;
};