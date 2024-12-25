import logging
import os
import subprocess
import sys

import pytest

CWD = os.path.dirname(__file__)
Easy = os.path.join(CWD, "Easy")
def under_Easy(file):
    return os.path.join(Easy, file)
Compiler = os.path.join(CWD, "..", "src/main.py")
Runtime = os.path.join(CWD, "..", "runtime/runtime.c")

class SYCase:
    def __init__(self, mode: str, name: str):
        self._mode = mode
        self._name = name
        self._need_input = os.path.exists(self.in_path)
    
    def _path_under_dir(self, file: str) -> str:
        return os.path.join(CWD, self._mode, file)
    
    @property
    def need_input(self) -> bool:
        return self._need_input

    @property
    def in_path(self) -> str:
        return self._path_under_dir(self._name+".in")
    
    @property
    def sy_path(self) -> str:
        return self._path_under_dir(self._name+".sy")
    
    @property
    def out_path(self) -> str:
        return self._path_under_dir(self._name+".out")

def find_test_cases() -> list[tuple[str, str]]:
    result = []
    for dir, mode in [(os.path.join(CWD, mode), mode) for mode in ["Easy", "Medium", "Hard"]]:
        names = sorted(list(
            set(map(lambda x: x.split('.')[0], os.listdir(dir)))
        ))
        result.extend([(mode, name) for name in names])
    return result

def run_command_in_shell(cmd: str, input: None | str=None):
    return subprocess.run(
        cmd,
        input=input, text=True,
        shell=True, capture_output=True)
    
def generate_ir(test_case: SYCase, ll_path: str):
    logging.info("Generate IR...")
    compile_cmd = f"{sys.executable} {Compiler} --emit-ir -o {ll_path} {test_case.sy_path}"
    compile_proc = run_command_in_shell(compile_cmd)
    if compile_proc.returncode != 0:
        logging.error(' '.join(["Generate IR error:", compile_cmd, compile_proc.stdout, compile_proc.stderr]))
    
def generate_bin(ll_path: str, bin_path: str):
    logging.info("Generating bin...")
    clang_cmd = f"clang {ll_path} {Runtime} -o {bin_path}"
    clang_proc = run_command_in_shell(clang_cmd)
    if clang_proc.returncode != 0:
        logging.error(' '.join(["Generating bin error:", clang_cmd, clang_proc.stdout, clang_proc.stderr]))
        with open(ll_path) as ll:
            logging.error(ll.read())
    
def exec_bin(test_case: SYCase, bin_path: str):
    input_content = None
    if test_case.need_input:
        logging.info("Reading Input...")
        with open(test_case.in_path) as f:
            input_content = f.read()
    logging.info("Executing...")
    exec_cmd = run_command_in_shell(f"{bin_path}", input_content)
    with open(test_case.out_path) as f:
        exec_out = exec_cmd.stdout.strip('\n') + "\n" + str(exec_cmd.returncode) if exec_cmd.stdout != ""\
            else str(exec_cmd.returncode)
        assert exec_out == f.read().strip()

@pytest.mark.parametrize("mode, case_name", find_test_cases())
def test_compiler(mode, case_name, tmp_path, caplog):
    caplog.set_level(logging.INFO)

    test_case = SYCase(mode, case_name)
    logging.info(' '.join([mode, case_name, "need input" if test_case.need_input else "no input"]))

    ll_path = os.path.join(tmp_path, "test.ll")
    bin_path = os.path.join(tmp_path, "a.out")

    generate_ir(test_case, ll_path)
    generate_bin(ll_path, bin_path)
    exec_bin(test_case, bin_path)

