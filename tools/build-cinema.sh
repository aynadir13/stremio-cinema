#!/usr/bin/env bash
# Native fork only: no browser engine is packaged.
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"
TARGET="${1:-mac}"
export CINEMA_UI=1
export APPID="${APPID:-fr.edo.originuilab.dev}"
export TITLE="${TITLE:-Origin UI Lab (Development)}"
case "$TARGET" in
  mac) exec bash tools/build.sh mac "${@:2}" ;;
  webos) exec bash tools/build.sh webos "${@:2}" ;;
  package) exec bash tools/package.sh ;;
  *) printf 'Usage: %s mac|webos|package [--run]\n' "$0" >&2; exit 2 ;;
esac
