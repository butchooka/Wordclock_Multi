@echo off
rem tools\bundle_firmware.bat - Wordclock_Multi v2.0: firmware as single files per language, e.g. for MakerWorld (double-click).
rem ESPHome: wordclock_multi_XX.yaml (main file + core + language as inline packages) + wordclock_multi_XX.h (all C++).
rem Arduino: Wordclock_XX\Wordclock_XX.ino (config.h inserted, language fixed) + wordclock_bundle.h (all C++).
rem Result: output\makerworld\ (esphome\, arduino\, README.txt, Wordclock_ESPHome.zip, Wordclock_Arduino.zip).
rem Only some languages:  bundle_firmware.bat DE GB dialect_BAD
rem Needs Python 3 only, takes about a second. Run tools\sync_src.py first if a .h file was changed.
chcp 65001 >nul
setlocal
cd /d "%~dp0.."
set PYTHONIOENCODING=utf-8
set "PY="
where py >nul 2>nul && set "PY=py -3"
if not defined PY where python >nul 2>nul && set "PY=python"
if not defined PY goto nopython

%PY% tools\bundle_firmware.py %*
echo.
pause
exit /b 0

:nopython
echo Python 3 was not found.
echo Install it from https://www.python.org and tick "Add python.exe to PATH" during the installation.
pause
exit /b 1
