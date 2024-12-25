#pragma once

#include <cstddef>
#include <ostream>
#include <stdexcept>
#include <utility>

#include "Type.h"
#include "TypeAlias.h"
#include "Value.h"

namespace sysyf {
namespace ir {
class BasicBlock;
enum class OpCode : unsigned char {
    FNeg,
    Add,
    FAdd,
    Sub,
    FSub,
    Mul,
    FMul,
    UDiv,
    SDiv,
    FDiv,
    URem,
    SRem,
    FRem,
    Shl,
    LShr,
    AShr,
    And,
    Or,
    Xor,
    Alloca,
    Load,
    Store,
    GetElementPtr,
    Trunc,
    ZExt,
    SExt,
    FPToUI,
    FPToSI,
    UIToFP,
    SIToFP,
    FPTrunc,
    FPExt,
    PtrToInt,
    IntToPtr,
    BitCast,
    ICmp,
    FCmp,
    Phi,
    Call,
    Select,
    Ret,
    Br,
    Switch
};
enum class ICmpType : unsigned char { EQ, NE, UGT, UGE, ULT, ULE, SGT, SGE, SLT, SLE };
enum class FCmpType : unsigned char { OEQ, ONE, OGT, OGE, OLT, OLE, UEQ, UNE, UGT, UGE, ULT, ULE };
class Instruction : public Value {
  protected:
    Instruction(RefPtr<BasicBlock> p, std::string name, Type t, OpCode op, Vec<RefPtr<Value>> operands)
        : Value(std::move(t), TypeID::Instruction, std::move(name)),
          parent_{p},
          code_{op},
          operands_{std::move(operands)} {}

  public:
    Instruction(const Instruction &) = delete;
    Instruction &operator=(const Instruction &) = delete;
    const Vec<RefPtr<Value>> &operands() const { return operands_; }
    RefPtr<Value> operand(std::size_t i) const { return operands_[i]; }
    OpCode op_code() const { return code_; }
    static bool classof(const Value *v) { return v->type_id() == TypeID::Instruction; }
    static RefPtr<Instruction> new_(RefPtr<BasicBlock> p, std::string name, Type t, OpCode op,
                                    Vec<RefPtr<Value>> operands);
    friend std::ostream &operator<<(std::ostream &out, const Instruction &inst);
    virtual ~Instruction() = default;

  protected:
    Vec<RefPtr<Value>> &operands() { return operands_; }

  private:
    RefPtr<BasicBlock> parent_;
    const OpCode code_;
    Vec<RefPtr<Value>> operands_;
};

class AllocaInst : public Instruction {
    AllocaInst(RefPtr<BasicBlock> p, std::string name, Type t)
        : Instruction(p, std::move(name), PointerType{std::move(t)}, OpCode::Alloca, {}) {}

  public:
    const Type &allocated_type() const { return *type().as<PointerType>()->pointee; }
    static bool classof(const Value *v) {
        const auto *i = v->as<Instruction>();
        return i && i->op_code() == OpCode::Alloca;
    }
    static RefPtr<AllocaInst> new_(RefPtr<BasicBlock> p, std::string name, Type t);
};

class StoreInst : public Instruction {
    StoreInst(RefPtr<BasicBlock> p, std::string name, RefPtr<Value> value, RefPtr<Value> target)
        : Instruction(p, std::move(name), VoidType{}, OpCode::Store, {value, target}) {}

  public:
    RefPtr<Value> value() const { return operand(0); }
    RefPtr<Value> target() const { return operand(1); }
    static bool classof(const Value *v) {
        const auto *i = v->as<Instruction>();
        return i && i->op_code() == OpCode::Alloca;
    }
    static RefPtr<StoreInst> new_(RefPtr<BasicBlock> p, std::string name, RefPtr<Value> value, RefPtr<Value> target);
};

class LoadInst : public Instruction {
    LoadInst(RefPtr<BasicBlock> p, std::string name, RefPtr<Value> source)
        : Instruction(p, std::move(name), *source->type().as<PointerType>()->pointee, OpCode::Load, {source}) {}

  public:
    static bool classof(const Value *v) {
        const auto *i = v->as<Instruction>();
        return i && i->op_code() == OpCode::Load;
    }
    static RefPtr<LoadInst> new_(RefPtr<BasicBlock> p, std::string name, RefPtr<Value> source);
};

namespace detail {
inline Type get_type_at(const Type &t, std::size_t len) {
    if (len == 0) throw std::invalid_argument{"Create a gep instruction with zero subscripts"};
    if (not t.is<PointerType>()) throw std::invalid_argument{"Create a gep instruction with non-pointer source"};
    const Type *temp = &t;
    for (; len != 0; len--) {
        if (const auto *point_type = temp->as<PointerType>()) {
            temp = point_type->pointee.get();
        } else if (const auto *array_type = temp->as<ArrayType>()) {
            temp = array_type->element_type.get();
        } else {
            throw std::invalid_argument{"Create a gep instruction with mismatched types and subscripts"};
        }
    }
    return PointerType{*temp};
}
}  // namespace detail

class GetElementPtrInst : public Instruction {
    GetElementPtrInst(RefPtr<BasicBlock> p, std::string name, RefPtr<Value> source, const Vec<RefPtr<Value>> &indices)
        : Instruction(p, std::move(name), detail::get_type_at(source->type(), indices.size()), OpCode::GetElementPtr,
                      {}) {
        operands().reserve(indices.size() + 1);
        operands().push_back(source);
        operands().insert(operands().end(), indices.begin(), indices.end());
    }

