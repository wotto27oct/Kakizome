@echo off
setlocal

gcc -std=c99 -o kakizome kakizome.c

REM == main function
echo === basic ===
call :runtest 0 0
call :runtest 1 1
call :runtest 19 19
call :runtest "1 2 3" "1 2 3"

echo === arithmetic operators ===
call :runtest "+ 1 2" 3
call :runtest "+ 10 20" 30
call :runtest "- 5 2" 3
call :runtest "* 2 4" 8
call :runtest "/ 121 11" 11 
call :runtest "+++1 2 3 4" 10
call :runtest "+ 1 + 2 + 3 4" 10
call :runtest "+ 3 * 5 6" 33

echo === functions ===
call :runtest "F[+ a a] F(1)" 2
call :runtest "F[* a 2] F(7)" 14
call :runtest "F[* a a] F(F(3))" 81
call :runtest "F[* a a] F(F(F(F(2))))" 65536
call :runtest "F[- a 2] G[* F(- a 1) 3] G(1)" -6

call :runtest "F[* a b] F(29 3)" 87

echo === built-in function ===
call :runtest "P(5)" 5

exit /b

REM == function "runtest"
:runtest
for /F "usebackq delims= " %%a in (`kakizome.exe %1`) do set output=%%a
if not %output% == %2 (
	echo %1: %2 expected, but got %output%
	exit /B
) 
echo %1 =^> %output%

exit /b
