@echo off
rem tools\render_fronts.bat - Wordclock_Multi v2.0: preview images of the fronts of all languages (double-click).
rem Needs only Python 3 (python.org, option "Add python.exe to PATH"); Pillow is installed automatically.
rem Without g++ the lit words come from tools\render_masks.json.xz (kept up to date by tools\make_masks.py).
rem Result: docs\render\ (light front) and docs\render\dark\ (dark front), one image per
rem language plus an overview Wordclock_Render_v2.0_ALL_1022.png.
rem Other time/colour: change the line "set OPTS=" below, e.g. set OPTS=--time 13:47 --color green --features
chcp 65001 >nul
setlocal
cd /d "%~dp0.."
set PYTHONIOENCODING=utf-8
set "OPTS="
set "PY="
where py >nul 2>nul && set "PY=py -3"
if not defined PY where python >nul 2>nul && set "PY=python"
if not defined PY goto nopython

%PY% -c "import PIL" >nul 2>nul || %PY% -m pip install --user pillow
echo Light fronts ...
%PY% tools\render_fronts.py %OPTS%
echo.
echo Dark fronts ...
%PY% tools\render_fronts.py --style dark --out docs\render\dark %OPTS%
echo.
echo Images in docs\render\ and docs\render\dark\
pause
exit /b 0

:nopython
echo Python 3 was not found.
echo Install it from https://www.python.org and tick "Add python.exe to PATH" during the installation.
pause
exit /b 1
