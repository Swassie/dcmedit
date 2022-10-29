import subprocess
from datetime import datetime
from string import Template

from common import get_repo_root


def get_major_minor_rev():
    proc = subprocess.run(['git', 'describe', '--abbrev=0'], check=True, capture_output=True, text=True)
    tag = proc.stdout.strip()

    proc = subprocess.run(['git', 'rev-list', f'{tag}..', '--count'], check=True, capture_output=True, text=True)
    commit_count_since_tag = proc.stdout.strip()

    return f'{tag}.{commit_count_since_tag}'


def get_branch():
    proc = subprocess.run(['git', 'branch', '--show-current'], check=True, capture_output=True, text=True)
    branch = proc.stdout.strip()

    return branch


def get_commit_hash():
    proc = subprocess.run(['git', 'rev-parse', '--short', 'HEAD'], check=True, capture_output=True, text=True)
    commit_hash = proc.stdout.strip()

    return commit_hash


def get_dirty():
    proc = subprocess.run(['git', 'diff-index', '--quiet', 'HEAD', '--'])
    dirty = proc.returncode != 0

    return dirty


def get_timestamp():
    return datetime.today().isoformat(timespec='seconds')


def generate_version():
    version = get_major_minor_rev()

    if (branch := get_branch()) != 'master':
        version += f'-{branch}'

    commit_hash = get_commit_hash()
    timestamp = get_timestamp()

    if get_dirty():
        commit_hash += '-dirty'

    version += f' ({commit_hash}, {timestamp})'

    return version


def generate_app_info():
    template_map = {'version': generate_version()}
    repo_root = get_repo_root()
    app_info_template_string = (repo_root / 'src/common/App_info.cpp.tmpl').read_text()
    app_info_string = Template(app_info_template_string).substitute(template_map)
    app_info_path = repo_root / 'src/common/App_info.cpp'
    app_info_path.write_text(app_info_string)
    print(f'Generated "{app_info_path}"')


if __name__ == '__main__':
    generate_app_info()
