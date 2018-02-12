@echo off

:: SVN
cd ..
svn update

:: PHOENIX
cd ./Achieve

rd PHOENIX /s /q
mkdir PHOENIX

::PHONEIXEngine
XCOPY ..\Bin\AppPlayerOpenGL.exe PHOENIX\ /s
XCOPY ..\Bin\PX2EngineOpenGL.dll PHOENIX\ /s
XCOPY ..\Bin\fmod.dll PHOENIX\ /s
XCOPY ..\Bin\awesomium.dll PHOENIX\ /s
XCOPY ..\Bin\Data\boost.list PHOENIX\Data\ /s
XCOPY ..\Bin\Data\boost.lua PHOENIX\Data\ /s
XCOPY ..\Bin\Data\boost.xml PHOENIX\Data\ /s
XCOPY ..\Bin\Data\engine\* PHOENIX\Data\engine\ /s
XCOPY ..\Bin\Data\engine_mtls\* PHOENIX\Data\engine_mtls\ /s
XCOPY ..\Bin\Data\Chaos\* PHOENIX\Data\Chaos\ /s

XCOPY ..\Bin\LauncherOpenGL.exe PHOENIX\ /s
XCOPY ..\Bin\DataLauncher\* PHOENIX\DataLauncher\ /s

XCOPY ..\Bin\Data\LPlugin\LPluginOpenGL.dll PHOENIX\Data\LPlugin\ /s
XCOPY ..\Bin\Data\Blockly\BlocklyOpenGL.dll PHOENIX\Data\Blockly\ /s
XCOPY ..\Bin\Data\Snap\SnapOpenGL.dll PHOENIX\Data\Snap\ /s

::PHONEIXFrame
XCOPY ..\PHOENIXFrame\* PHOENIX\PHOENIXFrame\* /s

set fDate=%date:~0,4%%date:~5,2%%date:~8,2%
set bTime=%TIME:~0,2%%TIME:~3,2%%TIME:~6,2%
.\7z.exe a -t7z .\PHOENIX_%fDate%_%bTime%.7z  .\PHOENIX\* -r 

pause