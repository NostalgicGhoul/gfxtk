#ifndef GFXTK_QUEUEFAMILY_HPP
#define GFXTK_QUEUEFAMILY_HPP

#include "microsoft_fix.hpp"
#include <cstdlib>
#include "QueueFlags.hpp"

namespace gfxtk {
    class GFXTK_EXPORT QueueFamily {
    public:
        QueueFamily(size_t id, QueueFlags flags) : _id(id), _flags(flags) {}

        [[nodiscard]]
        size_t id() const { return _id; }
        [[nodiscard]]
        QueueFlags flags() const { return _flags; }

    private:
        // TODO: This might be what causes `QueueFamily` to have to be converted to a `backed::QueueFamily` type. I'm
        //       not sure if all other APIs use a `size_t` for the queue identification. :shrug:
        size_t _id;
        QueueFlags _flags;

    };
}

#endif //GFXTK_QUEUEFAMILY_HPP
