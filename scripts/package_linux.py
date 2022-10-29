import argparse
import shutil
import subprocess
import sys
from pathlib import Path
from tempfile import TemporaryDirectory

from common import package_docs


def get_argparser():
    parser = argparse.ArgumentParser(description='Package dcmedit for Linux.')
    parser.add_argument('input', type=Path, help='path to dcmedit binary')
    parser.add_argument('output', type=Path, help='path to output dir')
    return parser


def validate_config(config):
    ok = True

    if not config.input.is_file():
        print('Input must be a file')
        ok = False
    if config.output.is_dir() and len(list(config.output.iterdir())) != 0:
        print('Output dir must be empty')
        ok = False

    return ok


def package_app(config):
    package_binary(config)
    package_docs(config)


def package_binary(config):
    with TemporaryDirectory() as d:
        temp_dir = Path(d)
        desktop_file = setup_app_dir(config, temp_dir)
        proc = subprocess.run(['linuxdeployqt', desktop_file, '-appimage', '-no-translations'], cwd=temp_dir)

        if proc.returncode != 0:
            print('linuxdeployqt failed')
            sys.exit(1)

        app_image = temp_dir / 'dcmedit-x86_64.AppImage'
        shutil.copy(app_image, config.output / 'dcmedit.AppImage')


def setup_app_dir(config, target_dir):
    bin_dir = target_dir / 'usr/bin'
    bin_dir.mkdir(parents=True)
    shutil.copy(config.input, bin_dir)

    desktop_dir = target_dir / 'usr/share/applications'
    desktop_dir.mkdir(parents=True)
    desktop_file = desktop_dir / 'dcmedit.desktop'
    desktop_content = """
[Desktop Entry]
Type=Application
Name=dcmedit
Comment=DICOM editor
Exec=dcmedit
Icon=stub
Categories=Office;
"""
    desktop_file.write_text(desktop_content)

    icon_dir = target_dir / 'usr/share/icons/hicolor/256x256/apps'
    icon_dir.mkdir(parents=True)
    icon_file = icon_dir / 'stub.png'
    icon_file.touch()

    return desktop_file


def main():
    parser = get_argparser()
    config = parser.parse_args()
    if not validate_config(config):
        parser.print_help()
        sys.exit(1)

    config.output.mkdir(exist_ok=True, parents=True)
    package_app(config)


if __name__ == '__main__':
    main()
