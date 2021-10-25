#ifndef GFXTK_DEVICEINFO_HPP
#define GFXTK_DEVICEINFO_HPP

#include <string>
#include <vector>
#include "DeviceType.hpp"
#include "QueueFamily.hpp"

namespace gfxtk {
    class DeviceInfo {
    public:
        DeviceInfo(DeviceType type, std::string name, std::vector<QueueFamily> queueFamilies)
                : _type(type), _name(std::move(name)), _queueFamilies(std::move(queueFamilies)) {}

        [[nodiscard]]
        DeviceType type() const { return _type; }
        [[nodiscard]]
        std::string const& name() const { return _name; }
        [[nodiscard]]
        std::vector<QueueFamily> const& queueFamilies() const { return _queueFamilies; }

    private:
        DeviceType _type;
        std::string _name;
        std::vector<QueueFamily> _queueFamilies;

    };
}

#endif //GFXTK_DEVICEINFO_HPP
