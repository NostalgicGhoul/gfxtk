#ifndef GFXTK_CORE_INITCONFIG_HPP
#define GFXTK_CORE_INITCONFIG_HPP

#include <string>
#include "Version.hpp"

namespace gfxtk {
    struct InitConfig {
        std::string applicationName;
        Version applicationVersion;
        std::string engineName;
        Version engineVersion;
        bool debugMode;

        // TODO: The default `engineVersion` should be defined in cmake I think
        InitConfig()
                : applicationName("gfxtk app"), applicationVersion(0, 0, 1),
                  engineName("gfxtk"), engineVersion(0, 0, 1),
                  debugMode(false) {}

    };
}

#endif //GFXTK_CORE_INITCONFIG_HPP
