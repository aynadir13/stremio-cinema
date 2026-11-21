# Netflix TV 2025 screenshot → native layout specification

Reference screenshot supplied by the project owner: **1200 × 675** (16:9). Target native renderer: **1920 × 1080**. The native renderer's UI coordinate system already uses 1920 × 1080, so all screenshot coordinates below are scaled by **1.6**.

This file specifies geometry only. **Do not distribute Netflix artwork, trademarked lettering, screenshots, or UI assets** in the fork. Source all program artwork from the user's authorized Stremio addon metadata. Do not show invented movie entries.

## Screen coordinates

| Element | Reference pixels | Native UI pixels |
|---|---|---|
| Profile/avatar (left header) | x28 y29 size31 | x45 y46 size50 |
| Search glyph center | x366 y44 | x586 y70 |
| Selected Home pill | x392 y21 w98 h48 | x627 y34 w157 h77 |
| Navigation baseline | y45 | y72 |
| Top-right brand location | x1152 y27 | x1843 y43 |
| Cinematic hero | x29 y89 w1142 h490 | x46 y142 w1827 h784 |
| Hero corner radius | ~18 | ~29 |
| Hero content title zone | x49 y415 | x78 y664 |
| Hero metadata baseline | y558 | y893 |
| Card/footer chips | x590 y520 | x944 y832 |
| First row heading | x29 y624 | x46 y998 |
| First row cards top | y654 | y1046 |

These are measurements from a reference screenshot, **not** pixel-perfect guarantees. The image may have been rescaled from a larger display.

## Rendering strategy

1. Reuse the active item's actual backdrop, logo and metadata from Origin's current board model.
2. Show the hero as a single rounded, textured graphic with a dark left-side readability gradient. Avoid fullscreen offscreen capture or new blur textures on the TV.
3. Place actual metadata on the hero, with the same focus and animation semantics as Origin.
4. Reuse the existing native top bar's focus/hit-test actions, but expand the navigation architecture only after the Shows/Movies routes are genuinely backed by filtered catalogues.
5. Begin the first content row at the bottom of the hero, partially visible at screen edge. Scroll naturally down; do not eagerly decode images outside visible/preload bounds.
6. Implement the 'Who's watching?' screen **only after** profile credential, library and Trakt session boundaries are fully audited.
7. Never show a fake play button or a media card that cannot lead to its real Stremio detail/playback workflow.

## TV performance gates

- Target 60 Hz (16.67 ms frame budget), with a measured p95 rather than a visual guess.
- Cache decoded art under the existing image memory budget; recycle GPU textures.
- Preload a bounded number of titles per row, and avoid anything heavy on remote-key callbacks.
- Run the same instrumentation on the unmodified Origin and the fork before declaring comparable performance.
- Confirm the original player, track/subtitle selection and all addon-based sources behave exactly as before.

## Current progress

The first native implementation replaces only the **top bar styling**. Hero geometry and the category tab architecture here are **design targets**, not yet implemented.
