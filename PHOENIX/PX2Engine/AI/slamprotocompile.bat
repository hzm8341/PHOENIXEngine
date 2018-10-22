@echo off

..\\..\\..\\Tools\\protoc -I=./ --cpp_out=./ ./slam.proto

pause