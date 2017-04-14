windows£º
	decompile ThirdPartiesLibs.zip compile Phoenix.sln

linux:
	engine:
		change dir to "Phoenix/Phoenix"
			make CFG=ReleaseDynamic -f makefile.px2
			sudo make CFG=ReleaseDynamic -f makefile.px2 install
	project:
		chnage dir to "Phoenix\Phoenix\Projects\Client\General"
			make CFG=ReleaseDynamic -f makefile.px2
linuxARM:
	engine:
		change dir to "Phoenix/Phoenix"
		make CFG=ReleaseDynamicARM -f makefile.px2
		sudo make CFG=ReleaseDynamicARM -f makefile.px2 install
	project:
		chnage dir to "Phoenix\Phoenix\Projects\Client\General"
		make CFG=ReleaseDynamicARM -f makefile.px2	

linux/linuxARM copy fmod:		
	change dir to "Phoenix/trunk/Phoenix/ThirdPartiesLibs/"
	sudo cp -fr FMOD /usr/local/lib/ 
	sudo chmod 777 /usr/local/lib/FMOD

	change dir to /usr/local/lib/FMOD/linux/lib/x86
	sudo cp -f libfmod.9.so ../../../../
	
welcome to QQGroup:336273110