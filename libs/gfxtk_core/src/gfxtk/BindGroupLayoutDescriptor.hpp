#ifndef GFXTK_BINDGROUPLAYOUTDESCRIPTOR_HPP
#define GFXTK_BINDGROUPLAYOUTDESCRIPTOR_HPP

#include "microsoft_fix.hpp"
#include <vector>
#include "BindGroupLayoutEntry.hpp"

namespace gfxtk {
    struct GFXTK_EXPORT BindGroupLayoutDescriptor {
        std::vector<BindGroupLayoutEntry> entries;

        explicit BindGroupLayoutDescriptor(std::vector<BindGroupLayoutEntry> entries)
                : entries(std::move(entries)) {}

    };
}

#endif //GFXTK_BINDGROUPLAYOUTDESCRIPTOR_HPP
