#pragma once
#include <memory>
#include <ostream>

#include "Instruction.h"
#include "Type.h"
#include "TypeAlias.h"
#include "Utils.hpp"
#include "Value.h"

namespace sysyf {
namespace ir {
class Function;
class BasicBlock : public Value {
    BasicBlock(RefPtr<Function> p, std::string block_name)
        : Value(LabelType{}, TypeID::BasicBlock, std::move(block_name)), parent_{p} {}

  public:
    RefPtr<Function> parent() const { return parent_; }
    const auto &instructions() const { return instructions_; }
    RefPtr<Instruction> append_instruction(std::unique_ptr<Instruction> &&inst) {
        instructions_.push_back(std::move(inst));
        return instructions_.rbegin()->get();
    }
    bool terminated() const {
        if (instructions_.empty()) return false;
        switch (instructions_.rbegin()->get()->op_code()) {
            case OpCode::Ret:
            case OpCode::Br:
            case OpCode::Switch: return true;
            default: return false;
        }
    }
    static bool classof(const Value *v) { return v->type_id() == TypeID::BasicBlock; }
    static RefPtr<BasicBlock> new_(RefPtr<Function> p, std::string block_name);
    friend std::ostream &operator<<(std::ostream &out, const BasicBlock &bb) {
        return out << bb.name() << ":" << join("\n    ", bb.instructions_) << "\n";
    }

    friend class Function;

  private:
    RefPtr<Function> parent_;
    Vec<std::unique_ptr<Instruction>> instructions_;
};
}  // namespace ir
}  // namespace sysyf
