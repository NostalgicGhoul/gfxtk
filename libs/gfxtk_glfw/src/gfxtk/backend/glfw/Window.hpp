#ifndef GFXTK_BACKEND_GLFW_WINDOW_HPP
#define GFXTK_BACKEND_GLFW_WINDOW_HPP

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <string>
#include <unordered_map>
#include <functional>
#include <gfxtk/InputAction.hpp>
#include <gfxtk/InputAxis.hpp>
#include <gfxtk/InputButton.hpp>
#include <gfxtk/InputJoystick.hpp>
#include <gfxtk/InputPointer.hpp>

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
        float getPointerX() const { return cachedPointerX; }
        [[nodiscard]]
        float getPointerY() const { return cachedPointerY; }
        [[nodiscard]]
        bool getShouldClose() const;
        [[nodiscard]]
        float getSuggestedZoom() const { return float(cachedFramebufferWidth) / float(cachedWindowWidth); }

        void setOnButtonInput(std::function<void(InputButton, InputAction)> onButtonInput) {
            this->onButtonInput = std::move(onButtonInput);
        }
        void setOnPointerInput(std::function<void(InputPointer, InputAction)> onPointerInput) {
            this->onPointerInput = std::move(onPointerInput);
        }

        // --== GLFW-specific Window Members ==--
        GLFWwindow* window;
        std::string cachedTitle;
        int cachedFramebufferWidth;
        int cachedFramebufferHeight;
        // I'm only keeping the cached window width and height to convert the cursor location from window coordinates
        // into framebuffer coordinated.
        int cachedWindowWidth;
        int cachedWindowHeight;
        float cachedPointerX;
        float cachedPointerY;
        std::function<void(int, int)> onFramebufferResized;
        std::function<void(InputButton, InputAction)> onButtonInput;
        std::function<void(InputPointer, InputAction)> onPointerInput;

        void processWindowFramebufferResized(int newWidth, int newHeight);
        void processWindowResized(int newWidth, int newHeight);
        void processWindowCursorPositionChanged(double newPosX, double newPosY);
        void processWindowButtonInput(InputButton inputButton, InputAction inputAction);
        void processWindowPointerInput(InputPointer inputPointer, InputAction inputAction);

    };
}

#endif //GFXTK_BACKEND_GLFW_WINDOW_HPP
