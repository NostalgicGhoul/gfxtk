#ifndef GFXTK_PIPELINECOLORBLENDATTACHMENTDESCRIPTOR_HPP
#define GFXTK_PIPELINECOLORBLENDATTACHMENTDESCRIPTOR_HPP

#include "microsoft_fix.hpp"
#include "BlendFactor.hpp"
#include "BlendOp.hpp"
#include "ColorWriteMask.hpp"

namespace gfxtk {
    struct GFXTK_EXPORT PipelineColorBlendAttachmentDescriptor {
        bool isBlendingEnabled;
        BlendFactor sourceColorBlendFactor;
        BlendFactor destinationColorBlendFactor;
        BlendOp colorBlendOp;
        BlendFactor sourceAlphaBlendFactor;
        BlendFactor destinationAlphaBlendFactor;
        BlendOp alphaBlendOp;
        ColorWriteMask colorWriteMask;

        explicit PipelineColorBlendAttachmentDescriptor(ColorWriteMask colorWriteMask)
                : PipelineColorBlendAttachmentDescriptor(
                        colorWriteMask,
                        BlendFactor::Zero,
                        BlendFactor::Zero,
                        BlendOp::Add,
                        BlendFactor::Zero,
                        BlendFactor::Zero,
                        BlendOp::Add,
                        false
                ) {}

        PipelineColorBlendAttachmentDescriptor(
                ColorWriteMask colorWriteMask,
                BlendFactor sourceColorBlendFactor,
                BlendFactor destinationColorBlendFactor,
                BlendOp colorBlendOp,
                BlendFactor sourceAlphaBlendFactor,
                BlendFactor destinationAlphaBlendFactor,
                BlendOp alphaBlendOp
        ) : PipelineColorBlendAttachmentDescriptor(
                colorWriteMask,
                sourceColorBlendFactor,
                destinationColorBlendFactor,
                colorBlendOp,
                sourceAlphaBlendFactor,
                destinationAlphaBlendFactor,
                alphaBlendOp,
                true
        ) {}

        PipelineColorBlendAttachmentDescriptor(
                ColorWriteMask colorWriteMask,
                BlendFactor sourceColorBlendFactor,
                BlendFactor destinationColorBlendFactor,
                BlendOp colorBlendOp,
                BlendFactor sourceAlphaBlendFactor,
                BlendFactor destinationAlphaBlendFactor,
                BlendOp alphaBlendOp,
                bool isBlendingEnabled
        ) : isBlendingEnabled(isBlendingEnabled),
            sourceColorBlendFactor(sourceColorBlendFactor),
            destinationColorBlendFactor(destinationColorBlendFactor),
            colorBlendOp(colorBlendOp),
            sourceAlphaBlendFactor(sourceAlphaBlendFactor),
            destinationAlphaBlendFactor(destinationAlphaBlendFactor),
            alphaBlendOp(alphaBlendOp),
            colorWriteMask(colorWriteMask) {}

    };
}

#endif //GFXTK_PIPELINECOLORBLENDATTACHMENTDESCRIPTOR_HPP
