#pragma once
#include <cstddef>
#include <iostream>
#include <memory>
#include <ostream>
#include <utility>

#include "BasicBlock.h"
#include "Type.h"
#include "TypeAlias.h"
#include "Value.h"

namespace sysyf {
namespace ir {
class Module;
class Function;
class Argument : public Value {
    Argument(RefPtr<Function> p, Type t, unsigned arg_no)
        : Value(std::move(t), TypeID::Argument, std::to_string(arg_no)), parent_{p}, arg_no_{arg_no} {}

  public:
    RefPtr<Function> parent() const { return parent_; }
    unsigned arg_no() const { return arg_no_; }
    static bool classof(const Value *v) { return v->type_id() == TypeID::Argument; }
    friend std::ostream &operator<<(std::ostream &out, const Argument &arg) {
        return out << arg.type() << " %\"" << arg.name() << "\"";
    }
    friend class Function;

  private:
    RefPtr<Function> parent_;
    unsigned arg_no_;
};

class Function : public Value {
    Function(RefPtr<Module> p, FunctionType t, std::string func_name)
        : Value(std::move(t), TypeID::Function, std::move(func_name)), parent_{p}, blocks_{}, id_{} {
        for (const auto &arg_type : type().as<FunctionType>()->arg_types)
            args_.push_back(Argument{this, *arg_type, id()});
    }

  public:
    RefPtr<Module> parent() const { return parent_; }

    RefPtr<BasicBlock> append_basic_block(std::string block_name) {
        return blocks_.emplace_back(std::unique_ptr<BasicBlock>{new BasicBlock{this, std::move(block_name)}}).get();
    }

    unsigned id() { return id_++; }

    const Vec<Argument> &args() const { return args_; }
    RefPtr<Argument> arg(std::size_t i) { return &args_[i]; }

    const Type &ret_type() const { return *type().as<FunctionType>()->ret_type; }

    static bool classof(const Value *v) { return v->type_id() == TypeID::Function; }
    static RefPtr<Function> new_(RefPtr<Module> p, FunctionType t, std::string func_name);
    friend std::ostream &operator<<(std::ostream &out, const Function &arg) {
        out << (arg.blocks_.empty() ? "declare " : "define ");
        out << arg.type().as<FunctionType>()->ret_type << " @" << arg.name() << "(";
        if (not arg.args_.empty()) out << arg.args_[0];
        for (std::size_t i = 1; i < arg.args_.size(); i++) out << ", " << arg.args_[i];
        if (arg.blocks_.empty()) return out << ")\n";
        out << ") {\n";
        for (const auto &bb : arg.blocks_) out << *bb << "\n";
        return out << "}\n";
    }

  private:
    RefPtr<Module> parent_;
    Vec<Argument> args_;
    List<std::unique_ptr<BasicBlock>> blocks_;
    unsigned id_;  // for number instructions
};
}  // namespace ir
}  // namespace sysyf
