import re

from common import get_repo_root


def get_short_version():
    repo_root = get_repo_root()
    app_info_string = (repo_root / 'src/common/App_info.cpp').read_text()
    pattern = re.compile('const char\* const App_info::version = \"(.*?)\";')
    match = pattern.search(app_info_string)
    long_version = match.group(1)

    return long_version.split()[0]


if __name__ == '__main__':
    try:
        version = get_short_version()
    except Exception:
        version = 'version-error'

    print(version, end='')
