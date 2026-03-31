#!/bin/sh
set -eu

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
PREFIX="${1:-${ROOT}/install}"
BUILD_DIR="${LOG_BUILD_DIR:-${ROOT}/build}"
DEPS_PREFIX="${ROOT}/library/fmt;${ROOT}/library/spdlog"
LOG_TESTS_FLAG="-DLOG_BUILD_TESTS=OFF"
if [ -d "${ROOT}/library/googletest" ]; then
  DEPS_PREFIX="${DEPS_PREFIX};${ROOT}/library/googletest"
  LOG_TESTS_FLAG="-DLOG_BUILD_TESTS=ON"
fi
JOBS="${JOBS:-$(getconf _NPROCESSORS_ONLN 2>/dev/null || echo 4)}"

cmake -S "$ROOT" -B "$BUILD_DIR" \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_PREFIX_PATH="$DEPS_PREFIX" \
  -DCMAKE_INSTALL_PREFIX="$PREFIX" \
  ${LOG_TESTS_FLAG}

cmake --build "$BUILD_DIR" -j"$JOBS"
cmake --install "$BUILD_DIR" --prefix "$PREFIX"

echo "Installed log to: $PREFIX"
