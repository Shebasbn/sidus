@echo off

cd /D "%~dp0"

rem echo "%~dp0"

if not defined DevEnvDir (
    setlocal enabledelayedexpansion
    set "D_vswhere=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
    
    if exist "!D_vswhere!" (
      for /f "usebackq tokens=*" %%i in (`"!D_vswhere!" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do    (
            set "D_VS_PATH=%%i"
        )
    )
    
    if not defined D_VS_PATH (
        set "D_VS_PATH=C:\Program Files\Microsoft Visual Studio\18\Community"
    )
    
    :: Pass ONLY the string path out of the sandbox
    for /f "tokens=*" %%a in ("!D_VS_PATH!") do (
        endlocal
        set "VS_PATH=%%a"
    )
)

:: 2. Now run vcvarsall.bat completely OUTSIDE of any setlocal block!
:: This guarantees the variables permanently live on for cl.exe to use.
if defined VS_PATH (
    if exist "%VS_PATH%\VC\Auxiliary\Build\vcvarsall.bat" (
        pushd "%VS_PATH%\VC\Auxiliary\Build"
        call vcvarsall.bat x64 >nul
        popd
        set VS_PATH=
    ) else (
        echo [ERROR] Could not find vcvarsall.bat at: "%VS_PATH%\VC\Auxiliary\Build"
        exit /b 1
    )
)

setlocal

:: --- Unpack Arguments -------------------------------------------------------
for %%a in (%*) do set "%%a=1"
if not "%msvc%"=="1" if not "%clang%"=="1" set msvc=1
if not "%release%"=="1" set debug=1
if "%debug%"=="1"   set release=0 && echo [debug mode]
if "%release%"=="1" set debug=0 && echo [release mode]
if "%msvc%"=="1"    set clang=0 && echo [msvc compile]
if "%clang%"=="1"   set msvc=0 && echo [clang compile]

:: --- Compile/Link Line Definitions ------------------------------------------
set cl_common=	/I..\code\ /I..\local\ /nologo /FC /Z7 /W4 /WX
set cl_debug=	 call cl /Od /DBUILD_DEBUG=1 %cl_common% 
set cl_release=   call cl /O2 /DBUILD_DEBUG=0 %cl_common%	
set cl_link=	  /link /MANIFEST:EMBED /INCREMENTAL:NO /pdbaltpath:%%%%_PDB%%%%
set cl_out= 	  /Fe:
set cl_include=   /I

set clang_common= -I..\code\ -I..\local\ -g -gcodeview -Wall -Werror -Wno-unused-command-line-argument
set clang_debug=   call clang -O0 -DBUILD_DEBUG=1 %clang_common%
set clang_release= call clang -O2 -DBUILD_DEBUG=0 %clang_common%
set clang_link=    -fuse-ld=lld -Wl,/MANIFEST:EMBED,/INCREMENTAL:NO,/pdbaltpath:%%%%_PDB%%%%
set clang_out=     -o 
set clang_include= -I

rem echo Compile/Link Line

:: --- Per-Build Settings -----------------------------------------------------
rem set link_dll=-DLL
if "%msvc%"=="1"  set only_compile=/c
if "%clang%"=="1" set only_compile=-c
if "%msvc%"=="1"  set EHsc=/EHsc
if "%clang%"=="1" set EHsc=
if "%msvc%"=="1"  set no_aslr=/DYNAMICBASE:NO
if "%clang%"=="1" set no_aslr=-Wl,/DYNAMICBASE:NO
if "%msvc%"=="1"  set rc=call rc
if "%clang%"=="1" set rc=call llvm-rc
if "%msvc%"=="1"  set inc_flag=%cl_include%
if "%clang%"=="1" set inc_flag=%clang_include%
if "%msvc%"=="1"  set link=
if "%clang%"=="1" set link=-l
if "%msvc%"=="1"  set link_path=/LIBPATH:
if "%clang%"=="1" set link_path=-L
if "%msvc%"=="1"  set link_dll=/LD /DBUILD_DLL=1
if "%clang%"=="1" set link_dll=-shared

rem echo Per-Build Settings

:: --- Choose Compile/Link Lines ----------------------------------------------
if "%msvc%"=="1"      set compile_debug=%cl_debug%
if "%msvc%"=="1"      set compile_release=%cl_release%
if "%msvc%"=="1"      set compile_link=%cl_link%
if "%msvc%"=="1"      set out=%cl_out%
if "%clang%"=="1"     set compile_debug=%clang_debug%
if "%clang%"=="1"     set compile_release=%clang_release%
if "%clang%"=="1"     set compile_link=%clang_link%
if "%clang%"=="1"     set out=%clang_out%
if "%debug%"=="1"     set compile=%compile_debug%
if "%release%"=="1"   set compile=%compile_release%

 if "%msvc%"=="1" (
   set sidus_compile= /DBUILD_DLL=1 /Fe:sidus_engine.dll /IVULKAN_SDK%/Include /LD
   set sidus_link= /LIBPATH:%VULKAN_SDK%\Lib user32.lib vulkan-1.lib 

   set sandbox_compile=
   set sandbox_link=
 )

:: --- Prep Directories -------------------------------------------------------
if not exist build mkdir build
if not exist local mkdir local

:: --- Get Current Git Commit Id ----------------------------------------------
for /f %%i in ('call git describe --always --dirty')   do set compile=%compile% -DBUILD_GIT_HASH=\"%%i\"
for /f %%i in ('call git rev-parse HEAD')              do set compile=%compile% -DBUILD_GIT_HASH_FULL=\"%%i\"


:: ---- Build ----------------------------
pushd build
if "%engine%"=="1" (
 set didbuild=1
rem echo "%compile%"
echo %compile% %sidus_compile% "..\code\engine\sidus_engine.c" %compile_link% %sidus_link% 
 %compile% %sidus_compile% "..\code\engine\sidus_engine.c" %compile_link% %sidus_link% || exit /b 1
)

if "%sandbox%"=="1" (
  set didbuild=1
  %compile% %sandbox_compile% "..\code\sandbox\sandbox.c" %compile_link% %sandbox_link% || exit /b 1
)
popd

:: --- Warn On No Builds ------------------------------------------------------
if "%didbuild%"=="" (
  echo [WARNING] no valid build target specified; must use build target names as arguments to this script, like `build g0` or `build tests`.
  exit /b 1
)

:: --- Unset ------------------------------------------------------------------
for %%a in (%*) do set "%%a=0"
set compile=
set compile_link=
set out=
set msvc=
set debug=
endlocal
