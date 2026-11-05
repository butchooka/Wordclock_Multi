@echo off
rem tools\bundle_models.bat - Wordclock_Multi v2.0: single-file versions of the models, e.g. for MakerWorld (double-click).
rem Inserts the shared parts (Wordclock_Common.scad / Wordclock_Common.py) and for OpenSCAD also the language files
rem (models\lang\) into Wordclock_Model.scad, Wordclock_Model_PictureFrame.scad and both FCMacros.
rem Result: models\export\bundle\ (same file names). Needs Python 3 only, takes about a second.
rem (models\ is private - not part of the GitHub repository.)
chcp 65001 >nul
setlocal
cd /d "%~dp0.."
if not exist models\Wordclock_Common.scad (echo models\ not found - the 3D models are not part of this repository. & pause & exit /b 1)
set PYTHONIOENCODING=utf-8
set "PY="
where py >nul 2>nul && set "PY=py -3"
if not defined PY where python >nul 2>nul && set "PY=python"
if not defined PY goto nopython

%PY% tools\bundle_models.py
echo.
pause
exit /b 0

:nopython
echo Python 3 was not found.
echo Install it from https://www.python.org and tick "Add python.exe to PATH" during the installation.
pause
exit /b 1
