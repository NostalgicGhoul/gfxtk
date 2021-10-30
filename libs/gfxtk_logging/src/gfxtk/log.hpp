#ifndef GFXTK_LOG_HPP
#define GFXTK_LOG_HPP

#include <string>
#include <gfxtk/gfxtk_internal.hpp>

namespace gfxtk {
    class GFXTK_EXPORT log {
    public:
        static void init();
        static void deinit();

        /**
         * Log an information line
         */
        static void i(std::string const& file, std::string const& function, int line, std::string const& message);
        /**
         * Log an information line only on debug mode
         */
        static void d(std::string const& file, std::string const& function, int line, std::string const& message);
        /**
         * Log a warning message
         */
        static void w(std::string const& file, std::string const& function, int line, std::string const& message);
        /**
         * Log an error message
         */
        static void e(std::string const& file, std::string const& function, int line, std::string const& message);
        /**
         * Log a fatal error message then abort the process
         */
        static void f(std::string const& file, std::string const& function, int line, std::string const& message);

    };
}

#define GFXTK_LOG_I(message) gfxtk::log::i(__FILE__, __func__, __LINE__, (message))
#define GFXTK_LOG_D(message) gfxtk::log::d(__FILE__, __func__, __LINE__, (message))
#define GFXTK_LOG_W(message) gfxtk::log::w(__FILE__, __func__, __LINE__, (message))
#define GFXTK_LOG_E(message) gfxtk::log::e(__FILE__, __func__, __LINE__, (message))
#define GFXTK_LOG_F(message) gfxtk::log::f(__FILE__, __func__, __LINE__, (message)); std::exit(1)

#endif //GFXTK_LOG_HPP
