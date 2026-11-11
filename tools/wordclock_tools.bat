@echo off
rem tools\wordclock_tools.bat - Wordclock_Multi v1.0: all tools in one menu (double-click).
rem Choose an action by its number, A runs all of them one after another in a sensible order.
rem Direct call without menu:  wordclock_tools.bat 5      or      wordclock_tools.bat A
rem Unchanged outputs are skipped (5, 9, 10, 12-14, 16: info file with the base data next to the outputs, see
rem tools\wc_stamp.py). Build everything again: second argument F, e.g.  wordclock_tools.bat A F
rem Needs Python 3 (python.org, option "Add python.exe to PATH"). Logs go to tools\logs\, after every action
rem tools\clean.py removes caches and temporary files (__pycache__, build folders in %%TEMP%%, ...).
rem B (Backup clean) also removes the generated STL/3MF/zips/fonts - all can be rebuilt with the menu.
rem Actions 3, 4, 8, 9, 10, 12, 13, 14, 15, 16 need the private folder models\ (not part of the GitHub repository).
chcp 65001 >nul
setlocal EnableExtensions
cd /d "%~dp0.."
set "ROOT=%CD%"
set PYTHONIOENCODING=utf-8
set PYTHONDONTWRITEBYTECODE=1
set WC_NOPAUSE=1
set "PY="
where py >nul 2>nul && set "PY=py -3"
if not defined PY where python >nul 2>nul && set "PY=python"
if not defined PY goto nopython
if not exist tools\logs mkdir tools\logs
rem titles of the actions (shown while they run)
set "T1=Check languages"
set "T2=Check ESPHome"
set "T3=Check parameters SCAD vs. FreeCAD"
set "T4=Check 3D models"
set "T5=Render fronts"
set "T6=Bundle firmware"
set "T8=Bundle models"
set "T9=Export fronts STL"
set "T10=Export PictureFrame STL"
set "T11=Mask cache"
set "T12=Bambu 3MF per language"
set "T13=Bambu 3MF with all fronts"
set "T14=Export parts STL"
set "T15=Fonts check / install"
set "T16=Bambu 3MF PictureFrame"

if /i "%~2"=="F" set "WC_FORCE=1"
if not "%~1"=="" (
  set "SEL=%~1"
  set "ONCE=1"
  goto run
)

:menu
cls
echo  Wordclock_Multi - tools                                           (logs in tools\logs\)
echo  ---------------------------------------------------------------------------------------------
echo   1  Check languages     sync C++ to ESPHome, pack web page, check all languages, update
echo                          docs\languages, setup guides (.md), language lists in README/config.h/YAML
echo   2  Check ESPHome       all lang_XX.yaml, with ESPHome installed also "esphome config"
echo   3  Check parameters    SCAD ^<-^> FreeCAD macro settings (models, Python only)
echo   4  Check 3D models     render all parts with OpenSCAD, fit check, FreeCAD comparison
echo   5  Render fronts       preview images light/dark, normal + _full, overview, GIFs, ticker -^> docs\render*
echo   6  Bundle firmware     single-file versions -^> esphome\ + arduino\single_Language, zips -^> _private\makerworld
echo   8  Bundle models       single-file SCAD/FCMacro -^> _private\makerworld\models
echo   9  Export fronts       STL of the case front, all languages -^> _private\makerworld\export (slow)
echo  10  Export PictureFrame STL of the picture frame plate, all languages and frames (RIBBA, SANNAHED)
echo                          -^> _private\makerworld\export (slow)
echo  11  Mask cache          rebuild tools\render_masks.json.xz after a language change (needs g++)
echo  12  Bambu 3MF           one Bambu Studio project per language from tools\template_P2S.3mf
echo                          -^> _private\makerworld\export_3mf (exports missing STL first)
echo  13  Bambu 3MF all       one Bambu Studio project with all fronts (one plate each) -^> export_3mf
echo  14  Export parts        STL of rear, holders and their supports -^> _private\makerworld\export
echo  15  Fonts               check the fonts of the fronts (CN, JP, KR, runes), download and install
echo                          missing ones for all users (asks for administrator rights)
echo  16  Bambu 3MF PictureFrame  one project per language and frame (RIBBA, SANNAHED) from the front
echo                          of tools\template_P2S.3mf -^> export_3mf (exports missing STL first)
echo   P  PictureFrame other  special case: asks size, depth, ... of another picture frame and exports
echo                          the plates -^> _private\makerworld\export\custom
echo   A  All                15 1 2 3 4 5 6 8 9 10 14 12 16 one after another
echo   C  Clean              remove caches and temporary files only
echo   B  Backup clean       also remove generated STL/3MF/zips/fonts (slim folder for a manual backup,
echo                          only git-ignored outputs, lists first and asks; rebuild with 6, 8-10, 12-16)
echo   Q  Quit
echo   Unchanged outputs are skipped (5, 9, 10, 12-14, 16); all again: wordclock_tools.bat 9 F  (or A F)
echo.
set "SEL="
set /p "SEL=Choice: "
if not defined SEL goto menu

