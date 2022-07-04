import argparse
import shutil
import subprocess
import sys
from pathlib import Path


def get_argparser():
    parser = argparse.ArgumentParser(description='Package dcmedit for macOS.')
    parser.add_argument('input', type=Path, help='path to dcmedit app bundle')
    parser.add_argument('output', type=Path, help='path to output dir')
    return parser


def validate_config(config):
    ok = True

    if not config.input.is_dir():
        print('Input must be an app bundle')
        ok = False
    if config.output.is_dir() and len(list(config.output.iterdir())) != 0:
        print('Output dir must be empty')
        ok = False

    return ok


def package_app(config):
    package_binary(config)
    package_docs(config)


def package_binary(config):
    dest = config.output / 'dcmedit.app'
    shutil.copytree(config.input, dest)
    proc = subprocess.run(['macdeployqt', dest, '-dmg'])

    if proc.returncode != 0:
        print('macdeployqt failed')
        sys.exit(1)

    shutil.rmtree(dest)


def package_docs(config):
    repo_root = Path(__file__).parent.parent.resolve()
    shutil.copy(repo_root / 'package-readme.txt', config.output / 'README.txt')
    shutil.copy(repo_root / 'LICENSE.html', config.output)


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
