$ErrorActionPreference = 'Stop'
$srcDir = Resolve-Path './bazel-bin/vehicle_plugin'
$dst = 'C:/Program Files/Outerra/Anteworld/plugins/vehicle_plugin'
New-Item -ItemType Directory -Path $dst -Force | Out-Null
$files = @('vehicle_plugin.dll','vehicle_plugin.pdb')
foreach ($f in $files) {
  $p = Join-Path $srcDir $f
  if (Test-Path -LiteralPath $p) {
    Copy-Item -LiteralPath $p -Destination $dst -Force
  }
}
Write-Host "Installed vehicle_plugin artifacts to $dst"
