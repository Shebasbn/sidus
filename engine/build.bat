@echo off
rem Build Script For Engine
SetLocal EnableDelayedExpansion

set CONFIG=%~1
if "%CONFIG%"=="" set CONFIG=debug

Set Assembly=engine
set FileName=engine_entry.c

set CommonCFlags=/nologo /W4 /WX /std:c11 /TC /FC /Zm200
set DebugFlags=/Zi /Od /MDd /RTC1
set ReleaseFlags=/O2 /Oi /MD /GL /DNDEBUG
 
set CommonDefines=/DWIN32_LEAN_AND_MEAN /D_CRT_SECURE_NO_WARNINGS /DS_EXPORT
set DebugDefines=/D_DEBUG /DS_BUILD_DEBUG
set ReleaseDefines=/DNDEBUG /DS_BUILD_RELEASE

set IncludeFlags=/I"src" /I"%VULKAN_SDK%\Include"
set LinkerFlags=/INCREMENTAL:NO /OPT:REF /LIBPATH:"%VULKAN_SDK%\Lib" user32.lib vulkan-1.lib 

if /I "%CONFIG%"=="release" (
    set ActiveFlags=%CommonCFlags% %ReleaseFlags%
    set ActiveDefines=%CommonDefines% %ReleaseDefines%
) else (
    set ActiveFlags=%CommonCFlags% %DebugFlags%
    set ActiveDefines=%CommonDefines% %DebugDefines%
)

echo %cd%
echo "Compiling %Assembly% [%CONFIG%]..."

if exist ..\bin rmdir /s /q ..\bin
mkdir ..\bin
if not exist ..\bin mkdir ..\bin

cl %ActiveFlags% %ActiveDefines% /I. %IncludeFlags% src\%FileName% /Fo"..\bin\\" /Fe"..\bin\%Assembly%.dll" /link /DLL %LinkerFlags%

exit /b %ERRORLEVEL%


