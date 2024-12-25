#!/usr/bin/env python3
import argparse

from sysyf_ast.builder import ASTBuilder
from sysyf_ast.printer import ASTPrinter
from sysyf_ir.builder import IRBuilder
from sysyf_parser.sysyf_parser import Lark_StandAlone


def run_compiler(source_file: str, output_file: str, emit_ir: bool, emit_ast: bool):
    parser = Lark_StandAlone()
    with open(source_file) as fp:
        source_code = fp.read()
    parse_tree = parser.parse(source_code)
    ast = ASTBuilder().transform(parse_tree)

    if emit_ast:
        print(ASTPrinter().visit_Assembly(ast))
    if emit_ir:
        ir_code = IRBuilder().visit_Assembly(ast)
        with open(output_file, "w") as fp:
            fp.write(ir_code)


def main():
    parser = argparse.ArgumentParser(description="SysYF IR Compiler")
    parser.add_argument("--emit-ir", action="store_true", help="Generate LLVM IR and print it")
    parser.add_argument("--emit-ast", action="store_true", help="Print source code recovered from AST")
    parser.add_argument("-o", type=str, dest="output_file", help="Output file name", default="testcase.ll")
    parser.add_argument("input", type=str, help="Input source file", default="testcase.sy")
    args = parser.parse_args()

    run_compiler(args.input, args.output_file, args.emit_ir, args.emit_ast)


if __name__ == "__main__":
    main()