:run
if /i "%SEL%"=="Q" exit /b 0
if /i "%SEL%"=="A" goto all
if /i "%SEL%"=="C" goto clean_only
if /i "%SEL%"=="B" goto clean_backup
if /i "%SEL%"=="P" goto pf_custom
call :do %SEL%
goto finish

:all
set "T0=%time%"
set "NALL=0"
for %%N in (15 1 2 3 4 5 6 8 9 10 14 12 16) do (
  set /a NALL+=1
  call :do %%N
)
set "NALL="
echo.
echo All actions done (started %T0%, finished %time%). Logs: tools\logs\
goto finish

:pf_custom
rem special case: front plate for another picture frame (values of Wordclock_Model_PictureFrame.scad)
if not exist models\Wordclock_Model_PictureFrame.scad (echo skipped: models\ not found & goto finish)
echo.
echo  PictureFrame for another picture frame - Enter keeps the value in brackets
set "PF_SIZE=231" & set "PF_DEPTH=38" & set "PF_THICK=2" & set "PF_GLASS=0"
set "PF_MOUNT=SCREW" & set "PF_LANG=DE" & set "PF_FONT=Liberation" & set "PF_QUAL=Fine"
set /p "PF_SIZE=  Picture size = glass size, mm (220...300)  [%PF_SIZE%]: "
set /p "PF_DEPTH=  Inner depth of the frame, mm (22...80)     [%PF_DEPTH%]: "
set /p "PF_THICK=  Thickness of the printed plate, mm (1...4)         [%PF_THICK%]: "
set /p "PF_GLASS=  original Glass in front of the plate, mm (0 = none) [%PF_GLASS%]: "
set /p "PF_MOUNT=  Fastening SCREW / THIMBLES / NONE          [%PF_MOUNT%]: "
set /p "PF_LANG=  Languages (e.g. DE GB, ALL = all)          [%PF_LANG%]: "
set /p "PF_FONT=  Font Liberation / Arial / DejaVu (CN, JP, KR, runes: own font) [%PF_FONT%]: "
set /p "PF_QUAL=  Quality Preview / Normal / Fine            [%PF_QUAL%]: "
set "PF_L=--lang %PF_LANG%"
if /i "%PF_LANG%"=="ALL" set "PF_L="
set "TT=PictureFrame other"
%PY% tools\export_fronts.py PictureFrame %PF_L% --font %PF_FONT% --quality %PF_QUAL% --size %PF_SIZE% --depth %PF_DEPTH% --thickness %PF_THICK% --glass %PF_GLASS% --mount %PF_MOUNT%
call :done P
goto finish

:clean_only
%PY% tools\clean.py
goto finish

:clean_backup
rem slim folder for a manual backup: caches + large generated outputs (never files tracked by git)
%PY% tools\clean.py --backup --dry
echo.
set "OK="
set /p "OK=Remove these files? (Y/N): "
if /i not "%OK%"=="Y" (echo nothing removed & goto finish)
%PY% tools\clean.py --backup --quiet
goto finish

:finish
echo.
if defined ONCE exit /b 0
pause
goto menu

rem ---------------------------------------------------------------------------------------------
:do
call set "TT=%%T%~1%%"
echo.
echo =============================================================================================
if defined NALL (echo  [%NALL%/13]  %~1  %TT%   - start %time:~0,8%) else (echo  %~1  %TT%   - start %time:~0,8%)
echo =============================================================================================
if "%~1"=="1"  goto a1
if "%~1"=="2"  goto a2
if "%~1"=="3"  goto a3
if "%~1"=="4"  goto a4
if "%~1"=="5"  goto a5
if "%~1"=="6"  goto a6
if "%~1"=="8"  goto a8
if "%~1"=="9"  goto a9
if "%~1"=="10" goto a10
if "%~1"=="11" goto a11
if "%~1"=="12" goto a12
if "%~1"=="13" goto a13
if "%~1"=="14" goto a14
if "%~1"=="15" goto a15
if "%~1"=="16" goto a16
echo Unknown choice: %~1
exit /b 1

