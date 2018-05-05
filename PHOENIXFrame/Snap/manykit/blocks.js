// blocks.js

SyntaxElementMorph.prototype.originalLabelPart = SyntaxElementMorph.prototype.labelPart;
SyntaxElementMorph.prototype.labelPart = function(spec) {
    var part,
        block = this;

    switch (spec) {
		case '%pxf_Pin':
			part = new InputSlotMorph(
					null,
					true,
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
					}
					);
			part.originalChanged = part.changed;
			part.changed = function () { part.originalChanged(); if (block.toggle) { block.toggle.refresh(); } };
        break;
        case '%pxf_AnalogPin':
            part = new InputSlotMorph(
                    null,
                    true,
                    {
                        'A0' : ['A0'],
                        'A1' : ['A1'],
                        'A2' : ['A2'],
                        'A3' : ['A3'],
                        'A4' : ['A4'],
                        'A5' : ['A5']
                    }
                    );
            part.originalChanged = part.changed;
            part.changed = function () { part.originalChanged(); if (block.toggle) { block.toggle.refresh(); } };
            break;
        case '%pxf_PwmPin':
            part = new InputSlotMorph(
                    null,
                    true,
                    {
                        '3' : ['3'],
                        '5' : ['5'],
                        '6' : ['6'],
                        '9' : ['9'],
                        '10' : ['10'],
                        '11' : ['11']
                    }
                    );
            break;
        case '%pxf_dirtype':
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
        case '%pxf_simpledirtype':
            part = new InputSlotMorph(
                null,
                false,
                {
                    'none': ['none'],
                    'forward': ['forward'],
                    'backward': ['backward'],
                    'left': ['left'],
                    'right': ['right']
                },
				true
            );
            break;
        case '%pxf_PinMode':
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
        case '%pxf_Pin_mc':
            part = new InputSlotMorph(
                null,
                true,
                {
                    '1': ['1'],
                    '2': ['2'],
                    '3': ['3'],
                    '3': ['3'],
                    '4': ['4'],
                    '5': ['5'],
                    '6': ['6'],
                    '7': ['7'],
                    '8': ['8'],
                    '9': ['9'],
                    '10': ['10']
                }
            );
            part.originalChanged = part.changed;
            part.changed = function () { part.originalChanged(); if (block.toggle) { block.toggle.refresh(); } };
            break;
        case '%pxf_PinMoto_mc':
            part = new InputSlotMorph(
                null,
                true,
                {
                    '1': ['1'],
                    '2': ['2'],
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