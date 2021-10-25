#include "Window.hpp"

void gfxtk_glfw_windowResizeCallback(GLFWwindow* window, int width, int height) {
    auto gfxtkWindow = reinterpret_cast<gfxtk::backend::Window*>(glfwGetWindowUserPointer(window));

    if (gfxtkWindow != nullptr) {
        gfxtkWindow->onWindowResized(width, height);
    }
}

void gfxtk::backend::Window::init() {
    glfwInit();
    // NOTE: I don't plan to ever support OpenGL or OpenGL ES, so I don't _think_ this will ever need to be changed...
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
}

void gfxtk::backend::Window::deinit() {
    glfwTerminate();
}

void gfxtk::backend::Window::pollEvents() {
    glfwPollEvents();
}

gfxtk::backend::Window::Window(
        std::string const& title,
        int width,
        int height,
        std::function<void(int, int)> onResized
) : window(glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr)),
    cachedWidth(width),
    cachedHeight(height),
    onResized(std::move(onResized)) {
    glfwSetFramebufferSizeCallback(window, gfxtk_glfw_windowResizeCallback);
    glfwSetWindowUserPointer(window, this);
}

gfxtk::backend::Window::Window(gfxtk::backend::Window&& other) noexcept  {
    window = other.window;
    cachedWidth = other.cachedWidth;
    cachedHeight = other.cachedHeight;
    other.window = nullptr;
    // Replace the entry with the new pointer
    glfwSetWindowUserPointer(window, this);
}

gfxtk::backend::Window::~Window() {
    glfwDestroyWindow(window);
    window = nullptr;
}

bool gfxtk::backend::Window::getShouldClose() const {
    return glfwWindowShouldClose(window);
}

void gfxtk::backend::Window::onWindowResized(int newWidth, int newHeight) {
    cachedWidth = newWidth;
    cachedHeight = newHeight;

    if (onResized) {
        onResized(newWidth, newHeight);
    }
}
