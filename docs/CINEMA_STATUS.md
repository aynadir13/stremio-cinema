# Native Netflix-style fork — verified project status

## Scope and test honesty
This branch is development-only. It is NOT a complete 1.0 release.
The application stays native: C / SDL2 / OpenGL ES 2; all existing
player, stream-selection, subtitles, library and addon code stays in place.

## Implemented
- Flat white-pill top navigation rendered through existing GPU primitives.
- Uses Stremio Origin's real hit-testing and destinations; no fake tabs.
- Build-time switch `CINEMA_UI=1`; default build still uses upstream UI.
- Build object-cache invalidation when switching between skin variants.
- Initial **process-level** profile data isolation: `SB_CINEMA_PROFILE=alice` selects a private `profiles/alice` state/cache directory *before* any Stremio login is loaded. IDs are validated and filesystem failures fail closed. The UI cannot switch profiles yet.
- Separate development package identifier via `tools/build-cinema.sh`.
- Smoke tests for native syntax and key source invariants.

## Not yet implemented
- Profile picker and complete per-profile account/sync isolation audit (the initial isolated-directory building block exists, but is NOT a complete profile system).
- Netflix-sized rounded hero and exact vertical card layout.
- New Movies and Shows category routes (never relabel an unrelated tab).
- Native assets for the custom N/crossbones mark.
- Real-device playback regression and frame-time/memory benchmarking.
- Confirmed ARMv7 build and installable IPK with all required libraries. A macOS native executable has been produced by GitHub Actions; this is not an LG build.

## Build on macOS
The upstream build requires its external SDL2 + Zig/webOS SDK setup.
When configured, run:
```sh
bash tools/build-cinema.sh mac --run
bash tools/build-cinema.sh webos
bash tools/build-cinema.sh package
```
Packaging must include optional playback libraries to retain all upstream
capabilities; see `tools/package.sh`. No HTML ships in the app.

## Completion gate
Only mark 1.0 after Mac and webOS full builds, video tests (HDR/DV,
audio tracks, subtitles, resume, addons, debrid, torrent), profile isolation
tests, 60fps/frame-time benchmarks, and long-session soak testing on device.

## Validated in CI
- GitHub Actions passes syntax/invariant checks for the native UI.
- Native C module filesystem tests verify different state directories, restrictive permissions, and invalid-ID rejection.
- A full native macOS build of the modified code passed on GitHub Actions; a downloadable executable is stored in the run artifacts.
- A headless native OpenGL screenshot smoke check is experimental because hosted runners may not expose a suitable display.
