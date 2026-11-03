@echo off
rem tools\check_languages.bat - Wordclock_Multi v2.0: checks all languages (double-click) and updates docs\languages\
rem and docs\setup\ (tools\make_info.py, only files there are written, no language file is changed).
rem Result: output\check_log.txt. Needs Python 3 (python.org, option "Add python.exe to PATH").
rem Filler check and docs\languages\LANG_XX.txt need g++: winget install BrechtSanders.WinLibs.POSIX.UCRT (then new window).
chcp 65001 >nul
setlocal
cd /d "%~dp0.."
set PYTHONIOENCODING=utf-8
set "PY="
where py >nul 2>nul && set "PY=py -3"
if not defined PY where python >nul 2>nul && set "PY=python"
if not defined PY goto nopython

if not exist output mkdir output
set "LOG=%CD%\output\check_log.txt"
> "%LOG%" echo Wordclock_Multi - language check %date% %time%
where g++ >nul 2>nul || >>"%LOG%" echo NOTE: no g++ found - fillers not checked, docs\languages\LANG_XX.txt not rewritten.
where g++ >nul 2>nul || >>"%LOG%" echo       Install: winget install BrechtSanders.WinLibs.POSIX.UCRT
>>"%LOG%" echo.
>>"%LOG%" echo Pack the web interface - tools\make_webpage.py
%PY% tools\make_webpage.py >>"%LOG%" 2>&1
>>"%LOG%" echo.
>>"%LOG%" echo Script variants of the fronts - tools\make_variants.py
%PY% tools\make_variants.py >>"%LOG%" 2>&1
>>"%LOG%" echo.
>>"%LOG%" echo Check all languages - tools\check_lang.py
%PY% tools\check_lang.py >>"%LOG%" 2>&1
if errorlevel 1 (set "RES=ERRORS FOUND - see the lines with ERROR above") else (set "RES=ALL OK")
>>"%LOG%" echo.
>>"%LOG%" echo Update docs\languages and docs\setup - tools\make_info.py
%PY% tools\make_info.py >>"%LOG%" 2>&1
>>"%LOG%" echo.
>>"%LOG%" echo Result: %RES%
type "%LOG%"
echo.
echo Log saved: %LOG%
pause
exit /b 0

:nopython
echo Python 3 was not found.
echo Install it from https://www.python.org and tick "Add python.exe to PATH" during the installation.
pause
exit /b 1
