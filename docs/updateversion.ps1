# Get version
param(
    [string]$Version,
    [bool]$CheckFormat = $true
)

if (-not $Version) {
    $Version = describe --tags --abrev=0
}

if ($CheckFormat) {
    if ($Version -notmatch '^v[0-9]+\.[0-9]+\.[0-9]+$') {
        Write-Host "Invalid version format! Version must be in the format vX.Y.Z (e.g., v1.2.3)"
        exit 1
    }
} else {
    Write-Host "Version format is ignored!"
}

Write-Host "Using version: $Version"

# Change dir to ./docs if not here already
$scriptDir = (Get-Location).Path
$scriptDir = Split-Path -Path $MyInvocation.MyCommand.Definition -Parent

# Replaces @VERSION@ with the actual version in Doxyfile.in and output to Doxyfile
(Get-Content $scriptDir\Doxyfile.in) -replace '@VERSION@', $version | Set-Content $scriptDir\Doxyfile