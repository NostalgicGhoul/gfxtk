#include <gfxtk/Window.hpp>

using namespace gfxtk;

// NOTE: THIS IS FOR TESTING ONLY
int main() {
    Window::init();

    auto window = Window::create("Hokari", 800, 600);

    while (!window->getShouldClose()) {
        Window::pollEvents();
    }

    Window::deinit();

    return 0;
}
