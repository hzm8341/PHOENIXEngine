::@echo off

@echo cmd = %0%
@echo pathname = %1%

.\7z.exe a -t7z ./projectuploading.7z  ./Data/%1%/* -r