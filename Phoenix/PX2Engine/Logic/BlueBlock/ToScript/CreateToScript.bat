@echo off

: dir
cd /d %cd%
del "PX2BBlueBlockToLua.cpp"
: tolua
tolua++.exe -n BBlocks -o PX2BBlueBlockToLua.cpp PX2ToScript.pkg

copy PX2BBlueBlockToLua.cpp ..\\

..\\..\\..\\..\\..\\Bin\\PkgParser.exe PX2ToScript.pkg pkg.cpp
xcopy /DY pkg.xml ..\\..\\..\\..\\..\\Bin\\Data\\BlueBlock\\pkg

pause