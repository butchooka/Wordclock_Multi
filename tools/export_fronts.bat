@echo off
rem tools\export_fronts.bat - Wordclock 16x16, v2.0
rem Exports the front of EVERY language (models\lang\lang_XX.scad) with OpenSCAD as STL into the folder
rem models\export (Front from Wordclock_Model.scad and/or PictureFrame from Wordclock_Model_PictureFrame.scad,
rem see PARTS). Double-click, or run in cmd. Settings below. (FreeCAD: LANG = "ALL" in the macro.)
setlocal enabledelayedexpansion

rem ---- settings ----
set OPENSCAD=C:\Program Files\OpenSCAD\openscad.exe
rem Front = front of the own case, PictureFrame = front plate for the 25 cm picture frame (IKEA SANNAHED / RIBBA), Both = both
set PARTS=Front
rem Liberation, Arial, DejaVu (as FONT in the Customizer)
set FONT=Liberation
rem Vorschau, Normal, Fein (as QUALITY in the model)
set QUALITY=Fein
rem extra options, e.g. --backend=Manifold (OpenSCAD 2024/2025, much faster)
set OPTS=
rem ------------------

set VERSION=v2.0
set LIST=%PARTS%
if /i "%PARTS%"=="Both" set LIST=Front PictureFrame
set FONTTAG=LiberationSansBold
if /i "%FONT%"=="Arial" set FONTTAG=ArialBold
if /i "%FONT%"=="DejaVu" set FONTTAG=DejaVuSansBold

cd /d "%~dp0..\models"
if not exist "%OPENSCAD%" (
  echo OpenSCAD not found: %OPENSCAD%  - adjust OPENSCAD at the top of this file.
  pause
  exit /b 1
)
if not exist export mkdir export
for %%p in (%LIST%) do (
  for %%f in (lang\lang_*.scad) do (
    set N=%%~nf
    set L=!N:lang_=!
    if /i not "!L!"=="all" (
      set OUT=export\Wordclock_%%p_%VERSION%_!L!_%FONTTAG%.stl
      echo !L!  -^>  !OUT!
      if /i "%%p"=="PictureFrame" (
        "%OPENSCAD%" %OPTS% -o "!OUT!" -D "LANG=\"!L!\"" -D "FONT=\"%FONT%\"" -D "QUALITY=\"%QUALITY%\"" -D "PRINT_ORIENT=true" Wordclock_Model_PictureFrame.scad
      ) else (
        "%OPENSCAD%" %OPTS% -o "!OUT!" -D "LANG=\"!L!\"" -D "PART=\"%%p\"" -D "FONT=\"%FONT%\"" -D "QUALITY=\"%QUALITY%\"" -D "PRINT_ORIENT=true" Wordclock_Model.scad
      )
    )
  )
)
echo.
echo Done, files in %CD%\export
echo (Languages with their own font, e.g. Korean, get the name of that font in the console output of OpenSCAD.)
pause
