@echo off

rem Copyright 2025 Aleksandr Bocharov
rem Distributed under the Boost Software License, Version 1.0.
rem See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
rem 2025-03-10
rem https://github.com/Aleksandr3Bocharov/RefalAB

rem *******************************************************************
rem refxcv.bat
rem special script
rem compile xcv.ref from refal to GNU-assembler + assembling
rem result: xcv.o  
rem *******************************************************************

bin\RefalAB src\inter\xcv > src\inter\xcv.log
as -o src\inter\xcv.o src\inter\xcv.s >> src\inter\xcv.log 
