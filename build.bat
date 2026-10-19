@echo off
chcp 65001 >nul
echo Компиляция DiscordSoundSwitcher...
g++ -std=c++17 -O2 main.cpp -o DiscordSoundSwitcher.exe -lshell32 -lwininet
if %ERRORLEVEL% EQU 0 (
    echo [✔] Успешно скомпилировано в DiscordSoundSwitcher.exe!
) else (
    echo [X] Ошибка компиляции!
)
pause
