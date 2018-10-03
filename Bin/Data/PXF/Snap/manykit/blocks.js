// blocks.js

SyntaxElementMorph.prototype.originalLabelPart = SyntaxElementMorph.prototype.labelPart;
SyntaxElementMorph.prototype.labelPart = function(spec) {
    var part,
        block = this;

    switch (spec) {
		case '%_Pin':
			part = new InputSlotMorph(
					null,
					false,
					{
                        '0': ['0'],
                        '1': ['1'],
                        '2': ['2'],
						'3' : ['3'],
						'3' : ['3'],
						'4' : ['4'],
						'5' : ['5'],
						'6' : ['6'],
						'7' : ['7'],
						'8' : ['8'],
						'9' : ['9'],
						'10' : ['10'],
						'11' : ['11'],
						'12' : ['12'],
						'13' : ['13'],
						'A0' : ['A0'],
						'A1' : ['A1'],
						'A2' : ['A2'],
						'A3' : ['A3'],
						'A4' : ['A4'],
						'A5' : ['A5']
                    },
                    true
					);
			part.originalChanged = part.changed;
			part.changed = function () { part.originalChanged(); if (block.toggle) { block.toggle.refresh(); } };
        break;
        case '%_AnalogPin':
            part = new InputSlotMorph(
                    null,
                    false,
                    {
                        'A0' : ['A0'],
                        'A1' : ['A1'],
                        'A2' : ['A2'],
                        'A3' : ['A3'],
                        'A4' : ['A4'],
                        'A5' : ['A5']
                    },
                    true
                    );
            part.originalChanged = part.changed;
            part.changed = function () { part.originalChanged(); if (block.toggle) { block.toggle.refresh(); } };
            break;
        case '%_PwmPin':
            part = new InputSlotMorph(
                    null,
                    false,
                    {
                        '3' : ['3'],
                        '5' : ['5'],
                        '6' : ['6'],
                        '9' : ['9'],
                        '10' : ['10'],
                        '11' : ['11']
                    },
                    true
                    );
            break;
        case '%_dirtype':
            part = new InputSlotMorph(
                null,
                false,
                {
                    'none': ['none'],
                    'forward': ['forward'],
                    'backward': ['backward']
                },
				true
            );
            break;
        case '%_simpledirtype':
            part = new InputSlotMorph(
                null,
                false,
                {
                    'none': ['none'],
                    'go': ['go'],
                    'back': ['back'],
                    'left': ['left'],
                    'right': ['right']
                },
				true
            );
            break;
        case '%_PinMode':
            part = new InputSlotMorph(
                null,
                false,
                {
                    'input' : ['input'],
                    'output' : ['output']
                },
                true
                );
            break;
        case '%_HighLow':
            part = new InputSlotMorph(
                null,
                false,
                {
                    'high' : ['high'],
                    'low' : ['low']
                },
                true
                );
            break;
        case '%_Pin_mc':
            part = new InputSlotMorph(
                null,
                true,
                {
                    'P_1': ['P_1'],
                    'P_2': ['P_2'],
                    'P_3': ['P_3'],
                    'P_3': ['P_3'],
                    'P_4': ['P_4'],
                    'P_5': ['P_5'],
                    'P_6': ['P_6'],
                    'P_7': ['P_7'],
                    'P_8': ['P_8'],
                    'P_9': ['P_9'],
                    'P_10': ['P_10']
                },
                true
            );
            part.originalChanged = part.changed;
            part.changed = function () { part.originalChanged(); if (block.toggle) { block.toggle.refresh(); } };
            break;
        case '%_PinMoto_mc':
            part = new InputSlotMorph(
                null,
                true,
                {
                    'P_1': ['P_1'],
                    'P_2': ['P_2'],
                }
            );
            part.originalChanged = part.changed;
            part.changed = function () { part.originalChanged(); if (block.toggle) { block.toggle.refresh(); } };
            break;
        default:
            part = this.originalLabelPart(spec);
            break;
    }
    return part;
};

BlockMorph.prototype.originalUserMenu = BlockMorph.prototype.userMenu;
BlockMorph.prototype.userMenu = function () {
    var menu = this.originalUserMenu();
    if (StageMorph.prototype.enableCodeMapping && this.selector == 'receiveGo') {
        menu.addLine();
        menu.addItem(
                'export as Arduino sketch...',
                'transpileToC'
                );
    }
    return menu;
};

BlockMorph.prototype.transpileToC = function () {
    var ide = this.parentThatIsA(IDE_Morph),
        safeChars = {"á": "a", "à": "a", "ä": "a",
                     "é": "e", "è": "e", "ë": "e",
                     "í": "i", "ì": "i", "ï": "i",
                     "ó": "o", "ò": "o", "ö": "o",
                     "ú": "u", "ù": "u", "ü": "u",
                     "Á": "A", "À": "A", "Ä": "A",
                     "É": "E", "È": "E", "Ë": "E",
                     "Í": "I", "Ì": "I", "Ï": "I",
                     "Ó": "O", "Ò": "O", "Ö": "O",
                     "Ú": "U", "Ù": "U", "Ü": "U",
                     "ç":"c", "Ç": "C", "ñ": "n", "Ñ": "N"},
        fileName = ide.projectName || 'manykitarduino';

    fileName = fileName.replace(/[^\w ]/g, function(char) {
        return safeChars[char] || char;
    });
    fileName = fileName.replace(/ /g,'_')
    fileName = fileName.replace(/[^a-zA-Z0-9_]/g,'');
    try {
        ide.saveFileAs(
                this.world().Arduino.transpile(
                    this.mappedCode(),
                    this.parentThatIsA(ScriptsMorph).children.filter(
                        function (each) {
                            return each instanceof HatBlockMorph &&
                                each.selector == 'receiveMessage';
                        })),
                'application/ino;chartset=utf-8',
                fileName);
    } catch (error) {
        ide.inform('Error exporting to Arduino sketch!', error.message)
    }
};