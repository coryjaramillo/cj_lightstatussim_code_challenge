# PowerShell script to build all configurations for Windows
# Usage: .\build_all_windows.ps1

param(
    [switch]$Clean = $false
)

Write-Host "Smart Home Light Status Monitor - Windows Build Script" -ForegroundColor Green
Write-Host "=====================================================" -ForegroundColor Green

$BuildTypes = @("Debug_Simple", "Debug_Verbose", "Debug_All", "Release")
$TotalBuilds = $BuildTypes.Count
$CurrentBuild = 0

# Clean previous builds if requested
if ($Clean) {
    Write-Host "`nCleaning previous builds..." -ForegroundColor Yellow
    $BuildTypes | ForEach-Object {
        $BuildDir = "build_$($_.ToLower() -replace '_', '_')"
        if (Test-Path $BuildDir) {
            Remove-Item -Recurse -Force $BuildDir
            Write-Host "Removed $BuildDir" -ForegroundColor Gray
        }
    }
}

foreach ($BuildType in $BuildTypes) {
    $CurrentBuild++
    $BuildDir = "build_$($BuildType.ToLower() -replace '_', '_')"
    $ExecutableName = "cj_lightsimstatus_code_chal_win11_$($BuildType.ToLower() -replace '_', '_').exe"
    
    Write-Host ("`n[{0}/{1}] Building {2} configuration..." -f $CurrentBuild, $TotalBuilds, $BuildType) -ForegroundColor Cyan
    Write-Host "Build directory: $BuildDir" -ForegroundColor Gray
    Write-Host "Output: $ExecutableName" -ForegroundColor Gray
    
    try {
        # Create and navigate to build directory
        if (!(Test-Path $BuildDir)) {
            New-Item -ItemType Directory -Force -Path $BuildDir | Out-Null
        }
        Set-Location $BuildDir
        
        # Configure
        Write-Host "Configuring..." -ForegroundColor Yellow
        cmake -DCMAKE_BUILD_TYPE=$BuildType .. 2>&1 | ForEach-Object {
            if ($_ -match "error|Error|ERROR") {
                Write-Host $_ -ForegroundColor Red
            }
        }
        if ($LASTEXITCODE -ne 0) { throw "CMake configuration failed" }

        # Build
        Write-Host "Building..." -ForegroundColor Yellow
        cmake --build . --config $BuildType 2>&1 | ForEach-Object {
            if ($_ -match "error|Error|ERROR") {
                Write-Host $_ -ForegroundColor Red
            } elseif ($_ -match "warning|Warning|WARNING") {
                Write-Host $_ -ForegroundColor Yellow
            }
        }
        if ($LASTEXITCODE -ne 0) { throw "Build failed" }

        # Verify executable
        $ExePath = Get-ChildItem -Recurse -Name "*.exe" | Select-Object -First 1
        if ($ExePath) {
            Write-Host "✓ Build successful: $ExePath" -ForegroundColor Green
            $FileInfo = Get-Item $ExePath
            Write-Host "  Size: $([math]::Round($FileInfo.Length / 1KB, 2)) KB" -ForegroundColor Gray
            Write-Host "  Created: $($FileInfo.CreationTime)" -ForegroundColor Gray
        } else {
            Write-Host "⚠ Warning: Executable not found" -ForegroundColor Yellow
        }

        Set-Location ..
    }
    catch {
        Write-Host "✗ Build failed: $($_.Exception.Message)" -ForegroundColor Red
        Set-Location ..
        continue
    }
}


Write-Host "`n=====================================================" -ForegroundColor Green
Write-Host "Build Summary:" -ForegroundColor Green

# Display final status
$BuildTypes | ForEach-Object {
    $BuildDir = "build_$($_.ToLower() -replace '_', '_')"
    $ExecutableName = "cj_lightsimstatus_code_chal_win11_$($_.ToLower() -replace '_', '_').exe"
    
    if (Test-Path "$BuildDir\*.exe" -or (Get-ChildItem -Path $BuildDir -Recurse -Name "*.exe" -ErrorAction SilentlyContinue)) {
        Write-Host "✓ $_ - SUCCESS" -ForegroundColor Green
    } else {
        Write-Host "✗ $_ - FAILED" -ForegroundColor Red
    }
}

Write-Host "`nTo run an executable:" -ForegroundColor Cyan
Write-Host "  cd build_release" -ForegroundColor Gray
Write-Host "  .\cj_lightsimstatus_code_chal_win11_release.exe" -ForegroundColor Gray

Write-Host "`nPackages created in: build_*/package/" -ForegroundColor Cyan
