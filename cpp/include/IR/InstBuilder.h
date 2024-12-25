#pragma once
#include <string>
#include <type_traits>

#include "BasicBlock.h"
#include "Constant.h"
#include "Function.h"
#include "Instruction.h"
#include "Module.h"
#include "Type.h"
#include "TypeAlias.h"

namespace sysyf {
namespace ir {
namespace detail {
template <typename T>
struct is_vec : std::false_type {};
template <typename T>
struct is_vec<Vec<T>> : std::true_type {};
};  // namespace detail
class InstBuilder {
  public:
    InstBuilder() = default;
    InstBuilder(RefPtr<Module> module, RefPtr<BasicBlock> b = nullptr) : module_{module}, block_{b} {}
    void position_at_end(RefPtr<BasicBlock> b) { block_ = b; }
    bool terminated() const { return block_->terminated(); }
    RefPtr<Module> module() const { return module_; }
    RefPtr<Function> function() const { return block_->parent(); }
    RefPtr<BasicBlock> block() const { return block_; }

    template <typename T>
    RefPtr<Constant> const_(T &&val) {
        if constexpr (std::is_integral_v<::sysyf::detail::remove_cvref_t<T>>) {
            return ConstantInt::new_(module(), val);
        } else if constexpr (std::is_floating_point_v<::sysyf::detail::remove_cvref_t<T>>) {
            return ConstantFP::new_(module(), val);
        } else if constexpr (detail::is_vec<::sysyf::detail::remove_cvref_t<T>>::value) {
            Vec<RefPtr<Constant>> value{};
            value.reserve(val.size());
            for (auto &&v : val) value.push_back(const_(v));
            return ConstantArray::new_(module(), std::move(value));
        } else {
            static_assert(false, "Unsupported Constant type");
        }
    }
    RefPtr<Instruction> fneg(RefPtr<Value> exp) {
        return Instruction::new_(block_, std::to_string(function()->id()), exp->type(), OpCode::FNeg, {exp});
    }
    RefPtr<Instruction> neg(RefPtr<Value> exp) { return sub(const_(0), exp); }
    RefPtr<Instruction> fneg(RefPtr<Value> lhs, RefPtr<Value> rhs) {
        return Instruction::new_(block_, std::to_string(function()->id()), lhs->type(), OpCode::FNeg, {lhs, rhs});
    }

    RefPtr<Instruction> add(RefPtr<Value> lhs, RefPtr<Value> rhs) {
        return Instruction::new_(block_, std::to_string(function()->id()), lhs->type(), OpCode::Add, {lhs, rhs});
    }

    RefPtr<Instruction> fadd(RefPtr<Value> lhs, RefPtr<Value> rhs) {
        return Instruction::new_(block_, std::to_string(function()->id()), lhs->type(), OpCode::FAdd, {lhs, rhs});
    }

    RefPtr<Instruction> sub(RefPtr<Value> lhs, RefPtr<Value> rhs) {
        return Instruction::new_(block_, std::to_string(function()->id()), lhs->type(), OpCode::Sub, {lhs, rhs});
    }

    RefPtr<Instruction> fsub(RefPtr<Value> lhs, RefPtr<Value> rhs) {
        return Instruction::new_(block_, std::to_string(function()->id()), lhs->type(), OpCode::FSub, {lhs, rhs});
    }

    RefPtr<Instruction> mul(RefPtr<Value> lhs, RefPtr<Value> rhs) {
        return Instruction::new_(block_, std::to_string(function()->id()), lhs->type(), OpCode::Mul, {lhs, rhs});
    }

    RefPtr<Instruction> fmul(RefPtr<Value> lhs, RefPtr<Value> rhs) {
        return Instruction::new_(block_, std::to_string(function()->id()), lhs->type(), OpCode::FMul, {lhs, rhs});
    }

    RefPtr<Instruction> udiv(RefPtr<Value> lhs, RefPtr<Value> rhs) {
        return Instruction::new_(block_, std::to_string(function()->id()), lhs->type(), OpCode::UDiv, {lhs, rhs});
    }

    RefPtr<Instruction> sdiv(RefPtr<Value> lhs, RefPtr<Value> rhs) {
        return Instruction::new_(block_, std::to_string(function()->id()), lhs->type(), OpCode::SDiv, {lhs, rhs});
    }

    RefPtr<Instruction> fdiv(RefPtr<Value> lhs, RefPtr<Value> rhs) {
        return Instruction::new_(block_, std::to_string(function()->id()), lhs->type(), OpCode::FDiv, {lhs, rhs});
    }

    RefPtr<Instruction> urem(RefPtr<Value> lhs, RefPtr<Value> rhs) {
        return Instruction::new_(block_, std::to_string(function()->id()), lhs->type(), OpCode::URem, {lhs, rhs});
    }

    RefPtr<Instruction> srem(RefPtr<Value> lhs, RefPtr<Value> rhs) {
        return Instruction::new_(block_, std::to_string(function()->id()), lhs->type(), OpCode::SRem, {lhs, rhs});
    }

    RefPtr<Instruction> frem(RefPtr<Value> lhs, RefPtr<Value> rhs) {
        return Instruction::new_(block_, std::to_string(function()->id()), lhs->type(), OpCode::FRem, {lhs, rhs});
    }

    RefPtr<Instruction> shl(RefPtr<Value> lhs, RefPtr<Value> rhs) {
        return Instruction::new_(block_, std::to_string(function()->id()), lhs->type(), OpCode::Shl, {lhs, rhs});
    }

    RefPtr<Instruction> lshr(RefPtr<Value> lhs, RefPtr<Value> rhs) {
        return Instruction::new_(block_, std::to_string(function()->id()), lhs->type(), OpCode::LShr, {lhs, rhs});
    }

