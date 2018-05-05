// pxframe.js

unique = function (anArray) {
    return anArray.filter(function (elem, pos) { 
        return anArray.indexOf(elem) == pos; 
    });
};

WorldMorph.prototype.PXFrame = PXFrame;

// PXFrame prototype
function PXFrame (owner) {
    this.owner = owner;
    this.board = undefined;
    this.connecting = false;
    this.disconnecting = false;
    this.justConnected = false;
    this.keepAliveIntervalID = null;
};

// This should belong to the IDE
PXFrame.prototype.showMessage = function (msg) {
    if (!this.message) { this.message = new DialogBoxMorph() };

    var txt = new TextMorph(
            msg,
            this.fontSize,
            this.fontStyle,
            true,
            false,
            'center',
            null,
            null,
            MorphicPreferences.isFlat ? null : new Point(1, 1),
            new Color(255, 255, 255)
            );

    if (!this.message.key) { this.message.key = 'message' + this.owner.name + msg };

    this.message.labelString = this.owner.name;
    this.message.createLabel();
    if (msg) { this.message.addBody(txt) };
    this.message.drawNew();
    this.message.fixLayout();
    this.message.popUp(world);
    this.message.show();
};

PXFrame.prototype.hideMessage = function () {
    if (this.message) {
        this.message.cancel();
        this.message = null;
    }
};

PXFrame.prototype.attemptConnectPXLauncher = function()
{
}

PXFrame.prototype.attemptDisConnectPXLauncher = function()
{
}

PXFrame.prototype.attemptConnection = function () {
    var myself = this;

    if (this.justConnected) {
        this.justConnected = undefined;
        return;
    }

    if (!this.connecting) {
        if (this.board === undefined) 
        {
            // Get list of ports (Arduino compatible)
            var ports = world.PXFrame.getSerialPorts(function (ports)
            {
                var portMenu = new MenuMorph(this, 'select a port');
                if (Object.keys(ports).length >= 1)
                {
                    Object.keys(ports).forEach(function (each) {
                        portMenu.addItem(each, function () {
                            myself.connect(each);
                        })
                    });
                }
                portMenu.popUpAtHand(world);
            });
        }
         else 
        {
            ide.inform(myself.name, localize('There is already a board connected to this sprite'));
        }
    }
};

PXFrame.prototype.attemptWifiConnection = function () {
    var myself = this;

    if (this.justConnected) {
        this.justConnected = undefined;
        return;
    }

    if (!this.connecting) {
        if (this.board === undefined) {
            myself.connectWifi();
        }
        else {
            ide.inform(myself.name, localize('There is already a board connected to this sprite'));
        }
    }
};

PXFrame.prototype.closeHandler = function (silent) {

    var portName = 'unknown';

    clearInterval(this.keepAliveIntervalID);

    if (this.board) 
    {
        portName = this.board.sp.path;

        this.board.sp.removeAllListeners();
        this.board.sp = undefined;

        this.board = undefined;
    };

    Arduino.unlockPort(this.port);
    this.connecting = false;
    this.disconnecting = false;
    this.justConnected = false;

    if (this.gotUnplugged & !silent) {
        ide.inform(
                this.owner.name,
                localize('Board was disconnected from port\n') 
                + portName 
                + '\n\nIt seems that someone pulled the cable!');
        this.gotUnplugged = false;
    } else if (!silent) {
        ide.inform(this.owner.name, localize('Board was disconnected from port\n') + portName);
    }
};

PXFrame.prototype.connect = function (port) {
    var myself = this;
    this.disconnect();

    this.showMessage(localize('Connecting board at port\n') + port);
    this.connecting = true;

    var cntStr = "connect_" + port;
    PXFrame.prototype.getURL('device', cntStr, function (ret) 
    {
        if ("suc" == ret)
        {
            world.PXFrame.lockPort(port);
            myself.port = port;
            myself.connecting = false;
            myself.justConnected = true;

            myself.hideMessage();
            ide.inform(myself.owner.name, localize('An board has been connected. Happy prototyping!'));
        }
        else if ("failed" == ret)
        {     
            //myself.board = null;
            myself.connecting = false;
            myself.hideMessage();
            ide.inform(
                    myself.owner.name,
                    localize('Could not talk to board in port\n')
                    + port + '\n\n' + localize('Check if PHOENIXFrameFirewall is loaded.')
                    );
        }
    });
};

