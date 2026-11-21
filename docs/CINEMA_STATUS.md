# Native Netflix-style fork — verified project status

## Scope and test honesty
This branch is development-only. It is NOT a complete 1.0 release.
The application stays native: C / SDL2 / OpenGL ES 2; all existing
player, stream-selection, subtitles, library and addon code stays in place.

## Implemented
- Reference v0.3-based native top bar: scaled coordinates, working Home / Shows / Movies / My Netflix navigation and search, red N brand mark. Shows and Movies select genuine addon type filters, Library backs My Netflix.
- Uses Stremio Origin's real hit-testing and destinations; no fake tabs.
- Cinematic hero backdrop clipped to a 1828×783 logical 1080p viewport based on the provided 1200×675 reference; current artwork continues to load dynamically from actual addons.
- Home catalog rails use landscape card dimensions and real backdrop assets; neither the demo Avatar image nor fake movie data are shipped.
- Build-time switch `CINEMA_UI=1`; default build still uses upstream UI.
- Build object-cache invalidation when switching between skin variants.
- Native 'Qui regarde ?' modal with profile slots (Alex, Sam, Enfants). Selection persists an active ID then restarts the native executable before loading authentication. Sam/Enfants use private state/cache directories; Alex reuses the legacy default path. IDs are validated, paths restricted and filesystem failures fail closed. Names and avatars are temporary fixed defaults; profile management and full auth-leak audit remain.
- Separate development package identifier via `tools/build-cinema.sh`.
- Smoke tests for native syntax and key source invariants.

## Not yet implemented
- Edit/create/delete profile UI, custom avatars, and complete per-profile account/sync isolation audit (the selection and separate data directories are implemented, but not all state consumers audited).
- Visual parity on actual artwork, hero title fitting and corner rendering, despite GPU-rounded masking already being implemented using the real baked backdrop.
- Screenshot-calibrated card focus, scrolling and dynamic hero copy layout.
- Exhaustive Shows/Movies filtering coverage across every addon configuration, beyond basic native type filtering.
- Native assets for the custom N/crossbones mark and actual chosen avatar photos; current vector-font N and generated letter tiles are temporary.
- Real-device playback regression and frame-time/memory benchmarking.
- Confirmed ARMv7 build and installable IPK with all required libraries. A macOS native executable has been produced by GitHub Actions; this is not an LG build.

## Exact visual reference
The source is the user's `stremio-netflix-ui-preview-v03.zip` with a 1200×675 screenshot. Onboarding, fake catalogs and demo accounts are not copied into the native application.

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
