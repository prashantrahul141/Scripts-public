from os import system
import concurrent.futures
from typing import TypedDict
import json


class ScriptsType(TypedDict):
    NAME: str
    PREFIX_ARGS: list[str]
    LOCATION: str
    SCRIPT: str


# getting data
with open("data.json", 'r') as f:
    data = json.loads(f.read())

scripts_data: list[ScriptsType] = data['SCRIPTS']


# makings scripts
_scripts: list[list[str]] = []
for each_script in scripts_data:
    _list = []
    if len(each_script["PREFIX_ARGS"]) > 0:
        _list.append(" && ".join(each_script['PREFIX_ARGS']))
    _list.append(f"cd {each_script['LOCATION']}")
    _list.append(f"{each_script['SCRIPT']}")

    _scripts.append([each_script["NAME"], ' && '.join(_list)])


def startProcess(cmd_: str):
    system(cmd_)


# starting processes
if __name__ == '__main__':
    with concurrent.futures.ProcessPoolExecutor() as executor:
        for _script in _scripts:
            print(f"[MAIN] Starting \"{_script[0]}\" Process")
            f = executor.submit(startProcess, _script[1])
