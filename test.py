#!/usr/bin/env python3

import argparse
import os
import subprocess
import sys


def eprint(*objects: object, sep: str = " ", end: str = "\n", flush: bool = False):
    print(*objects, sep=sep, end=end, file=sys.stderr, flush=flush)


def run_command(cmd: str, input=None):
    return subprocess.run(cmd, shell=True, capture_output=True, input=input, text=True)


def task3_eval(
    exe_path: str,
    test_dir: str,
    test_cases: dict[str, bool],
    timeout: int,
):
    eprint("===========TEST START===========")
    eprint(f"now in {test_dir}")
    succ_count = 0
    max_len = max(len(case) for case in test_cases)
    for case, need_input in test_cases.items():
        eprint(f"Case \x1b[1m{case:<{max_len}}\x1b[0m", end="")
        test_path = os.path.join(test_dir, case)
        sy_path = test_path + ".sy"
        ll_path = test_path + ".ll"
        input_path = test_path + ".in"
        output_path = test_path + ".out"

        result = run_command(f"{exe_path} --emit-ir -o {ll_path} {sy_path}")
        if result.returncode == 0:
            input_option = None
            if need_input:
                with open(input_path) as fin:
                    input_option = fin.read()
            try:
                result = run_command(f"clang -O0 -o {test_path} {ll_path} runtime/runtime.c")
                if result.returncode != 0:
                    eprint("\t\x1b[1;31mCompile Error\x1b[0m")
                    continue
                # Use the timeout command instead of subprocess's timeout option,
                # as the latter has too many bugs in its implementation.
                result = run_command(f"timeout {timeout} {test_path}", input=input_option)
                if result.returncode == 124:  # timeout
                    eprint("\t\x1b[1;31mTime Out\x1b[0m")
                    continue
                outs = result.stdout.splitlines()
                outs.append(str(result.returncode))
                outs = [line for line in outs if line]  # Remove empty line
                with open(output_path) as fp:
                    lines = fp.read().splitlines()
                answer = [line for line in lines if line]
                case_succ = outs == answer
                if case_succ:
                    eprint("\t\x1b[1;32mPass\x1b[0m")
                    succ_count += 1
                else:
                    eprint("\t\x1b[1;31mWrong Answer\x1b[0m")
            except Exception as e:
                eprint(e, end="")
                eprint("\t\x1b[31mCodeGen or CodeExecute Fail\x1b[0m")
            finally:
                _ = run_command(f"rm -rf {test_path} {test_path}.o {test_path}.ll")
        else:
            eprint("\t\x1b[1;31mIRBuild Fail\x1b[0m")
    eprint(f"\t\x1b[1m{succ_count} Passed / {len(test_cases) - succ_count} Failed\x1b[0m")
    if succ_count == len(test_cases):
        eprint(f"\t\x1b[1;32mSuccess\x1b[0m in dir {test_dir}")
    else:
        eprint(f"\t\x1b[1;31mFail\x1b[0m in dir {test_dir}")

    eprint("============TEST END============")


def main():
    parser = argparse.ArgumentParser(description="Test script")
    parser.add_argument("language", type=str, help="language", choices=["cpp", "python"])
    parser.add_argument("mode", type=str, help="Test Mode", choices=["Easy", "Medium", "Hard"])

    args = parser.parse_args()

    timeout = 30
    test_dir = os.path.join("./test", args.mode)

    items = [i.split(".")[0] for i in os.listdir(test_dir)]
    items.sort()
    test_cases = {k: os.path.isfile(os.path.join(test_dir, f"{k}.in")) for k in items}
    task3_eval(
        "./python/src/main.py" if args.language == "python" else "./cpp/build/compiler", test_dir, test_cases, timeout
    )


if __name__ == "__main__":
    main()
