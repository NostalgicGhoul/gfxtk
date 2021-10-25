#ifndef GFXTK_CORE_VERSION_HPP
#define GFXTK_CORE_VERSION_HPP

#include <string>

namespace gfxtk {
    class Version {
        unsigned short _major;
        unsigned short _minor;
        unsigned short _patch;

    public:
        Version(unsigned short major, unsigned short minor, unsigned short patch)
                : _major(major), _minor(minor), _patch(patch) {}

        unsigned short major() const { return _major; }
        unsigned short minor() const { return _minor; }
        unsigned short patch() const { return _patch; }

        std::string string() const {
            std::string result = std::to_string(_major) + ".";
            result += std::to_string(_minor) + ".";
            result += std::to_string(_patch);
            return result;
        }

    };
}

#endif //GFXTK_CORE_VERSION_HPP
