#include "Window.hpp"

std::unordered_map<GLFWwindow*, gfxtk::backend::Window*> gfxtk::backend::Window::allWindows;

void gfxtk_glfw_windowResizeCallback(GLFWwindow* window, int width, int height) {
    auto foundWindow = gfxtk::backend::Window::allWindows.find(window);

    if (foundWindow != gfxtk::backend::Window::allWindows.end()) {
        foundWindow->second->onWindowResized(width, height);
    }
}

void gfxtk::backend::Window::init() {
    glfwInit();
    // NOTE: I don't plan to ever support OpenGL or OpenGL ES, so I don't _think_ this will ever need to be changed...
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
}

void gfxtk::backend::Window::deinit() {
    // NOTE: This SHOULD trigger all created windows to be immediately destroyed.
    allWindows.clear();
    glfwTerminate();
}

void gfxtk::backend::Window::pollEvents() {
    glfwPollEvents();
}

gfxtk::backend::Window::Window(std::string const& title, int width, int height)
        : window(glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr)),
          cachedWidth(width), cachedHeight(height) {
    glfwSetWindowSizeCallback(window, gfxtk_glfw_windowResizeCallback);
    allWindows.insert({window, this});
}

gfxtk::backend::Window::Window(gfxtk::backend::Window&& other) noexcept  {
    window = other.window;
    cachedWidth = other.cachedWidth;
    cachedHeight = other.cachedHeight;
    other.window = nullptr;
    // Replace the map entry with the new pointer
    allWindows[window] = this;
}

gfxtk::backend::Window::~Window() {
    glfwDestroyWindow(window);

    if (window != nullptr) {
        // Remove the current pointer from the map (if it is contained...)
        for (auto it = allWindows.begin(); it != allWindows.end();) {
            if (it->second == this) {
                it = allWindows.erase(it);
            } else {
                ++it;
            }
        }
    }

    window = nullptr;
}

bool gfxtk::backend::Window::getShouldClose() const {
    return glfwWindowShouldClose(window);
}

void gfxtk::backend::Window::onWindowResized(int newWidth, int newHeight) {
    cachedWidth = newWidth;
    cachedHeight = newHeight;
}
