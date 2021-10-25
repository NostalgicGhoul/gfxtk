#include "LoadOp.hpp"

VkAttachmentLoadOp gfxtk::backend::LoadOp::convert(gfxtk::LoadOp loadOp) {
    switch (loadOp) {
        case gfxtk::LoadOp::DontCare:
            return VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        case gfxtk::LoadOp::Load:
            return VK_ATTACHMENT_LOAD_OP_LOAD;
        case gfxtk::LoadOp::Clear:
            return VK_ATTACHMENT_LOAD_OP_CLEAR;
    }
}
