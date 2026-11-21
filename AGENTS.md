# Origin UI Lab — development instructions (working title)

This repository is a fork of [Stremio Origin](https://github.com/stremio-origin/webos), an unofficial native Stremio client for LG webOS.

## Non-negotiable principles

- **Native TV application:** retain the existing C, SDL2, and OpenGL ES 2 renderer. The browser-based `index.html` is a *design review tool only* and must never replace the native TV UI or player.
- **Preserve every working Origin capability:** Stremio addons, account login, catalogues, streams, debrid/direct/torrent playback, video plane, audio tracks, subtitles, Trakt, search, library, resume, and platform integrations.
- **Profiles are real data boundaries:** never present multiple avatars while sharing one user's history, watch state, watchlist, credentials, or addon settings without explicitly communicating the limitation. Design isolated storage and sessions before enabling profile switching.
- **No fabricated media in the native application:** posters, backdrops, descriptions, recommendations and catalogues come from the active profile's real metadata/addon sources. Handle missing artwork and empty/error states explicitly.
- **Performance first:** preserve batching and texture caching; limit GPU texture memory, avoid network or image decoding on the UI frame path, and benchmark versus the unmodified Origin build.
- **Safe development:** keep `main` and the official Stremio Origin installation untouched. Develop in feature branches. Use a separate package ID and test on macOS before deploying to LG webOS.
- **Reference design:** Netflix TV 2025–2026's top navigation, cinematic hero, focus behavior, and horizontally scrolling artwork, adapted to a distinct project identity.
- **Licensing:** preserve GPL-3.0 notices and third-party attributions. Do not commit service tokens, API keys, personal data, or proprietary Netflix assets.

## Target environment

LG OLED55A16LA, webOS 6.6, ARMv7. The existing source builds via `tools/build.sh mac` and `tools/build.sh webos`, with a separately configured local toolchain. The build and runtime must continue to work without any HTML engine.

## Implementation approach

1. Baseline the upstream branch and preserve native playback.
2. Introduce independently testable UI styling/layout adaptations through existing `src/core/app.c`, `src/screens/`, and `src/ui/` interfaces.
3. Design and test profile state isolation, credential lifecycle, per-profile sync, and migration before enabling a profile selector.
4. Validate complete functionality and native performance on both the Mac build and an actual LG device.

**Test truthfully:** never label a design mock-up, a syntax-only check, or an unrun patch as a fully working LG application.

## Visual identity decision

The owner selected a red N with crossed red bones as the eventual project emblem. Do not substitute the temporary name or unrelated logo. Before public distribution, review branding rights and provide an original, safely usable asset. The repository slug `stremio-cinema` is historical and **not** the final product name.
