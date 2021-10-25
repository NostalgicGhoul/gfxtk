#ifndef GFXTK_PIPELINEVIEWPORTSTATEDESCRIPTOR_HPP
#define GFXTK_PIPELINEVIEWPORTSTATEDESCRIPTOR_HPP

#include <vector>
#include "Rect2D.hpp"
#include "Viewport.hpp"

namespace gfxtk {
    struct PipelineViewportStateDescriptor {
        std::vector<Viewport> viewports;
        std::vector<Rect2D> scissors;

        PipelineViewportStateDescriptor(Viewport viewport, Rect2D scissors)
                : viewports({viewport}), scissors({scissors}) {}
        PipelineViewportStateDescriptor(std::vector<Viewport> viewports, std::vector<Rect2D> scissors)
                : viewports(std::move(viewports)), scissors(std::move(scissors)) {}

    };
}

#endif //GFXTK_PIPELINEVIEWPORTSTATEDESCRIPTOR_HPP
