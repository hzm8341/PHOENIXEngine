@echo off

: dir
cd /d %cd%
del "BlockToLua.cpp"
: tolua
.\tolua++.exe -n Block -o BlockToLua.cpp BlockToScript.pkg

copy BlockToLua.cpp ..\\

pause