@echo off

set filename=%1
g++ -finput-charset=UTF-8 -fexec-charset=gbk -shared -g %filename% -o %filename%.dll