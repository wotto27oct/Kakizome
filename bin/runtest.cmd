@echo off
setlocal

gcc -std=c99 -o kakizome kakizome.c

REM == main function
call :runtest 0 0
call :runtest 1 1
exit /b 

REM == function "runtest"
:runtest
for /F "usebackq delims=" %%a in (`kakizome.exe %1`) do set output=%%a
if not %output% == %2 (
	echo %1: %2 expected, but got %output%
	exit /B
) 
echo %1 =^> %output%

exit /b
