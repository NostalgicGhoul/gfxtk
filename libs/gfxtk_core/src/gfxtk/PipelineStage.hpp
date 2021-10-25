#ifndef GFXTK_PIPELINESTAGE_HPP
#define GFXTK_PIPELINESTAGE_HPP

namespace gfxtk {
    // TODO: This is only used for semaphores. I'm not sure how granular we can be with Metal's semaphores so this may
    //       end up being deleted...
    enum class PipelineStage {
        BottomOfPipe,
        TopOfPipe,
        ColorAttachment,
    };
}

#endif //GFXTK_PIPELINESTAGE_HPP
