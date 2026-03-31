#!/bin/sh
set -eu

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
LIBRARY="${ROOT}/library"
BUILD_ROOT="${ROOT}/.third_party_build"
FMT_REF="10.2.1"
FMT_REPO="https://github.com/fmtlib/fmt.git"
jobs="${JOBS:-$(getconf _NPROCESSORS_ONLN 2>/dev/null || echo 4)}"

cmake_install() {
  _src="$1"
  _build="$2"
  shift 2
  cmake -S "$_src" -B "$_build" "$@"
  cmake --build "$_build" -j"$jobs"
  cmake --install "$_build"
}

_src="${BUILD_ROOT}/fmt"
_build="${BUILD_ROOT}/fmt-build"
rm -rf "$_src" "$_build"
mkdir -p "$BUILD_ROOT"
git clone --depth 1 --branch "$FMT_REF" "$FMT_REPO" "$_src"
cmake_install "$_src" "$_build" \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_INSTALL_PREFIX="${LIBRARY}/fmt" \
  -DFMT_TEST=OFF

echo "Installed fmt to ${LIBRARY}/fmt"
