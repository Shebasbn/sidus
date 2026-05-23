@echo off
echo "Building everything..."

pushd engine
call build.bat
popd
if %ERRORLEVEL% neq 0 (echo Erro:%ERRORLEVEL% && exit)

pushd sandbox
call build.bat
popd
if %ERRORLEVEL% neq 0 (echo Erro:%ERRORLEVEL% && exit)

echo "All assemblies built successfully."