:a1
set "LOG=%ROOT%\tools\logs\check_log.txt"
> "%LOG%" echo Wordclock_Multi - language check %date% %time%
echo   (details at the end and in tools\logs\check_log.txt)
where g++ >nul 2>nul || >>"%LOG%" echo NOTE: no g++ found - fillers not checked, docs\languages\LANG_XX.txt not rewritten.
where g++ >nul 2>nul || >>"%LOG%" echo       Install: winget install BrechtSanders.WinLibs.POSIX.UCRT
>>"%LOG%" echo.
call :say "Copy the C++ files to ESPHome - tools\sync_src.py"
%PY% tools\sync_src.py >>"%LOG%" 2>&1
>>"%LOG%" echo.
call :say "Pack the web interface - tools\make_webpage.py"
%PY% tools\make_webpage.py >>"%LOG%" 2>&1
>>"%LOG%" echo.
call :say "Script variants of the fronts - tools\make_variants.py"
%PY% tools\make_variants.py >>"%LOG%" 2>&1
>>"%LOG%" echo.
call :say "Check all languages - tools\check_lang.py"
%PY% tools\check_lang.py >>"%LOG%" 2>&1
if errorlevel 1 (set "RES=ERRORS FOUND - see the lines with ERROR above") else (set "RES=ALL OK")
echo     %RES%
>>"%LOG%" echo.
call :say "Update docs\languages and setup guides - tools\make_info.py"
%PY% tools\make_info.py >>"%LOG%" 2>&1
>>"%LOG%" echo.
>>"%LOG%" echo Result: %RES%
type "%LOG%"
goto done

:a2
rem options: --no-esphome only the Python part, --esphome ESPHome required
%PY% tools\check_esphome.py --log "%ROOT%\tools\logs\check_esphome_log.txt"
goto done

:a3
if not exist models\Wordclock_Model.scad goto nomodels
rem option: --verbose also list the equal and the known one-sided parameters
%PY% tools\check_params.py --log "%ROOT%\tools\logs\check_params_log.txt"
goto done

:a4
if not exist models\Wordclock_Model.scad goto nomodels
rem options: --quick without front/PictureFrame, --update save the current state as new reference, --keep STL files
%PY% tools\check_models.py --fit --freecad --log "%ROOT%\tools\logs\check_models_log.txt"
goto done

:a5
%PY% -c "import PIL" >nul 2>nul || %PY% -m pip install --user pillow
rem renders the normal set and the _full set (all additional displays on); other time/colour: e.g. --time 13:47 --color green --set full
echo Light fronts ...
%PY% tools\render_fronts.py
echo.
echo Dark fronts ...
%PY% tools\render_fronts.py --style dark
goto done

:a6
%PY% tools\bundle_firmware.py
goto done

:a8
if not exist models\Wordclock_Model.scad goto nomodels
%PY% tools\bundle_models.py
goto done

:a9
if not exist models\Wordclock_Model.scad goto nomodels
rem options: --font Arial, --quality Normal, --manifold (OpenSCAD 2024/2025, much faster), --lang DE GB
%PY% tools\export_fronts.py Front
goto done

:a10
if not exist models\Wordclock_Model.scad goto nomodels
%PY% tools\export_fronts.py PictureFrame
goto done

:a11
%PY% tools\make_masks.py
goto done

:a12
if not exist models\Wordclock_Model.scad goto nomodels
rem exports all STL again (current model), then one 3MF per language
rem options: --lang DE GB, --reuse (use existing STL, tests only), --no-supports, --template FILE, --font Arial
%PY% tools\make_3mf.py --log "%ROOT%\tools\logs\make_3mf_log.txt"
goto done

:a13
if not exist models\Wordclock_Model.scad goto nomodels
%PY% tools\make_3mf.py --all-only --log "%ROOT%\tools\logs\make_3mf_all_log.txt"
goto done

:a14
if not exist models\Wordclock_Model.scad goto nomodels
%PY% tools\export_fronts.py Parts
goto done

:a15
if not exist models\lang goto nomodels
rem option: --check only check, install nothing
%PY% tools\install_fonts.py
goto done

:a16
if not exist models\Wordclock_Model.scad goto nomodels
rem PictureFrame plates (export_fronts.PF_FRAMES) in the place of the front of the template, one 3MF each
rem options: --frame RIBBA, --lang DE GB, --reuse
%PY% tools\make_3mf.py --pictureframe --log "%ROOT%\tools\logs\make_3mf_pf_log.txt"
goto done

:nomodels
echo skipped: models\ not found - the 3D models are not part of this repository.
goto done

:done
%PY% tools\clean.py --quiet
echo  --- %~1 %TT% finished %time:~0,8%
exit /b 0

:say
rem step of an action: on the console and in the log
echo   - %~1
>>"%LOG%" echo %~1
exit /b 0

:nopython
echo Python 3 was not found.
echo Install it from https://www.python.org and tick "Add python.exe to PATH" during the installation.
pause
exit /b 1
