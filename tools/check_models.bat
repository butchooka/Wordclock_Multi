@echo off
rem tools\check_models.bat - Wordclock_Multi v2.0: checks the 3D models (double-click). Needs Python 3 and OpenSCAD.
rem Renders every part of Wordclock_Model.scad and Wordclock_Model_PictureFrame.scad and reports render errors,
rem model warnings, loose bodies, open meshes, wrong print orientation and changes since the last saved state.
rem Result: output\check_models_log.txt. (models\ is private - not part of the GitHub repository.) OpenSCAD 2024/2025 (Manifold) needs about a minute,
rem OpenSCAD 2021 several minutes.
rem Options in the line "set OPTS=" below:
rem   --quick    without front and PictureFrame        --fit      holders / back / front must not overlap
rem   --freecad  compare with Wordclock_Model.FCMacro (FreeCAD 1.x, freecadcmd is searched automatically)
rem   --update   save the current state as the new reference (after an intended change)
chcp 65001 >nul
setlocal
cd /d "%~dp0.."
if not exist models\check_models.py (echo models\check_models.py not found - the 3D models are not part of this repository. & pause & exit /b 1)
set PYTHONIOENCODING=utf-8
set "OPTS=--fit --freecad"
set "PY="
where py >nul 2>nul && set "PY=py -3"
if not defined PY where python >nul 2>nul && set "PY=python"
if not defined PY goto nopython

if not exist output mkdir output
set "LOG=%CD%\output\check_models_log.txt"
%PY% models\check_models.py %OPTS% --log "%LOG%"
echo.
echo Log saved: %LOG%
pause
exit /b 0

:nopython
echo Python 3 was not found.
echo Install it from https://www.python.org and tick "Add python.exe to PATH" during the installation.
pause
exit /b 1
