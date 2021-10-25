#include "StoreOp.hpp"

VkAttachmentStoreOp gfxtk::backend::StoreOp::convert(gfxtk::StoreOp storeOp) {
    switch (storeOp) {
        case gfxtk::StoreOp::DontCare:
            return VK_ATTACHMENT_STORE_OP_DONT_CARE;
        case gfxtk::StoreOp::Store:
            return VK_ATTACHMENT_STORE_OP_STORE;
    }
}