    RefPtr<Instruction> ashr(RefPtr<Value> lhs, RefPtr<Value> rhs) {
        return Instruction::new_(block_, std::to_string(function()->id()), lhs->type(), OpCode::AShr, {lhs, rhs});
    }

    RefPtr<Instruction> and_(RefPtr<Value> lhs, RefPtr<Value> rhs) {
        return Instruction::new_(block_, std::to_string(function()->id()), lhs->type(), OpCode::And, {lhs, rhs});
    }

    RefPtr<Instruction> or_(RefPtr<Value> lhs, RefPtr<Value> rhs) {
        return Instruction::new_(block_, std::to_string(function()->id()), lhs->type(), OpCode::Or, {lhs, rhs});
    }

    RefPtr<Instruction> xor_(RefPtr<Value> lhs, RefPtr<Value> rhs) {
        return Instruction::new_(block_, std::to_string(function()->id()), lhs->type(), OpCode::Xor, {lhs, rhs});
    }

    RefPtr<Instruction> trunc(RefPtr<Value> source, Type target_type) {
        return CastInst::new_(block_, std::to_string(function()->id()), OpCode::Trunc, source, std::move(target_type));
    }

    RefPtr<Instruction> zext(RefPtr<Value> source, Type target_type) {
        return CastInst::new_(block_, std::to_string(function()->id()), OpCode::ZExt, source, std::move(target_type));
    }

    RefPtr<Instruction> sext(RefPtr<Value> source, Type target_type) {
        return CastInst::new_(block_, std::to_string(function()->id()), OpCode::SExt, source, std::move(target_type));
    }

    RefPtr<Instruction> fptoui(RefPtr<Value> source, Type target_type) {
        return CastInst::new_(block_, std::to_string(function()->id()), OpCode::FPToUI, source, std::move(target_type));
    }

    RefPtr<Instruction> fptosi(RefPtr<Value> source, Type target_type) {
        return CastInst::new_(block_, std::to_string(function()->id()), OpCode::FPToSI, source, std::move(target_type));
    }

    RefPtr<Instruction> uitofp(RefPtr<Value> source, Type target_type) {
        return CastInst::new_(block_, std::to_string(function()->id()), OpCode::UIToFP, source, std::move(target_type));
    }

    RefPtr<Instruction> sitofp(RefPtr<Value> source, Type target_type) {
        return CastInst::new_(block_, std::to_string(function()->id()), OpCode::SIToFP, source, std::move(target_type));
    }

    RefPtr<Instruction> fptrunc(RefPtr<Value> source, Type target_type) {
        return CastInst::new_(block_, std::to_string(function()->id()), OpCode::FPTrunc, source,
                              std::move(target_type));
    }

    RefPtr<Instruction> fpext(RefPtr<Value> source, Type target_type) {
        return CastInst::new_(block_, std::to_string(function()->id()), OpCode::FPExt, source, std::move(target_type));
    }

    RefPtr<Instruction> ptrtoint(RefPtr<Value> source, Type target_type) {
        return CastInst::new_(block_, std::to_string(function()->id()), OpCode::PtrToInt, source,
                              std::move(target_type));
    }

    RefPtr<Instruction> inttoptr(RefPtr<Value> source, Type target_type) {
        return CastInst::new_(block_, std::to_string(function()->id()), OpCode::IntToPtr, source,
                              std::move(target_type));
    }

    RefPtr<Instruction> bitcast(RefPtr<Value> source, Type target_type) {
        return CastInst::new_(block_, std::to_string(function()->id()), OpCode::BitCast, source,
                              std::move(target_type));
    }

    RefPtr<Instruction> call(RefPtr<Function> func, const Vec<RefPtr<Value>> &args) {
        return CallInst::new_(block_, std::to_string(function()->id()), func, args);
    }

    RefPtr<Instruction> ret(RefPtr<Value> ret_val = nullptr) {
        return ReturnInst::new_(block_, std::to_string(function()->id()), ret_val);
    }

    RefPtr<Instruction> icmp(ICmpType op, RefPtr<Value> lhs, RefPtr<Value> rhs) {
        return ICmpInst::new_(block_, std::to_string(function()->id()), op, lhs, rhs);
    }

    RefPtr<Instruction> fcmp(FCmpType op, RefPtr<Value> lhs, RefPtr<Value> rhs) {
        return FCmpInst::new_(block_, std::to_string(function()->id()), op, lhs, rhs);
    }

    RefPtr<Instruction> alloca_(Type t) {
        return AllocaInst::new_(block_, std::to_string(function()->id()), std::move(t));
    }

    RefPtr<Instruction> store(RefPtr<Value> value, RefPtr<Value> target) {
        return StoreInst::new_(block_, std::to_string(function()->id()), value, target);
    }

    RefPtr<Instruction> load(RefPtr<Value> source) {
        return LoadInst::new_(block_, std::to_string(function()->id()), source);
    }

    RefPtr<Instruction> gep(RefPtr<Value> source, const Vec<RefPtr<Value>> &indices) {
        return GetElementPtrInst::new_(block_, std::to_string(function()->id()), source, indices);
    }

    RefPtr<BranchInst> branch(RefPtr<Value> cond, RefPtr<BasicBlock> true_bb, RefPtr<BasicBlock> false_bb) {
        return BranchInst::new_(block_, std::to_string(function()->id()), cond, true_bb, false_bb);
    }

    RefPtr<BranchInst> branch(RefPtr<BasicBlock> bb) {
        return BranchInst::new_(block_, std::to_string(function()->id()), bb);
    }

  private:
    RefPtr<Module> module_;
    RefPtr<BasicBlock> block_;
};
}  // namespace ir
}  // namespace sysyf
