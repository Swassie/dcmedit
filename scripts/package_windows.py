import argparse
import shutil
import subprocess
import sys
from pathlib import Path

from common import package_docs


def get_argparser():
    parser = argparse.ArgumentParser(description='Package dcmedit for Windows.')
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
    shutil.copy(config.input, config.output)
    proc = subprocess.run([
        'windeployqt', '--no-quick-import', '--no-translations', '--no-system-d3d-compiler',
        '--no-virtualkeyboard', '--no-webkit2', '--no-angle', '--no-opengl-sw', config.output
    ])

    if proc.returncode != 0:
        print('windeployqt failed')
        sys.exit(1)


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
