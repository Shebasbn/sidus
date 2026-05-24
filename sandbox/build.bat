@echo off
rem Build Script For Sandbox App
SetLocal EnableDelayedExpansion

set CONFIG=%~1
if "%CONFIG%"=="" set CONFIG=debug

Set Assembly=sandbox
set FileName=sandbox.c

set CommonCFlags=/nologo /W4 /WX /std:c11 /TC /FC /Zm200
set DebugFlags=/Zi /Od /MDd /RTC1
set ReleaseFlags=/O2 /Oi /MD /GL /DNDEBUG
 
set CommonDefines=/DWIN32_LEAN_AND_MEAN /D_CRT_SECURE_NO_WARNINGS /DSIDUS_IMPORT
set DebugDefines=/D_DEBUG /DBUILD_DEBUG
set ReleaseDefines=/DNDEBUG /DBUILD_RELEASE

set IncludeFlags=/I"src" /I"../engine/src/"
set LinkerFlags=/INCREMENTAL:NO /OPT:REF /LIBPATH:"..\build\bin" engine.lib 

if /I "%CONFIG%"=="release" (
    set ActiveFlags=%CommonCFlags% %ReleaseFlags%
    set ActiveDefines=%CommonDefines% %ReleaseDefines%
) else (
    set ActiveFlags=%CommonCFlags% %DebugFlags%
    set ActiveDefines=%CommonDefines% %DebugDefines%
)

echo %cd%
echo "Compiling %Assembly% [%CONFIG%]..."

if not exist ..\build\bin mkdir ..\build\bin

cl %ActiveFlags% %ActiveDefines% /I. %IncludeFlags% src\%FileName% /Fo"..\build\\" /Fe"..\build\bin\%Assembly%.exe" /link %LinkerFlags%

cl  /P %ActiveFlags% %ActiveDefines% /I. %IncludeFlags%  /Fi"..\build\sandbox.i" src\%FileName% 

exit /b %ERRORLEVEL%