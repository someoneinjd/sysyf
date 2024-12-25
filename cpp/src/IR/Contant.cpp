#include <memory>
#include <utility>

#include "Constant.h"
#include "Module.h"
#include "TypeAlias.h"

namespace sysyf {
namespace ir {
RefPtr<ConstantInt> ConstantInt::new_(RefPtr<Module> p, int value) {
    auto const_ = std::unique_ptr<Constant>(new ConstantInt{p, value});
    return static_cast<RefPtr<ConstantInt>>(p->add_constant(std::move(const_)));
}
RefPtr<ConstantFP> ConstantFP::new_(RefPtr<Module> p, float value) {
    auto const_ = std::unique_ptr<Constant>(new ConstantFP{p, value});
    return static_cast<RefPtr<ConstantFP>>(p->add_constant(std::move(const_)));
}
RefPtr<ConstantArray> ConstantArray::new_(RefPtr<Module> p, Vec<RefPtr<Constant>> value) {
    auto const_ = std::unique_ptr<Constant>(new ConstantArray{p, std::move(value)});
    return static_cast<RefPtr<ConstantArray>>(p->add_constant(std::move(const_)));
}
}  // namespace ir
}  // namespace sysyf
