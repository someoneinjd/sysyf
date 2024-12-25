#include "Instruction.h"

#include <memory>
#include <utility>

#include "BasicBlock.h"
#include "Type.h"
#include "TypeAlias.h"
#include "Value.h"

namespace sysyf {
namespace ir {
RefPtr<Instruction> Instruction::new_(RefPtr<BasicBlock> p, std::string name, Type t, OpCode op,
                                      Vec<RefPtr<Value>> operands) {
    auto inst =
        std::unique_ptr<Instruction>{new Instruction{p, std::move(name), std::move(t), op, std::move(operands)}};
    return p->append_instruction(std::move(inst));
}

RefPtr<AllocaInst> AllocaInst::new_(RefPtr<BasicBlock> p, std::string name, Type t) {
    auto inst = std::unique_ptr<Instruction>{new AllocaInst{p, std::move(name), std::move(t)}};
    return static_cast<RefPtr<AllocaInst>>(p->append_instruction(std::move(inst)));
}

RefPtr<StoreInst> StoreInst::new_(RefPtr<BasicBlock> p, std::string name, RefPtr<Value> value, RefPtr<Value> target) {
    auto inst = std::unique_ptr<Instruction>{new StoreInst{p, std::move(name), value, target}};
    return static_cast<RefPtr<StoreInst>>(p->append_instruction(std::move(inst)));
}

RefPtr<LoadInst> LoadInst::new_(RefPtr<BasicBlock> p, std::string name, RefPtr<Value> source) {
    auto inst = std::unique_ptr<Instruction>{new LoadInst{p, std::move(name), source}};
    return static_cast<RefPtr<LoadInst>>(p->append_instruction(std::move(inst)));
}

RefPtr<GetElementPtrInst> GetElementPtrInst::new_(RefPtr<BasicBlock> p, std::string name, RefPtr<Value> source,
                                                  const Vec<RefPtr<Value>> &indices) {
    auto inst = std::unique_ptr<Instruction>{new GetElementPtrInst{p, std::move(name), source, std::move(indices)}};
    return static_cast<RefPtr<GetElementPtrInst>>(p->append_instruction(std::move(inst)));
}

RefPtr<CastInst> CastInst::new_(RefPtr<BasicBlock> p, std::string name, OpCode op, RefPtr<Value> source,
                                Type target_type) {
    auto inst = std::unique_ptr<Instruction>{new CastInst{p, std::move(name), op, source, std::move(target_type)}};
    return static_cast<RefPtr<CastInst>>(p->append_instruction(std::move(inst)));
}

RefPtr<ICmpInst> ICmpInst::new_(RefPtr<BasicBlock> p, std::string name, ICmpType icmp_type, RefPtr<Value> lhs,
                                RefPtr<Value> rhs) {
    auto inst = std::unique_ptr<Instruction>{new ICmpInst{p, std::move(name), icmp_type, lhs, rhs}};
    return static_cast<RefPtr<ICmpInst>>(p->append_instruction(std::move(inst)));
}

RefPtr<FCmpInst> FCmpInst::new_(RefPtr<BasicBlock> p, std::string name, FCmpType fcmp_type, RefPtr<Value> lhs,
                                RefPtr<Value> rhs) {
    auto inst = std::unique_ptr<Instruction>{new FCmpInst{p, std::move(name), fcmp_type, lhs, rhs}};
    return static_cast<RefPtr<FCmpInst>>(p->append_instruction(std::move(inst)));
}

RefPtr<ReturnInst> ReturnInst::new_(RefPtr<BasicBlock> p, std::string name, RefPtr<Value> value) {
    auto inst = std::unique_ptr<Instruction>{new ReturnInst{p, std::move(name), value}};
    return static_cast<RefPtr<ReturnInst>>(p->append_instruction(std::move(inst)));
}

RefPtr<BranchInst> BranchInst::new_(RefPtr<BasicBlock> p, std::string name, RefPtr<Value> cond,
                                    RefPtr<BasicBlock> true_bb, RefPtr<BasicBlock> false_bb) {
    auto inst = std::unique_ptr<Instruction>{new BranchInst{p, std::move(name), cond, true_bb, false_bb}};
    return static_cast<RefPtr<BranchInst>>(p->append_instruction(std::move(inst)));
}

RefPtr<BranchInst> BranchInst::new_(RefPtr<BasicBlock> p, std::string name, RefPtr<BasicBlock> bb) {
    auto inst = std::unique_ptr<Instruction>{new BranchInst{p, std::move(name), bb}};
    return static_cast<RefPtr<BranchInst>>(p->append_instruction(std::move(inst)));
}

RefPtr<CallInst> CallInst::new_(RefPtr<BasicBlock> p, std::string name, RefPtr<Value> func,
                                const Vec<RefPtr<Value>> &args) {
    auto inst = std::unique_ptr<Instruction>{new CallInst{p, std::move(name), func, args}};
    return static_cast<RefPtr<CallInst>>(p->append_instruction(std::move(inst)));
}

std::ostream &operator<<(std::ostream &out, OpCode op_code) {
    switch (op_code) {
        case OpCode::FNeg: return out << "fneg";
        case OpCode::Add: return out << "add";
        case OpCode::FAdd: return out << "fadd";
        case OpCode::Sub: return out << "sub";
        case OpCode::FSub: return out << "fsub";
        case OpCode::Mul: return out << "mul";
        case OpCode::FMul: return out << "fmul";
        case OpCode::UDiv: return out << "udiv";
        case OpCode::SDiv: return out << "sdiv";
        case OpCode::FDiv: return out << "fdiv";
        case OpCode::URem: return out << "urem";
        case OpCode::SRem: return out << "srem";
        case OpCode::FRem: return out << "frem";
        case OpCode::Shl: return out << "shl";
        case OpCode::LShr: return out << "lshr";
        case OpCode::AShr: return out << "ashr";
        case OpCode::And: return out << "and";
        case OpCode::Or: return out << "or";
        case OpCode::Xor: return out << "xor";
        case OpCode::Alloca: return out << "alloca";
        case OpCode::Load: return out << "load";
        case OpCode::Store: return out << "store";
        case OpCode::GetElementPtr: return out << "getelementptr";
        case OpCode::Trunc: return out << "trunc";
        case OpCode::ZExt: return out << "zext";
        case OpCode::SExt: return out << "sext";
        case OpCode::FPToUI: return out << "fptoui";
        case OpCode::FPToSI: return out << "fptosi";
        case OpCode::UIToFP: return out << "uitofp";
        case OpCode::SIToFP: return out << "sitofp";
        case OpCode::FPTrunc: return out << "fptrunc";
        case OpCode::FPExt: return out << "fpext";
        case OpCode::PtrToInt: return out << "ptrtoint";
        case OpCode::IntToPtr: return out << "inttoptr";
        case OpCode::BitCast: return out << "bitcast";
        case OpCode::ICmp: return out << "icmp";
        case OpCode::FCmp: return out << "fcmp";
        case OpCode::Phi: return out << "phi";
        case OpCode::Call: return out << "call";
        case OpCode::Select: return out << "select";
        case OpCode::Ret: return out << "ret";
        case OpCode::Br: return out << "br";
        case OpCode::Switch: return out << "switch";
    }
}
std::ostream &operator<<(std::ostream &out, ICmpType icmp_type) {
    switch (icmp_type) {
        case ICmpType::EQ: return out << "eq";
        case ICmpType::NE: return out << "ne";
        case ICmpType::UGT: return out << "ugt";
        case ICmpType::UGE: return out << "uge";
        case ICmpType::ULT: return out << "ult";
        case ICmpType::ULE: return out << "ule";
        case ICmpType::SGT: return out << "sgt";
        case ICmpType::SGE: return out << "sge";
        case ICmpType::SLT: return out << "slt";
        case ICmpType::SLE: return out << "sle";
    }
}
std::ostream &operator<<(std::ostream &out, FCmpType fcmp_type) {
    switch (fcmp_type) {
        case FCmpType::OEQ: return out << "oeq";
        case FCmpType::ONE: return out << "one";
        case FCmpType::OGT: return out << "ogt";
        case FCmpType::OGE: return out << "oge";
        case FCmpType::OLT: return out << "olt";
        case FCmpType::OLE: return out << "ole";
        case FCmpType::UEQ: return out << "ueq";
        case FCmpType::UNE: return out << "une";
        case FCmpType::UGT: return out << "ugt";
        case FCmpType::UGE: return out << "uge";
        case FCmpType::ULT: return out << "ult";
        case FCmpType::ULE: return out << "ule";
    }
}

static std::string get_reference(RefPtr<const Value> val) {
    switch (val->type_id()) {
        case Value::TypeID::Constant: return val->name();
        case Value::TypeID::GlobalVariable: return "@" + val->name();
        case Value::TypeID::Function: return "@" + val->name();
        case Value::TypeID::BasicBlock: return "%" + val->name();
        default: return "%\"" + val->name() + "\"";
    }
}

std::ostream &operator<<(std::ostream &out, const Instruction &inst) {
    if (not inst.type().is<VoidType>()) out << "%\"" << inst.name() << "\" = ";
    switch (inst.op_code()) {
        case OpCode::Alloca: return out << "alloca " << inst.type().as<PointerType>()->pointee;
        case OpCode::Store:
            return out << "store " << inst.operand(0)->type() << " " << get_reference(inst.operand(0)) << ", "
                       << inst.operand(1)->type() << " " << get_reference(inst.operand(1));
        case OpCode::Load: return out << "load " << inst.type() << ", " <<  inst.operand(0)->type() << " " << get_reference(inst.operand(0));
        case OpCode::GetElementPtr: {
            out << "getelementptr inbounds " << inst.operand(0)->type().as<PointerType>()->pointee << ", "
                << inst.operand(0)->type() << "  " << get_reference(inst.operand(0));
            for (std::size_t i = 1; i < inst.operands().size(); i++)
                out << ", " << inst.operand(i)->type() << " " << get_reference(inst.operand(i));
            return out;
        }
        case OpCode::Br: {
            out << "br " << inst.operand(0)->type() << " " << get_reference(inst.operand(0));
            for (std::size_t i = 1; i < inst.operands().size(); i++)
                out << ", " << inst.operand(i)->type() << " " << get_reference(inst.operand(i));
            return out;
        }
        case OpCode::Ret: {
            if (inst.operands().empty()) return out << "ret void";
            return out << "ret " << inst.operand(0)->type() << " " << get_reference(inst.operand(0));
        }
        case OpCode::Call: {
            out << "call " << inst.operand(0)->type().as<FunctionType>()->ret_type << " " << get_reference(inst.operand(0))
                << "(";
            if (inst.operands().size() > 1) out << inst.operand(1)->type() << " " << get_reference(inst.operand(1));
            for (std::size_t i = 2; i < inst.operands().size(); i++)
                out << ", " << inst.operand(i)->type() << " " << get_reference(inst.operand(i));
            return out << ")";
        }
        case OpCode::ICmp:
            return out << "icmp " << inst.as<ICmpInst>()->icmp_type() << " " << inst.operand(0)->type() << " "
                       << get_reference(inst.operand(0)) << ", " << get_reference(inst.operand(1));
        case OpCode::FCmp:
            return out << "fcmp " << inst.as<FCmpInst>()->fcmp_type() << " " << inst.operand(0)->type() << " "
                       << get_reference(inst.operand(0)) << ", " << get_reference(inst.operand(1));
        case OpCode::Trunc:
        case OpCode::ZExt:
        case OpCode::SExt:
        case OpCode::FPToUI:
        case OpCode::FPToSI:
        case OpCode::UIToFP:
        case OpCode::SIToFP:
        case OpCode::FPTrunc:
        case OpCode::FPExt:
        case OpCode::PtrToInt:
        case OpCode::IntToPtr:
        case OpCode::BitCast:
            return out << inst.op_code() << " " << inst.operand(0)->type() << " " << get_reference(inst.operand(0))
                       << " to " << inst.type();
        case OpCode::Select:
        case OpCode::Phi:
        case OpCode::Switch:
        default: {
            out << inst.op_code() << " " << inst.operand(0)->type() << " " << get_reference(inst.operand(0));
            for (std::size_t i = 1; i < inst.operands().size(); i++) out << ", " << get_reference(inst.operand(i));
            return out;
        }
    }
}
}  // namespace ir
}  // namespace sysyf
