#include "Window.hpp"
#include <gfxtk/log.hpp>

#ifdef GFXTK_WINDOW_BACKEND_GLFW
#include <gfxtk/backend/glfw/Window.hpp>
#else
#error target OS is not supported by any existing window backend!
#endif

std::unique_ptr<gfxtk::Window> gfxtk::Window::create(
        std::string const& title,
        int width,
        int height,
        std::function<void(int, int)> onResized
) {
    return std::unique_ptr<Window>(new Window(title, width, height, std::move(onResized)));
}

void gfxtk::Window::init() {
    GFXTK_LOG_I("initializing window backend...");
    GFXTK_LOG_I("using windowing backend `GLFW3`...");
    backend::Window::init();
}

void gfxtk::Window::deinit() {
    GFXTK_LOG_I("deinitializing window backend...");
    backend::Window::deinit();
}

void gfxtk::Window::pollEvents() {
    backend::Window::pollEvents();
}

gfxtk::Window::Window(std::string const& title, int width, int height, std::function<void(int, int)> const& onResized)
        : _backendWindow(std::make_shared<backend::Window>(title, width, height, onResized)) {
    GFXTK_LOG_I("created window with title \"" + title + "\"");
}

std::string const& gfxtk::Window::getTitle() const {
    return _backendWindow->getTitle();
}

int gfxtk::Window::getFramebufferWidth() const {
    return _backendWindow->getFramebufferWidth();
}

int gfxtk::Window::getFramebufferHeight() const {
    return _backendWindow->getFramebufferHeight();
}

glm::vec2 gfxtk::Window::getPointerPosition() const {
    return glm::vec2(
            _backendWindow->getPointerX(),
            _backendWindow->getPointerY()
    );
}

bool gfxtk::Window::getShouldClose() const {
    return _backendWindow->getShouldClose();
}

float gfxtk::Window::getSuggestedZoom() const {
    return _backendWindow->getSuggestedZoom();
}

void gfxtk::Window::setOnButtonInput(std::function<void(InputButton, InputAction)> onButtonInput) {
    _backendWindow->setOnButtonInput(std::move(onButtonInput));
}

void gfxtk::Window::setOnPointerInput(std::function<void(InputPointer, InputAction)> onPointerInput) {
    _backendWindow->setOnPointerInput(std::move(onPointerInput));
}
