#!/bin/sh
set -eu

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
PREFIX="${1:-${ROOT}/install}"
DEPS_PREFIX="${PREFIX};${ROOT}/library/fmt;${ROOT}/library/spdlog"
JOBS="${JOBS:-$(getconf _NPROCESSORS_ONLN 2>/dev/null || echo 4)}"

cmake -S "${ROOT}/demo" -B "${ROOT}/demo/build" \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_PREFIX_PATH="${DEPS_PREFIX}"

cmake --build "${ROOT}/demo/build" -j"${JOBS}"
ctest --test-dir "${ROOT}/demo/build" --output-on-failure

echo "Built: ${ROOT}/demo/build/log_demo"
