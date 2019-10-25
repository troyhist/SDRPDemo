@echo off
echo.
echo SDRPDEMO ver. 1.0 (05.11.2002)
if %1.==. goto nocom
echo !A_SRC ..\ SDRPDEMO %1 ..\AutoBuild.h !exclude.txt C:\Kolevatov\BACKUP
echo.
echo !A_SRC ..\ SDRPDEMO %1 ..\AutoBuild.h !exclude.txt C:\Kolevatov\BACKUP %2
if %2.==.     call !A_SRC ..\ SDRPDEMO %1 ..\AutoBuild.h !exclude.txt C:\Kolevatov\BACKUP
if not %2.==. call !A_SRC ..\ SDRPDEMO %1 ..\AutoBuild.h !exclude.txt C:\Kolevatov\BACKUP %2
goto end
:nocom
echo Type Build number !!! Ex: !makeres 10
:end
