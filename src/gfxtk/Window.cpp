#include "Window.hpp"

std::unique_ptr<gfxtk::Window> gfxtk::Window::create(std::string const& title, int width, int height) {
    return std::unique_ptr<Window>(new Window(title, width, height));
}

void gfxtk::Window::init() {
    backend::Window::init();
}

void gfxtk::Window::deinit() {
    backend::Window::deinit();
}

void gfxtk::Window::pollEvents() {
    backend::Window::pollEvents();
}

gfxtk::Window::Window(std::string const& title, int width, int height)
        : _backendWindow(title, width, height) {

}
