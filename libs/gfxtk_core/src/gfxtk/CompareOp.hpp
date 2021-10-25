#ifndef GFXTK_COMPAREOP_HPP
#define GFXTK_COMPAREOP_HPP

namespace gfxtk {
    enum class CompareOp {
        Never = 0,
        Less,
        Equal,
        LessOrEqual,
        Greater,
        NotEqual,
        GreaterOrEqual,
        Always,
    };
}

#endif //GFXTK_COMPAREOP_HPP
