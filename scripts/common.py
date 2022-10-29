import shutil
from pathlib import Path


def get_repo_root():
    return Path(__file__).parent.parent.resolve()


def package_docs(config):
    repo_root = get_repo_root()
    shutil.copy(repo_root / 'package-readme.txt', config.output / 'README.txt')
    shutil.copy(repo_root / 'LICENSE.html', config.output)
