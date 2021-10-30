#ifndef GFXTK_IMAGECOPYBUFFER_HPP
#define GFXTK_IMAGECOPYBUFFER_HPP

#include <cstdlib>
#include <gfxtk/gfxtk_internal.hpp>
#include "Buffer.hpp"

namespace gfxtk {
    struct GFXTK_EXPORT ImageCopyBuffer {
        Buffer const& buffer;
        size_t offset;
        uint32_t bytesPerRow;
        uint32_t rowsPerImage;

        ImageCopyBuffer(Buffer const& buffer, size_t offset, uint32_t bytesPerRow, uint32_t rowsPerImage)
                : buffer(buffer), offset(offset), bytesPerRow(bytesPerRow), rowsPerImage(rowsPerImage) {}

    };
}

#endif //GFXTK_IMAGECOPYBUFFER_HPP
