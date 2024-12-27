#include <utility>

#include "Constant.h"
#include "Module.h"
#include "TypeAlias.h"

namespace sysyf {
namespace ir {
RefPtr<ConstantInt> ConstantInt::new_(RefPtr<Module> p, int value) {
    return static_cast<RefPtr<ConstantInt>>(p->add_constant(value));
}
RefPtr<ConstantFP> ConstantFP::new_(RefPtr<Module> p, float value) {
    return static_cast<RefPtr<ConstantFP>>(p->add_constant(value));
}
RefPtr<ConstantArray> ConstantArray::new_(RefPtr<Module> p, Vec<RefPtr<Constant>> value) {
    return static_cast<RefPtr<ConstantArray>>(p->add_constant(std::move(value)));
}
}  // namespace ir
}  // namespace sysyf
