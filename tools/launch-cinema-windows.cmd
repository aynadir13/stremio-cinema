@echo off
setlocal
set "CYGWIN_ROOT=C:\cygwin64"
if not exist "%CYGWIN_ROOT%\bin\bash.exe" (
  echo [Cinema] Cygwin est absent de C:\cygwin64
  pause
  exit /b 1
)
if not exist "%CYGWIN_ROOT%\bin\XWin.exe" (
  echo [Cinema] Le serveur XWin manque : installe le paquet xorg-server.
  pause
  exit /b 1
)
REM cd /d handles regular paths; pushd additionally supports network shares.
pushd "%~dp0" || (
  echo [Cinema] Impossible d'ouvrir le dossier extrait.
  pause
  exit /b 1
)
if not exist "StremioCinema.exe" (
  echo [Cinema] StremioCinema.exe introuvable dans %CD%
  echo [Cinema] Extrais completement le ZIP, puis ouvre ce lanceur depuis le meme dossier que l'exe.
  popd
  pause
  exit /b 1
)
if not exist "assets\cacert.pem" (
  echo [Cinema] Le sous-dossier assets semble incomplet.
  popd
  pause
  exit /b 1
)
set "DISPLAY=:0"
set "SB_SHOW=1"
set "SB_WINDOW=1280x720"
set "SB_RES=720"
set "SB_REAL_VIDEO=0"
start "" /min "%CYGWIN_ROOT%\bin\XWin.exe" :0 -multiwindow -clipboard
timeout /t 3 /nobreak >nul
REM Cygwin inherits the current working directory from CMD. No cygpath
REM translation (the original FOR /F broke on quoted Windows paths).
"%CYGWIN_ROOT%\bin\bash.exe" --noprofile --norc -c "export SB_ASSETS=./assets SB_SHOW=1 SB_WINDOW=1280x720 SB_RES=720 SB_REAL_VIDEO=0 DISPLAY=:0; exec ./StremioCinema.exe"
set "RESULT=%ERRORLEVEL%"
if not "%RESULT%"=="0" (
  echo [Cinema] Erreur %RESULT%. Copie le message ci-dessus.
  pause
)
popd
endlocal
