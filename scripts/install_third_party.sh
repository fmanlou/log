#!/usr/bin/env bash
# Build and install fmt + spdlog into project library/ (library/fmt, library/spdlog).
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
LIBRARY="${ROOT}/library"
BUILD_ROOT="${ROOT}/.third_party_build"

FMT_REF="10.2.1"
SPDLOG_REF="v1.14.1"

FMT_REPO="https://github.com/fmtlib/fmt.git"
SPDLOG_REPO="https://github.com/gabime/spdlog.git"

jobs="${JOBS:-$(nproc 2>/dev/null || echo 4)}"

cmake_install() {
  local src="$1"
  local build="$2"
  shift 2
  cmake -S "${src}" -B "${build}" "$@"
  cmake --build "${build}" -j"${jobs}"
  cmake --install "${build}"
}

install_fmt() {
  local src="${BUILD_ROOT}/fmt"
  local build="${BUILD_ROOT}/fmt-build"
  rm -rf "${src}" "${build}"
  mkdir -p "${BUILD_ROOT}"
  git clone --depth 1 --branch "${FMT_REF}" "${FMT_REPO}" "${src}"
  cmake_install "${src}" "${build}" \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX="${LIBRARY}/fmt" \
    -DFMT_TEST=OFF
}

install_spdlog() {
  local src="${BUILD_ROOT}/spdlog"
  local build="${BUILD_ROOT}/spdlog-build"
  rm -rf "${src}" "${build}"
  git clone --depth 1 --branch "${SPDLOG_REF}" "${SPDLOG_REPO}" "${src}"
  cmake_install "${src}" "${build}" \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX="${LIBRARY}/spdlog" \
    -DCMAKE_PREFIX_PATH="${LIBRARY}/fmt" \
    -DSPDLOG_BUILD_EXAMPLE=OFF \
    -DSPDLOG_BUILD_TESTS=OFF \
    -DSPDLOG_FMT_EXTERNAL=ON
}

echo "Installing third-party libraries under: ${LIBRARY}"
install_fmt
install_spdlog
echo "Done. fmt -> ${LIBRARY}/fmt"
echo "     spdlog -> ${LIBRARY}/spdlog"
