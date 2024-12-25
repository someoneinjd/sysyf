#include "BasicBlock.h"

#include "Function.h"

namespace sysyf {
namespace ir {
RefPtr<BasicBlock> BasicBlock::new_(RefPtr<Function> p, std::string block_name) {
    return p->append_basic_block(std::move(block_name));
}
}  // namespace ir
}  // namespace sysyf
