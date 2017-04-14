windows compile£ºdecompile ThirdPartiesLibs.zip compile Phoenix.sln

linux copyFMOD:
enter->Phoenix/trunk/Phoenix/ThirdPartiesLibs/
sudo cp -fr FMOD /usr/local/lib/ 
sudo chmod 777 /usr/local/lib/FMOD

enter->/usr/local/lib/FMOD/linux/lib/x86
sudo cp -f libfmod.9.so ../../../../

linux compile: make CFG=ReleaseDynamic -f makefile.px2
linux install: sudo make CFG=ReleaseDynamic -f makefile.px2 install