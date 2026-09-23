# ============================================================
# 32learning notes one-click sync: pull -> add -> commit -> push
# Usage:
#   powershell -File git-note-push.ps1
#   powershell -File git-note-push.ps1 "custom commit message"
# ============================================================

$repo = Split-Path -Parent $MyInvocation.MyCommand.Path
Set-Location $repo

function ShowInfo($m) { Write-Host "[notes] $m" -ForegroundColor Cyan }
function ShowOk($m)   { Write-Host "[ok]    $m" -ForegroundColor Green }
function ShowWarn($m) { Write-Host "[warn]  $m" -ForegroundColor Yellow }

if (-not (Test-Path (Join-Path $repo '.git'))) {
    ShowWarn 'this folder is not a git repository'
    exit 1
}

# 1. best-effort pull (offline must not block a local commit)
ShowInfo 'pulling latest from GitHub ...'
git pull --ff-only 2>&1 | Out-Host
if ($LASTEXITCODE -ne 0) {
    ShowWarn 'pull failed (offline?) - will commit locally and try to push later'
}

# 2. stage every change
git add -A 2>&1 | Out-Host

# 3. nothing staged -> nothing to do (exit code 0 = no diff)
git diff --cached --quiet
if ($LASTEXITCODE -eq 0) {
    ShowInfo 'no new or changed notes found, nothing to commit'
    exit 0
}

# 4. build commit message: first argument wins, otherwise date+time
if ($args.Count -ge 1 -and -not [string]::IsNullOrWhiteSpace([string]$args[0])) {
    $msg = ([string]$args[0]).Trim()
} else {
    $msg = ([string][char]0x7B14 + [char]0x8BB0) + ': ' + (Get-Date -Format 'yyyy-MM-dd HH:mm')
}

git commit -m $msg 2>&1 | Out-Host
if ($LASTEXITCODE -ne 0) {
    ShowWarn 'commit failed, see the git message above'
    exit 1
}
ShowOk ("committed: " + $msg)

# 5. push to GitHub
ShowInfo 'pushing to GitHub ...'
git push 2>&1 | Out-Host
if ($LASTEXITCODE -ne 0) {
    ShowWarn 'push failed. notes are safe locally; just double-click again when online'
    exit 1
}
ShowOk 'push succeeded, GitHub is up to date'
exit 0
