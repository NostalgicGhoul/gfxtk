#ifndef GFXTK_WINDOW_HPP
#define GFXTK_WINDOW_HPP

#include <gfxtk/backend/glfw/Window.hpp>
#include <memory>
#include <string>

namespace gfxtk {
    class Window {
    public:
        static std::unique_ptr<Window> create(std::string const& title, int width, int height);

        static void init();
        static void deinit();
        static void pollEvents();

        [[nodiscard]]
        std::string const& getTitle() const { return _backendWindow.getTitle(); }
        [[nodiscard]]
        int getWidth() const { return _backendWindow.getWidth(); }
        [[nodiscard]]
        int getHeight() const { return _backendWindow.getHeight(); }
        [[nodiscard]]
        bool getShouldClose() const { return _backendWindow.getShouldClose(); }

    private:
        backend::Window _backendWindow;

        Window(std::string const& title, int width, int height);

    };
}

#endif //GFXTK_WINDOW_HPP
