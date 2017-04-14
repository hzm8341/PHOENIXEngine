@echo off

: dir
cd /d %cd%
del "PX2EditorToLua.cpp"
: tolua
.\tolua++.exe -n PX2Editor -o PX2EditorToLua.cpp PX2EditorToScript.pkg

pause