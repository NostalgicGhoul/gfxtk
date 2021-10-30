#include <gfxtk/log.hpp>
#include "StoreOp.hpp"

VkAttachmentStoreOp gfxtk::backend::StoreOp::convert(gfxtk::StoreOp storeOp) {
    switch (storeOp) {
        case gfxtk::StoreOp::DontCare:
            return VK_ATTACHMENT_STORE_OP_DONT_CARE;
        case gfxtk::StoreOp::Store:
            return VK_ATTACHMENT_STORE_OP_STORE;
        default:
            GFXTK_LOG_F("unknown `StoreOp` found in `gfxtk::backend::StoreOp::convert`!");
    }
}
