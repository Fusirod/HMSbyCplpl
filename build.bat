@echo off
echo Dang bien dich source code...
g++ main.cpp -o HMS.exe
if %ERRORLEVEL% EQU 0 (
    echo Bien dich thanh cong! File chay: HMS.exe
) else (
    echo Co loi xay ra trong qua trinh bien dich!
)
