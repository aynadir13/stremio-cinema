@echo off
setlocal
set "CYGWIN_ROOT=C:\cygwin64"
if not exist "%CYGWIN_ROOT%\bin\bash.exe" (
  echo [Cinema] La previsualisation Windows demande Cygwin.
  echo Installe le runtime via https://cygwin.com/install.html
  echo Paquets requis: libSDL2_2.0_0 libGLEW2.1 xorg-server
  pause
  exit /b 1
)
if not exist "%CYGWIN_ROOT%\bin\XWin.exe" (
  echo [Cinema] XWin n'est pas installe. Ajoute le paquet xorg-server dans Cygwin.
  pause
  exit /b 1
)
set "DISPLAY=:0"
set "SB_SHOW=1"
set "SB_WINDOW=1280x720"
set "SB_REAL_VIDEO=0"
set "SB_RES=720"
start "" /min "%CYGWIN_ROOT%\bin\XWin.exe" :0 -multiwindow -clipboard
timeout /t 3 /nobreak >nul
for %%I in ("%~dp0.") do set "CINEMA_DIR=%%~fI"
for /f "delims=" %%I in ('"%CYGWIN_ROOT%\bin\cygpath.exe" -u "%CINEMA_DIR%"') do set "CYG_DIR=%%I"
"%CYGWIN_ROOT%\bin\bash.exe" -lc "cd '%CYG_DIR%' && export SB_ASSETS='./assets' SB_SHOW=1 SB_WINDOW=1280x720 SB_REAL_VIDEO=0 DISPLAY=:0 && ./StremioCinema.exe"
if errorlevel 1 (
  echo [Cinema] Le lancement a echoue. Copie la fin de cette fenetre pour diagnostic.
  pause
)
endlocal
