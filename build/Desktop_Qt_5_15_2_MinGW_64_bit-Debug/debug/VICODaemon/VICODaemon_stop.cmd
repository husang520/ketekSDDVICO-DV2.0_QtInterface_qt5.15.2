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
:: If the process is running, stop it. Else, finish.
if %errorlevel% == 0 (
	echo VICODaemon is currently running.
	goto STOP
) else (
	echo Finished.
	exit /b
)
:STOP
echo Stopping VICODaemon...
:: Stop VICODaemon process
net stop VICODaemon > nul 2>&1
:: Delete VICODaemon service
sc delete VICODaemon > nul 2>&1
:: Kill VICODaemon task, if the process couldn't be stopped
taskkill /im "VICODaemon.exe" /t /f > nul 2>&1
:: Jump back to INIT to check if all VICODaemon processes are stopped. If parameter is stop, finish.
goto INIT