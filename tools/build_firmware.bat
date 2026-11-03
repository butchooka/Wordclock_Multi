@echo off
rem tools\build_firmware.bat - Wordclock_Multi: compiles the Arduino sketch for all languages and boards (double-click).
rem Uses the arduino-cli that comes with the Arduino IDE 2.x and its installed ESP32 board package (3.x for the C6).
rem Output: output\firmware\<board>_<language>_v<version>.bin  (full image, flash at 0x0)
rem         <version> = status of the language from line 2 of src\wc_lang_XX.h (v2.0 tested, v0.9 in test)
rem         output\firmware\app\<board>_<language>_v<version>_app.bin  (app only, flash at 0x10000)
rem Boards: ESP32   = generic ESP32 (ESP32 Dev Module, also fits the Wemos D1 mini ESP32)
rem         ESP32C6 = generic ESP32-C6 (ESP32C6 Dev Module, USB CDC On Boot, fits SuperMini / XIAO)
rem Only some languages:  build_firmware.bat DE GB scifi_NAV
rem The sketch folder itself is not changed: it is copied to %TEMP%, the language is set there via wc_build.h.
rem Data pin, current limit etc. come from config.h (LED_PIN default GPIO2).
setlocal EnableExtensions EnableDelayedExpansion
chcp 65001 >nul
cd /d "%~dp0.."
set "ROOT=%CD%"

set "SKETCH=%ROOT%\arduino\Wordclock"
set "OUT=%ROOT%\output\firmware"
set "WORK=%TEMP%\wc_firmware_build"
set "LOG=%OUT%\build_log.txt"

rem ---- boards: name and FQBN ----
set "B1_NAME=ESP32"
set "B1_FQBN=esp32:esp32:esp32:PartitionScheme=default"
set "B2_NAME=ESP32C6"
set "B2_FQBN=esp32:esp32:esp32c6:CDCOnBoot=cdc,PartitionScheme=default"
set "BOARDS=1 2"

rem ---- find arduino-cli (part of the Arduino IDE) ----
set "CLI="
for %%P in (
  "%LOCALAPPDATA%\Programs\Arduino IDE\resources\app\lib\backend\resources\arduino-cli.exe"
  "%ProgramFiles%\Arduino IDE\resources\app\lib\backend\resources\arduino-cli.exe"
  "%ProgramFiles(x86)%\Arduino IDE\resources\app\lib\backend\resources\arduino-cli.exe"
) do if not defined CLI if exist "%%~P" set "CLI=%%~P"
if not defined CLI for /f "delims=" %%P in ('where arduino-cli 2^>nul') do if not defined CLI set "CLI=%%P"
if not defined CLI (
  echo arduino-cli was not found. Install the Arduino IDE 2.x or put arduino-cli.exe into PATH.
  pause & exit /b 1
)
rem same settings as the IDE (sketchbook, libraries such as Adafruit NeoPixel for board package 2.0.x)
set "CFG="
if exist "%USERPROFILE%\.arduinoIDE\arduino-cli.yaml" set CFG=--config-file "%USERPROFILE%\.arduinoIDE\arduino-cli.yaml"

rem ---- firmware version from src\wc_core.h (fallback if a language file has no version) ----
set "VER="
for /f "tokens=3" %%V in ('findstr /b /c:"#define WC_VERSION" "%SKETCH%\src\wc_core.h"') do set "VER=%%~V"
if not defined VER set "VER=0.0"

rem ---- language list: arguments or all src\wc_lang_*.h ----
set "LANGS=%*"
if not defined LANGS (
  for %%F in ("%SKETCH%\src\wc_lang_*.h") do (
    set "N=%%~nF"
    set "LANGS=!LANGS! !N:wc_lang_=!"
  )
)

rem ---- temporary copy of the sketch ----
if not exist "%OUT%\app" mkdir "%OUT%\app"
robocopy "%SKETCH%" "%WORK%\Wordclock" /MIR /XD firmware build /NFL /NDL /NJH /NJS /NP >nul
if errorlevel 8 (echo Copying the sketch to %WORK% failed. & pause & exit /b 1)

> "%LOG%" echo Wordclock_Multi firmware build v%VER% - %date% %time%
>>"%LOG%" echo arduino-cli: %CLI%
>>"%LOG%" echo Languages:%LANGS%
echo arduino-cli: %CLI%
echo Version v%VER%, languages:%LANGS%
echo Output: %OUT%
echo.

set /a OK=0, FAIL=0
set "FAILED="
for %%B in (%BOARDS%) do (
  set "BN=!B%%B_NAME!"
  set "BF=!B%%B_FQBN!"
  for %%L in (%LANGS%) do call :build "!BN!" "!BF!" "%%L"
)

>>"%LOG%" echo.
>>"%LOG%" echo Result: %OK% ok, %FAIL% failed %FAILED%
echo.
echo Result: %OK% ok, %FAIL% failed %FAILED%
echo Log: %LOG%
pause
exit /b %FAIL%

rem ---------------------------------------------------------------------------------------------
:build
set "BNAME=%~1"
set "FQBN=%~2"
set "LC=%~3"
set "LF=%WORK%\Wordclock\src\wc_lang_%LC%.h"
if not exist "%LF%" (
  echo [skip]  %BNAME%_%LC%  - src\wc_lang_%LC%.h does not exist
  >>"%LOG%" echo [skip] %BNAME%_%LC% - language file missing
  set /a FAIL+=1 & set "FAILED=%FAILED% %BNAME%_%LC%"
  exit /b
)
rem version of the language: last word of the header line "wc_lang_XX.h - ..., v0.9"
set "LHEAD="
set "LV="
for /f "delims=" %%A in ('findstr /c:"wc_lang_%LC%.h - " "%LF%"') do if not defined LHEAD set "LHEAD=%%A"
if defined LHEAD for %%T in (!LHEAD!) do set "LV=%%T"
if defined LV if /i "!LV:~0,1!"=="v" (set "LV=!LV:~1!") else set "LV="
if not defined LV set "LV=%VER%"
set "NAME=%BNAME%_%LC%_v%LV%"
> "%WORK%\Wordclock\wc_build.h" echo #pragma once
>>"%WORK%\Wordclock\wc_build.h" echo #define WC_LANG_FILE "src/wc_lang_%LC%.h"
set "BP=%WORK%\build_%BNAME%"
<nul set /p "=[build] %NAME% ... "
>>"%LOG%" echo.
>>"%LOG%" echo ===== %NAME%  (%FQBN%) =====
"%CLI%" %CFG% compile --fqbn "%FQBN%" --build-path "%BP%" "%WORK%\Wordclock" >>"%LOG%" 2>&1
if errorlevel 1 (
  echo FAILED
  set /a FAIL+=1 & set "FAILED=%FAILED% %NAME%"
  exit /b
)
if exist "%BP%\Wordclock.ino.merged.bin" (
  copy /y "%BP%\Wordclock.ino.merged.bin" "%OUT%\%NAME%.bin" >nul
) else (
  rem board package without merged image: only the app is available
  copy /y "%BP%\Wordclock.ino.bin" "%OUT%\%NAME%.bin" >nul
  >>"%LOG%" echo note: no merged.bin, %NAME%.bin is the app only (flash at 0x10000)
)
copy /y "%BP%\Wordclock.ino.bin" "%OUT%\app\%NAME%_app.bin" >nul
echo ok
set /a OK+=1
exit /b
