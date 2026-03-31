#!/bin/sh
set -eu

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
LIBRARY="${ROOT}/library"
BUILD_ROOT="${ROOT}/.third_party_build"
SPDLOG_REF="v1.14.1"
SPDLOG_REPO="https://github.com/gabime/spdlog.git"
jobs="${JOBS:-$(getconf _NPROCESSORS_ONLN 2>/dev/null || echo 4)}"

cmake_install() {
  _src="$1"
  _build="$2"
  shift 2
  cmake -S "$_src" -B "$_build" "$@"
  cmake --build "$_build" -j"$jobs"
  cmake --install "$_build"
}

_src="${BUILD_ROOT}/spdlog"
_build="${BUILD_ROOT}/spdlog-build"
rm -rf "$_src" "$_build"
mkdir -p "$BUILD_ROOT"
git clone --depth 1 --branch "$SPDLOG_REF" "$SPDLOG_REPO" "$_src"
cmake_install "$_src" "$_build" \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_INSTALL_PREFIX="${LIBRARY}/spdlog" \
  -DCMAKE_PREFIX_PATH="${LIBRARY}/fmt" \
  -DSPDLOG_BUILD_EXAMPLE=OFF \
  -DSPDLOG_BUILD_TESTS=OFF \
  -DSPDLOG_FMT_EXTERNAL=ON

echo "Installed spdlog to ${LIBRARY}/spdlog"
