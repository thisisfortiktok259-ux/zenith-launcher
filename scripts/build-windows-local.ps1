# Zenith Launcher - Local Windows Build Helper
param(
    [string]$BuildType = "Release",
    [switch]$InstallPrerequisites
)

Write-Host "==========================================" -ForegroundColor Cyan
Write-Host " Zenith Launcher - Local Build for Windows" -ForegroundColor Cyan
Write-Host "==========================================" -ForegroundColor Cyan

if ($InstallPrerequisites) {
    Write-Host "[*] Checking and installing prerequisites via winget..." -ForegroundColor Yellow
    winget install -e --id Kitware.CMake --accept-package-agreements --accept-source-agreements
    winget install -e --id Ninja-build.Ninja --accept-package-agreements --accept-source-agreements
    Write-Host "[+] Prerequisites installed. Please ensure Qt 6.6+ is installed." -ForegroundColor Green
    exit 0
}

# Check for cmake
$cmake = Get-Command "cmake" -ErrorAction SilentlyContinue
if (-not $cmake) {
    Write-Host "[!] 'cmake' was not found in PATH." -ForegroundColor Red
    Write-Host "    You can run: .\scripts\build-windows-local.ps1 -InstallPrerequisites" -ForegroundColor Yellow
    Write-Host "    Or use GitHub Actions to build .exe automatically in the cloud without local setup." -ForegroundColor Green
    exit 1
}

Write-Host "[*] Found CMake: $($cmake.Source)" -ForegroundColor Green
Write-Host "[*] Configuring build with CMake ($BuildType)..." -ForegroundColor Cyan

cmake -B build -S . -DCMAKE_BUILD_TYPE=$BuildType

if ($LASTEXITCODE -eq 0) {
    Write-Host "[*] Compiling Zenith Launcher..." -ForegroundColor Cyan
    cmake --build build --config $BuildType
    Write-Host "[+] Build completed successfully! Check the 'build' directory." -ForegroundColor Green
} else {
    Write-Host "[-] CMake configuration failed. Check output above." -ForegroundColor Red
}
