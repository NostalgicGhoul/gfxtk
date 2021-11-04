#ifndef GFXTK_BACKEND_GLFW_WINDOW_HPP
#define GFXTK_BACKEND_GLFW_WINDOW_HPP

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <string>
#include <unordered_map>
#include <functional>

namespace gfxtk::backend {
    struct Window {
        // --== Standard Backend Window Functions ==--
        static void init();
        static void deinit();
        static void pollEvents();

        Window(std::string const& title, int width, int height, std::function<void(int, int)> onFramebufferResized);
        Window(Window const&) = delete;
        Window(Window&& other) noexcept;
        ~Window();
        [[nodiscard]]
        std::string const& getTitle() const { return cachedTitle; }
        [[nodiscard]]
        int getFramebufferWidth() const { return cachedFramebufferWidth; }
        [[nodiscard]]
        int getFramebufferHeight() const { return cachedFramebufferHeight; }
        [[nodiscard]]
        bool getShouldClose() const;

        // --== GLFW-specific Window Members ==--
        GLFWwindow* window;
        std::string cachedTitle;
        int cachedFramebufferWidth;
        int cachedFramebufferHeight;
        std::function<void(int, int)> onFramebufferResized;

        void onWindowFramebufferResized(int newWidth, int newHeight);

    };
}

#endif //GFXTK_BACKEND_GLFW_WINDOW_HPP
