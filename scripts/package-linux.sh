#!/usr/bin/env bash

set -eu -o pipefail

DCMEDIT_BIN=$1
OUTPUT_DIR="$(mktemp -d)"

mkdir -p "${OUTPUT_DIR}/usr/bin"
cp "${DCMEDIT_BIN}" "${OUTPUT_DIR}/usr/bin/dcmedit"

mkdir -p "${OUTPUT_DIR}/usr/share/applications"
cat << EOF > "${OUTPUT_DIR}/usr/share/applications/dcmedit.desktop"
[Desktop Entry]
Type=Application
Name=dcmedit
Comment=DICOM editor
Exec=dcmedit
Icon=stub
Categories=Office;
EOF

mkdir -p "${OUTPUT_DIR}/usr/share/icons/hicolor/256x256/apps"
touch "${OUTPUT_DIR}/usr/share/icons/hicolor/256x256/apps/stub.png"

linuxdeployqt "${OUTPUT_DIR}/usr/share/applications/dcmedit.desktop" -appimage -no-translations
