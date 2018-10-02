@echo off

: dir
cd /d %cd%
del "PX2NirvanaToLua.cpp"
: tolua
tolua++.exe -n Nirvana -o PX2NirvanaToLua.cpp PX2ToScript.pkg

copy PX2NirvanaToLua.cpp ..\\

pause