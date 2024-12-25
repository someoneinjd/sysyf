#include <fstream>
#include <string>

#include "ANTLRInputStream.h"
#include "ASTBuilder.h"
#include "ASTPrinter.h"
#include "CommonTokenStream.h"
#include "IRBuilder.h"
#include "Module.h"
#include "SysYFLexer.h"
#include "SysYFParser.h"
#include "cxxopts.hpp"

int main(int argc, const char **argv) {
    cxxopts::Options cmd_opt{"compiler", "A SysYF Compiler"};
    cmd_opt.add_options()("input", "source file", cxxopts::value<std::string>()->default_value("test.sy"));
    cmd_opt.add_options()("emit-ir", "Generate IR");
    cmd_opt.add_options()("emit-ast", "Generate AST");
    cmd_opt.add_options()("o,output", "Output file", cxxopts::value<std::string>()->default_value("test.ll"));
    cmd_opt.add_options()("h,help", "Print usage");
    cmd_opt.parse_positional({"input"});
    auto args = cmd_opt.parse(argc, argv);
    if (args.count("help")) {
        std::cout << cmd_opt.help() << "\n";
        return 0;
    }

    std::ifstream input{args["input"].as<std::string>()};
    auto i = antlr4::ANTLRInputStream(input);
    auto lexer = SysYFLexer{&i};
    antlr4::CommonTokenStream tokens{&lexer};
    SysYFParser parser{&tokens};
    auto *parse_tree = parser.comp_unit();

    auto ast_builder = sysyf::ast::ASTBuilder();
    auto ast = ast_builder.build(parse_tree);

    if (args["emit-ast"].as<bool>()) {
        sysyf::ast::ASTPrinter p{};
        std::cout << p.visit(&ast);
    }

    if (args["emit-ir"].as<bool>()) {
        sysyf::ir::Module m{};
        sysyf::ir::IRBuilder builder{&m};
        builder.visit(&ast);
        std::ofstream output{args["output"].as<std::string>()};
        output << m;
    }
}
