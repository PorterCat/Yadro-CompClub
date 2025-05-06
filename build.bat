@echo off
setlocal

if exist build (
    rmdir /s /q build
    if errorlevel 1 (
        exit /b 1
    )
)
mkdir build
if errorlevel 1 (
    exit /b 1
)

cd build || exit /b 1

cmake -G "MinGW Makefiles" ..

if errorlevel 1 (
    exit /b 1
)

cmake --build . --config Debug
if errorlevel 1 (
    exit /b 1
)

cd ..

echo For start: build/compclub.exe test_file.txt