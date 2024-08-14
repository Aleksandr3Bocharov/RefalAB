@echo off
rem *******************************************************************
rem r2clg_dbg.bat
rem	compile from refal to GNU-assembler + link + go
rem 	arg: %1 - name of refal programm (without ext ref)
rem	result: running of %1.exe 
rem
rem Copyright(C) Aleksandr Bocharov
rem Author : Aleksandr Bocharov
rem Date : 05.08.2024
rem *******************************************************************

set CC=F:\Programming\mingw32\bin

bin\refal2 %1 > %1.log
%CC%\as -o %1.o %1.asm >> %1.log
%CC%\gcc -o %1.exe lib\mainrf.o %1.o -Wl,-L.\lib -Wl,-lr2_dbg >> %1.log
%1.exe
