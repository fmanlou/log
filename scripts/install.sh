#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
PREFIX="${1:-${ROOT}/install}"
BUILD_DIR="${LOG_BUILD_DIR:-${ROOT}/build}"
DEPS_PREFIX="${ROOT}/library/fmt;${ROOT}/library/spdlog"
JOBS="${JOBS:-$(nproc 2>/dev/null || echo 4)}"

cmake -S "${ROOT}" -B "${BUILD_DIR}" \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_PREFIX_PATH="${DEPS_PREFIX}" \
  -DCMAKE_INSTALL_PREFIX="${PREFIX}"

cmake --build "${BUILD_DIR}" -j"${JOBS}"
cmake --install "${BUILD_DIR}" --prefix "${PREFIX}"

echo "Installed log to: ${PREFIX}"
