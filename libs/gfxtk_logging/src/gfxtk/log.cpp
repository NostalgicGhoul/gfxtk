#include "log.hpp"
#include <iostream>
#include <chrono>
#include <ctime>

void gfxtk::log::init() {

}

void gfxtk::log::deinit() {

}

void printMessage(
        std::string const& messageType,
        std::string const& file,
        std::string const& function,
        int line,
        std::string const& message
) {
    // TODO: I hate this but don't have the energy to format it by hand to YYYY MM dd HH:mm:ss... etc.
    //       Yes I have the energy to type that but in the fashion of C and C++ there isn't something as easy as
    //       `time.toString(format: ...)` so fucking annoying :)
    auto cCurrentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto cCurrentTimeStr = std::ctime(&cCurrentTime);
    std::cout << std::string(cCurrentTimeStr, 0, strlen(cCurrentTimeStr) - 1)
              << " gfxtk[" << messageType << ", " << file << ":" << line << ", " << function << "]: "
              << message << std::endl;
}

void gfxtk::log::i(std::string const& file, std::string const& function, int line, std::string const& message) {
    printMessage("INFO", file, function, line, message);
}

void gfxtk::log::d(std::string const& file, std::string const& function, int line, std::string const& message) {
#ifndef NDEBUG
    printMessage("DEBUG", file, function, line, message);
#endif
}

void gfxtk::log::w(std::string const& file, std::string const& function, int line, std::string const& message) {
    printMessage("WARN", file, function, line, message);
}

void gfxtk::log::e(std::string const& file, std::string const& function, int line, std::string const& message) {
    printMessage("ERROR", file, function, line, message);
}

void gfxtk::log::f(std::string const& file, std::string const& function, int line, std::string const& message) {
    printMessage("FATAL", file, function, line, message);
    std::exit(1);
}
