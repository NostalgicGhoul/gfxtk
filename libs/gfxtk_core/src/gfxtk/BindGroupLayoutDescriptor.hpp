#ifndef GFXTK_BINDGROUPLAYOUTDESCRIPTOR_HPP
#define GFXTK_BINDGROUPLAYOUTDESCRIPTOR_HPP

#include <vector>
#include "BindGroupLayoutEntry.hpp"

namespace gfxtk {
    struct BindGroupLayoutDescriptor {
        std::vector<BindGroupLayoutEntry> entries;

        explicit BindGroupLayoutDescriptor(std::vector<BindGroupLayoutEntry> entries)
                : entries(std::move(entries)) {}

    };
}

#endif //GFXTK_BINDGROUPLAYOUTDESCRIPTOR_HPP