PXFrame.prototype.connectWifi = function () {
    var myself = this;
    this.disconnect();

    this.showMessage(localize('Connecting board\n'));
    this.connecting = true;

    var cntStr = "connectwifi_";
    PXFrame.prototype.getURL('device', cntStr, function (ret) {
        if ("suc" == ret) {
            world.PXFrame.lockPort(1);
            myself.port = 1;
            myself.connecting = false;
            myself.justConnected = true;

            myself.hideMessage();
            ide.inform(myself.owner.name, localize('An board has been connected. Happy prototyping!'));
        }
        else if ("failed" == ret) {
            //myself.board = null;
            myself.connecting = false;
            myself.hideMessage();
            ide.inform(
                myself.owner.name,
                localize('Could not talk to board\n') + localize('Check if PHOENIXFrameFirewall is loaded.')
            );
        }
    }); 
};

PXFrame.prototype.disconnect = function () 
{
    var myself = this;
    if (!myself.justConnected)
    {
        PXFrame.unlockAllPort();
        //PXFrame.unlockPort(myself.port);
        myself.connecting = false;
        myself.disconnecting = false;
        myself.justConnected = false;

        return;
    }

    var cntStr = "disconnect";
    PXFrame.prototype.getURL('device', cntStr, function (ret) 
    {
        if ("suc" == ret)
        {
			PXFrame.unlockAllPort();
            //PXFrame.unlockPort(myself.port);
            myself.connecting = false;
            myself.disconnecting = false;
            myself.justConnected = false;
        }
        else if ("failed" == ret)
        {     
        }
    });
};

PXFrame.prototype.isBoardReady = function () {
    var myself = this;
    return myself.justConnected;
};

PXFrame.prototype.pinsSettableToMode = function (aMode) {
    // Retrieve a list of pins that support a particular mode
    var myself = this,
        pinNumbers = {};

    this.board.pins.forEach(
        function (each) { 
            if (each.supportedModes.indexOf(aMode) > -1) { 
                var number = myself.board.pins.indexOf(each).toString(); 
                pinNumbers[number] = number;
            }
        }
    );

    return pinNumbers;
};

PXFrame.portList = [];
PXFrame.usedPorts = [];

PXFrame.lockPort = function (port) {
    var usedPorts = this.usedPorts;

    if (usedPorts.indexOf(port) === -1) {
        usedPorts.push(port);
    }
};

PXFrame.unlockPort = function (port) {
    var usedPorts = this.usedPorts;

    if (usedPorts.indexOf(port) > -1) {
        usedPorts.splice(usedPorts.indexOf(port));
    }
};

PXFrame.unlockAllPort = function () {
    this.usedPorts = [];
};

PXFrame.isPortLocked = function (port) {
    return (this.usedPorts.indexOf(port) > -1);
};

PXFrame.getSerialPorts = function (callback) {
    var myself = this,
    portList = [],
    portcheck = /usb|DevB|rfcomm|acm|^com/i;

    PXFrame.prototype.getURL('device', "list", function (txt) 
    {
        var textStr = txt
        var strs = new Array(); //定义一数组 
        strs = textStr.split("_");

        strs.forEach(function (device){ 
         if (!myself.isPortLocked(device) && portcheck.test(device)) {
               portList[device] = device; 
            }
        });

        callback(portList);
    });    
};

PXFrame.prototype.getURL = function (cmd, code, callback) {
    var url = "http://127.0.0.1:8387/";
    var method = "GET";
    var myself = this;

    // You REALLY want async = true.
    // Otherwise, it'll block ALL execution waiting for server response.
    var async = false;

    var request = new XMLHttpRequest();

    request.onreadystatechange = function () {
        if (request.readyState != 4) {
            return;
        }

        var status = parseInt(request.status); // HTTP response status, e.g., 200 for "200 OK"
        var errorInfo = null;
        switch (status) {
            case 200:
                if (null != callback) {
                    callback.call(myself, request.responseText);
                }
                break;
            case 0:
                errorInfo = "code 0\n\nCould not connect to server at " + url + ".  Is the local web server running?";
                break;
            case 400:
                errorInfo = "code 400\n\nBuild failed - probably due to invalid source code.  Make sure that there are no missing connections in the blocks.";
                break;
            case 500:
                errorInfo = "code 500\n\nUpload failed.  Is the Arduino connected to USB port?";
                break;
            case 501:
                errorInfo = "code 501\n\nUpload failed.  Is 'ino' installed and in your path?  This only works on Mac OS X and Linux at this time.";
                break;
            default:
                errorInfo = "code " + status + "\n\nUnknown error.";
                break;
        };
    };

    request.open(method, url + "?" + BASE64.encode(cmd + "$" + code), async);
    request.send();

    if (!async) {
        if (request.status === 200) {
            return request.responseText;
        }
        throw new Error('unable to retrieve ' + url);
    }
}