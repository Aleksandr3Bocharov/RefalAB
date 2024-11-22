@echo off

rem Copyright 2024 Aleksandr Bocharov
rem Distributed under the Boost Software License, Version 1.0.
rem See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
rem 2024-11-23
rem https://github.com/Aleksandr3Bocharov/RefalAB

rem *******************************************************************
rem RefalABclg.bat
rem compile from refal to GNU-assembler + link + go
rem arg: %1 - name of refal programm (without ext ref)
rem result: running of %1.exe 
rem *******************************************************************

bin\RefalAB %1 > %1.log
as -o %1.o %1.asm >> %1.log
clang -o %1.exe %1.o lib\mainrf.o -Llib -lRefalAB >> %1.log
%1.exe
