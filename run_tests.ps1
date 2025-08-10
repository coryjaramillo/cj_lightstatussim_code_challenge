# PowerShell test runner script for HomeLights C++ project (Windows)

param(
    [switch]$Clean = $false,
    [switch]$Release = $false,
    [switch]$UnitOnly = $false,
    [switch]$IntegrationOnly = $false,
    [switch]$CTest = $false,
    [switch]$Help = $false
)

if ($Help) {
    Write-Host "Usage: .\run_tests.ps1 [OPTIONS]"
    Write-Host "Options:"
    Write-Host "  -Clean              Clean build directory"
    Write-Host "  -Release            Build in Release mode (default: Debug)"
    Write-Host "  -UnitOnly           Run only unit tests"
    Write-Host "  -IntegrationOnly    Run only integration tests"  
    Write-Host "  -CTest              Use CTest to run tests"
    Write-Host "  -Help               Show this help"
    exit 0
}

$ErrorActionPreference = "Stop"

$ProjectRoot = $PSScriptRoot
$BuildDir = Join-Path $ProjectRoot "build"

Write-Host "HomeLights Test Runner (PowerShell)" -ForegroundColor Green
Write-Host "====================================" -ForegroundColor Green

$BuildType = if ($Release) { "Release" } else { "Debug" }
$RunUnit = -not $IntegrationOnly
$RunIntegration = -not $UnitOnly

Set-Location $ProjectRoot

# Clean if requested
if ($Clean) {
    Write-Host "Cleaning build directory..." -ForegroundColor Yellow
    if (Test-Path $BuildDir) {
        Remove-Item $BuildDir -Recurse -Force
    }
}

# Create and configure build
if (-not (Test-Path $BuildDir)) {
    New-Item -ItemType Directory -Path $BuildDir | Out-Null
}
Set-Location $BuildDir

Write-Host "Configuring CMake..." -ForegroundColor Cyan
& cmake .. -DCMAKE_BUILD_TYPE=$BuildType -DBUILD_TESTS=ON
if ($LASTEXITCODE -ne 0) {
    Write-Host "CMake configuration failed!" -ForegroundColor Red
    exit 1
}

Write-Host "Building project..." -ForegroundColor Cyan
& cmake --build .
if ($LASTEXITCODE -ne 0) {
    Write-Host "Build failed!" -ForegroundColor Red
    exit 1
}

Write-Host ""
Write-Host "Build completed successfully!" -ForegroundColor Green
Write-Host ""

# Run tests
if ($CTest) {
    Write-Host "Running tests with CTest..." -ForegroundColor Cyan
    Write-Host "==========================" -ForegroundColor Cyan
    & ctest --verbose
} else {
    if ($RunUnit) {
        Write-Host "Running Unit Tests..." -ForegroundColor Cyan
        Write-Host "====================" -ForegroundColor Cyan
        $unitTestExe = Join-Path "tests" "HomeLightsTests.exe"
        & $unitTestExe
        if ($LASTEXITCODE -ne 0) {
            Write-Host "Unit tests failed!" -ForegroundColor Red
            exit 1
        }
        Write-Host ""
    }
    
    if ($RunIntegration) {
        Write-Host "Running Integration Tests..." -ForegroundColor Cyan
        Write-Host "===========================" -ForegroundColor Cyan
        $integrationTestExe = Join-Path "tests" "IntegrationTests.exe"
        & $integrationTestExe
        if ($LASTEXITCODE -ne 0) {
            Write-Host "Integration tests failed!" -ForegroundColor Red
            exit 1
        }
        Write-Host ""
    }
}

Write-Host "All tests completed successfully!" -ForegroundColor Green