  public:
    static bool classof(const Value *v) {
        const auto *i = v->as<Instruction>();
        return i && i->op_code() == OpCode::Alloca;
    }
    static RefPtr<GetElementPtrInst> new_(RefPtr<BasicBlock> p, std::string name, RefPtr<Value> source,
                                          const Vec<RefPtr<Value>> &indices);
};

class CastInst : public Instruction {
    CastInst(RefPtr<BasicBlock> p, std::string name, OpCode op, RefPtr<Value> source, Type target_type)
        : Instruction(p, std::move(name), std::move(target_type), op, {source}) {}

  public:
    static bool classof(const Value *v) {
        const auto *i = v->as<Instruction>();
        return i && i->op_code() >= OpCode::Trunc && i->op_code() <= OpCode::BitCast;
    }
    static RefPtr<CastInst> new_(RefPtr<BasicBlock> p, std::string name, OpCode op, RefPtr<Value> source,
                                 Type target_type);
};

class ICmpInst : public Instruction {
    ICmpInst(RefPtr<BasicBlock> p, std::string name, ICmpType icmp_type, RefPtr<Value> lhs, RefPtr<Value> rhs)
        : Instruction(p, std::move(name), IntType{1}, OpCode::ICmp, {lhs, rhs}), icmp_type_{icmp_type} {}

  public:
    ICmpType icmp_type() const { return icmp_type_; }
    static bool classof(const Value *v) {
        const auto *i = v->as<Instruction>();
        return i && i->op_code() == OpCode::ICmp;
    }
    static RefPtr<ICmpInst> new_(RefPtr<BasicBlock> p, std::string name, ICmpType icmp_type, RefPtr<Value> lhs,
                                 RefPtr<Value> rhs);

  private:
    const ICmpType icmp_type_;
};

class FCmpInst : public Instruction {
    FCmpInst(RefPtr<BasicBlock> p, std::string name, FCmpType fcmp_type, RefPtr<Value> lhs, RefPtr<Value> rhs)
        : Instruction(p, std::move(name), IntType{1}, OpCode::FCmp, {lhs, rhs}), fcmp_type_{fcmp_type} {}

  public:
    FCmpType fcmp_type() const { return fcmp_type_; }
    static bool classof(const Value *v) {
        const auto *i = v->as<Instruction>();
        return i && i->op_code() == OpCode::FCmp;
    }
    static RefPtr<FCmpInst> new_(RefPtr<BasicBlock> p, std::string name, FCmpType fcmp_type, RefPtr<Value> lhs,
                                 RefPtr<Value> rhs);

  private:
    const FCmpType fcmp_type_;
};

class ReturnInst : public Instruction {
    ReturnInst(RefPtr<BasicBlock> p, std::string name, RefPtr<Value> value = nullptr)
        : Instruction(p, std::move(name), VoidType{}, OpCode::Ret, {}) {
        if (value) operands().push_back(value);
    }

  public:
    static bool classof(const Value *v) {
        const auto *i = v->as<Instruction>();
        return i && i->op_code() == OpCode::Ret;
    }
    static RefPtr<ReturnInst> new_(RefPtr<BasicBlock> p, std::string name, RefPtr<Value> value = nullptr);
};

class BranchInst : public Instruction {
    BranchInst(RefPtr<BasicBlock> p, std::string name, RefPtr<Value> cond, RefPtr<BasicBlock> true_bb,
               RefPtr<BasicBlock> false_bb)
        : Instruction(p, std::move(name), VoidType{}, OpCode::Br,
                      {cond, RefPtr<Value>(true_bb), RefPtr<Value>(false_bb)}) {}
    BranchInst(RefPtr<BasicBlock> p, std::string name, RefPtr<BasicBlock> bb)
        : Instruction(p, std::move(name), VoidType{}, OpCode::Br, {RefPtr<Value>(bb)}) {}

  public:
    static bool classof(const Value *v) {
        const auto *i = v->as<Instruction>();
        return i && i->op_code() == OpCode::Br;
    }
    static RefPtr<BranchInst> new_(RefPtr<BasicBlock> p, std::string name, RefPtr<Value> cond,
                                   RefPtr<BasicBlock> true_bb, RefPtr<BasicBlock> false_bb);
    static RefPtr<BranchInst> new_(RefPtr<BasicBlock> p, std::string name, RefPtr<BasicBlock> bb);
};

class CallInst : public Instruction {
    CallInst(RefPtr<BasicBlock> p, std::string name, RefPtr<Value> func, const Vec<RefPtr<Value>> &args)
        : Instruction(p, std::move(name), *func->type().as<FunctionType>()->ret_type, OpCode::Call, {}) {
        operands().reserve(args.size() + 1);
        operands().push_back(func);
        operands().insert(operands().end(), args.begin(), args.end());
    }

  public:
    static bool classof(const Value *v) {
        const auto *i = v->as<Instruction>();
        return i && i->op_code() == OpCode::Call;
    }
    static RefPtr<CallInst> new_(RefPtr<BasicBlock> p, std::string name, RefPtr<Value> func,
                                 const Vec<RefPtr<Value>> &args);
};

class SwitchInst : public Instruction {};
class SelectInst : public Instruction {};
class PhiInst : public Instruction {};

std::ostream &operator<<(std::ostream &out, OpCode op_code);
std::ostream &operator<<(std::ostream &out, ICmpType icmp_type);
std::ostream &operator<<(std::ostream &out, FCmpType fcmp_type);
std::ostream &operator<<(std::ostream &out, const Instruction &inst);
}  // namespace ir
}  // namespace sysyf
