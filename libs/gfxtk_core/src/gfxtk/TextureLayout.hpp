#ifndef GFXTK_TEXTURELAYOUT_HPP
#define GFXTK_TEXTURELAYOUT_HPP

namespace gfxtk {
    enum class TextureLayout {
        Undefined,
        General,
        ColorAttachment,
        ColorAttachmentReadOnly,
        DepthStencilAttachment,
        DepthStencilReadOnly,
        ShaderReadOnly,
        TransferSource,
        TransferDestination,
        PresentSource,
    };
}

#endif //GFXTK_TEXTURELAYOUT_HPP
