@echo off
:: Check administrative rights
net session > nul 2>&1
if %errorlevel% == 0 (
	goto INIT
) else (
	echo Error: Please run as administrator.
	exit /b
)
:INIT
:: Search for VICODaemon.exe within processes
tasklist /fi "ImageName eq VICODaemon.exe" | find /i "VICODaemon.exe" > nul 2>&1
:: If the process is running, stop it. Else, start.
if %errorlevel% == 0 (
	echo VICODaemon is currently running.
	goto STOP
) else (
	goto START
)
:STOP
echo Stopping VICODaemon...
:: Stop VICODaemon process
net stop VICODaemon > nul 2>&1
:: Delete VICODaemon service
sc delete VICODaemon > nul 2>&1
:: Kill VICODaemon task, if the process couldn't be stopped
taskkill /im "VICODaemon.exe" /t /f > nul 2>&1
:: Jump back to INIT to check if all VICODaemon processes are stopped.
goto INIT
:START
echo Starting VICODaemon...
:: Create VICODaemon service
sc create VICODaemon binPath= "%~dp0VICODaemon.exe --backend windows" start= auto displayname= "KETEK VICODaemon" > nul 2>&1
:: Define VICODaemon service description
sc description VICODaemon "The VICODaemon service manages all communication between host and KETEK hardware." > nul 2>&1
:: Start VICODaemon service
net start VICODaemon  > nul 2>&1
echo Finished.
exit /b