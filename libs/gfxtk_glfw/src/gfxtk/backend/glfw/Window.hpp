#ifndef GFXTK_BACKEND_GLFW_WINDOW_HPP
#define GFXTK_BACKEND_GLFW_WINDOW_HPP

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <string>
#include <unordered_map>

namespace gfxtk::backend {
    struct Window {
        // --== Standard Backend Window Functions ==--
        static void init();
        static void deinit();
        static void pollEvents();

        Window(std::string const& title, int width, int height);
        Window(Window const&) = delete;
        Window(Window&& other) noexcept;
        ~Window();
        [[nodiscard]]
        std::string const& getTitle() const { return cachedTitle; }
        [[nodiscard]]
        int getWidth() const { return cachedWidth; }
        [[nodiscard]]
        int getHeight() const { return cachedHeight; }
        [[nodiscard]]
        bool getShouldClose() const;

        // --== GLFW-specific Window Members ==--
        static std::unordered_map<GLFWwindow*, Window*> allWindows;
        GLFWwindow* window;
        std::string cachedTitle;
        int cachedWidth;
        int cachedHeight;

        void onWindowResized(int newWidth, int newHeight);

    };
}

#endif //GFXTK_BACKEND_GLFW_WINDOW_HPP
