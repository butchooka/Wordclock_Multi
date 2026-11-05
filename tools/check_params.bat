@echo off
rem tools\check_params.bat - Wordclock_Multi v2.0: compares the parameters of the SCAD files with the FreeCAD macros
rem (double-click). Same name must have the same value, options must be in the Customizer list, nothing one-sided.
rem Needs Python 3 only (no OpenSCAD / FreeCAD, takes about a second). Result: output\check_params_log.txt.
rem (models\ is private - not part of the GitHub repository.)
rem Options in the line "set OPTS=" below:
rem   --verbose  also list the equal parameters and the known one-sided ones
chcp 65001 >nul
setlocal
cd /d "%~dp0.."
if not exist models\Wordclock_Model.scad (echo models\ not found - the 3D models are not part of this repository. & pause & exit /b 1)
set PYTHONIOENCODING=utf-8
set "OPTS="
set "PY="
where py >nul 2>nul && set "PY=py -3"
if not defined PY where python >nul 2>nul && set "PY=python"
if not defined PY goto nopython

if not exist output mkdir output
set "LOG=%CD%\output\check_params_log.txt"
%PY% tools\check_params.py %OPTS% --log "%LOG%"
echo.
echo Log saved: %LOG%
pause
exit /b 0

:nopython
echo Python 3 was not found.
echo Install it from https://www.python.org and tick "Add python.exe to PATH" during the installation.
pause
exit /b 1
