#include "IndexType.hpp"

VkIndexType gfxtk::backend::IndexType::convert(gfxtk::IndexType indexType) {
    switch (indexType) {
        case gfxtk::IndexType::Uint16:
            return VK_INDEX_TYPE_UINT16;
        case gfxtk::IndexType::Uint32:
            return VK_INDEX_TYPE_UINT32;
    }
}
