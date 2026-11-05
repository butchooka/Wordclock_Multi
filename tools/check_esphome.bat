@echo off
rem tools\check_esphome.bat - Wordclock_Multi v2.0: checks the ESPHome configuration of all languages (double-click).
rem Step 1 (Python only, a second): every lang_XX.yaml is valid YAML, all values are strings (Off / No / NO / Yes
rem        unquoted = bool -> "Must be string, got <class 'bool'>"), options of a select are unique.
rem Step 2 (only if ESPHome is installed: pip install esphome): "esphome config" for every language, validates
rem        the complete configuration with dummy secrets (no compile, approx. 5 s per language).
rem Result: output\check_esphome_log.txt, full ESPHome output per language in output\esphome_check\<code>.txt
rem Only some languages:  check_esphome.bat GB NO
rem Options in the line "set OPTS=" below:
rem   --no-esphome  only step 1     --esphome  step 2 required (error if ESPHome is missing)
chcp 65001 >nul
setlocal
cd /d "%~dp0.."
set PYTHONIOENCODING=utf-8
set "OPTS="
set "PY="
where py >nul 2>nul && set "PY=py -3"
if not defined PY where python >nul 2>nul && set "PY=python"
if not defined PY goto nopython

if not exist output mkdir output
set "LOG=%CD%\output\check_esphome_log.txt"
%PY% tools\check_esphome.py %OPTS% --log "%LOG%" %*
echo.
echo Log saved: %LOG%
pause
exit /b 0

:nopython
echo Python 3 was not found.
echo Install it from https://www.python.org and tick "Add python.exe to PATH" during the installation.
pause
exit /b 1
