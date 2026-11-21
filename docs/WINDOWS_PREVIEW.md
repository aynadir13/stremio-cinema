# Stremio Cinema: Windows 11 preview (experimental)

**Actual Windows PE executable:** `StremioCinema.exe` compiled from the project's native C/SDL2/OpenGL renderer. No HTML, Electron or WebView.

**Important:** this first compatibility build uses **Cygwin + XWin** for the POSIX socket/thread APIs; it is not yet a standalone Win32 binary. It is an **interface test**. Video streams run via a simulated player clock, not real Windows decoding; playback parity with webOS is NOT claimed.

## Run
1. Install Cygwin from https://cygwin.com/install.html to `C:\cygwin64`.
2. In its package selector install `xorg-server`, `libSDL2_2.0_0`, `libGLEW2.1`, and any dependency DLLs that the installer automatically selects. The Windows artifact uses the same Cygwin ecosystem as CI.
3. Unzip the GitHub Actions artifact (executable, `assets/`, and launcher) together into a folder. Do not execute the .exe alone without its `assets` directory.
4. Double click `Launch-Stremio-Cinema.cmd`. It starts the XWin server and the **1280x720 native app**.
5. Arrow keys = remote arrows, Enter = OK, Escape = Back; F1/F2 = Settings/Search.

If the app fails to start, open the .cmd from a Command Prompt and share the log.

## Development build
From the Cygwin terminal with the packages in `.github/workflows/cinema-windows-preview.yml` installed:
```sh
cd /cygdrive/c/path/to/stremio-cinema
export SB_SHOW=1 SB_WINDOW=1280x720 SB_REAL_VIDEO=0
bash tools/build-cinema.sh windows --run
```

This Windows preview is independent of the LG webOS ARMv7 production build. Test the visuals/profiles here, not LG-specific codec, subtitles or remote-control features.
