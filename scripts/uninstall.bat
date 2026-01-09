@echo off
set APP_NAME=quit-playing-tarkov.exe
set REG_KEY=QuitPlayingTarkov

echo [?] Starting system cleanup...
echo.

taskkill /F /IM %APP_NAME% /T
reg delete "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run" /v %REG_KEY% /f

echo.
echo [!] Cleanup completed successfully!
echo.
echo [+] Your system is now completely free of this application.
echo [+] You can safely delete this folder now.
pause