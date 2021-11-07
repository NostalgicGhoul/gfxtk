#include "Window.hpp"

void gfxtk_glfw_windowFramebufferResizeCallback(GLFWwindow* window, int width, int height) {
    auto gfxtkWindow = reinterpret_cast<gfxtk::backend::Window*>(glfwGetWindowUserPointer(window));

    if (gfxtkWindow != nullptr) {
        gfxtkWindow->processWindowFramebufferResized(width, height);
    }
}

void gfxtk_glfw_windowResizeCallback(GLFWwindow* window, int width, int height) {
    auto gfxtkWindow = reinterpret_cast<gfxtk::backend::Window*>(glfwGetWindowUserPointer(window));

    if (gfxtkWindow != nullptr) {
        gfxtkWindow->processWindowResized(width, height);
    }
}

void gfxtk_glfw_windowCursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    auto gfxtkWindow = reinterpret_cast<gfxtk::backend::Window*>(glfwGetWindowUserPointer(window));

    if (gfxtkWindow != nullptr) {
        gfxtkWindow->processWindowCursorPositionChanged(xpos, ypos);
    }
}

void gfxtk_glfw_windowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    auto gfxtkWindow = reinterpret_cast<gfxtk::backend::Window*>(glfwGetWindowUserPointer(window));

    if (gfxtkWindow != nullptr && (action == GLFW_PRESS || action == GLFW_RELEASE)) {
        gfxtk::InputAction inputAction = gfxtk::InputAction::Release;
        gfxtk::InputButton inputButton;

        if (action == GLFW_PRESS) {
            inputAction = gfxtk::InputAction::Press;
        }

        switch (key) {
            case GLFW_KEY_A: inputButton = gfxtk::InputButton::Keyboard_A; break;
            case GLFW_KEY_B: inputButton = gfxtk::InputButton::Keyboard_B; break;
            case GLFW_KEY_C: inputButton = gfxtk::InputButton::Keyboard_C; break;
            case GLFW_KEY_D: inputButton = gfxtk::InputButton::Keyboard_D; break;
            case GLFW_KEY_E: inputButton = gfxtk::InputButton::Keyboard_E; break;
            case GLFW_KEY_F: inputButton = gfxtk::InputButton::Keyboard_F; break;
            case GLFW_KEY_G: inputButton = gfxtk::InputButton::Keyboard_G; break;
            case GLFW_KEY_H: inputButton = gfxtk::InputButton::Keyboard_H; break;
            case GLFW_KEY_I: inputButton = gfxtk::InputButton::Keyboard_I; break;
            case GLFW_KEY_J: inputButton = gfxtk::InputButton::Keyboard_J; break;
            case GLFW_KEY_K: inputButton = gfxtk::InputButton::Keyboard_K; break;
            case GLFW_KEY_L: inputButton = gfxtk::InputButton::Keyboard_L; break;
            case GLFW_KEY_M: inputButton = gfxtk::InputButton::Keyboard_M; break;
            case GLFW_KEY_N: inputButton = gfxtk::InputButton::Keyboard_N; break;
            case GLFW_KEY_O: inputButton = gfxtk::InputButton::Keyboard_O; break;
            case GLFW_KEY_P: inputButton = gfxtk::InputButton::Keyboard_P; break;
            case GLFW_KEY_Q: inputButton = gfxtk::InputButton::Keyboard_Q; break;
            case GLFW_KEY_R: inputButton = gfxtk::InputButton::Keyboard_R; break;
            case GLFW_KEY_S: inputButton = gfxtk::InputButton::Keyboard_S; break;
            case GLFW_KEY_T: inputButton = gfxtk::InputButton::Keyboard_T; break;
            case GLFW_KEY_U: inputButton = gfxtk::InputButton::Keyboard_U; break;
            case GLFW_KEY_V: inputButton = gfxtk::InputButton::Keyboard_V; break;
            case GLFW_KEY_W: inputButton = gfxtk::InputButton::Keyboard_W; break;
            case GLFW_KEY_X: inputButton = gfxtk::InputButton::Keyboard_X; break;
            case GLFW_KEY_Y: inputButton = gfxtk::InputButton::Keyboard_Y; break;
            case GLFW_KEY_Z: inputButton = gfxtk::InputButton::Keyboard_Z; break;
            case GLFW_KEY_0: inputButton = gfxtk::InputButton::Keyboard_0; break;
            case GLFW_KEY_1: inputButton = gfxtk::InputButton::Keyboard_1; break;
            case GLFW_KEY_2: inputButton = gfxtk::InputButton::Keyboard_2; break;
            case GLFW_KEY_3: inputButton = gfxtk::InputButton::Keyboard_3; break;
            case GLFW_KEY_4: inputButton = gfxtk::InputButton::Keyboard_4; break;
            case GLFW_KEY_5: inputButton = gfxtk::InputButton::Keyboard_5; break;
            case GLFW_KEY_6: inputButton = gfxtk::InputButton::Keyboard_6; break;
            case GLFW_KEY_7: inputButton = gfxtk::InputButton::Keyboard_7; break;
            case GLFW_KEY_8: inputButton = gfxtk::InputButton::Keyboard_8; break;
            case GLFW_KEY_9: inputButton = gfxtk::InputButton::Keyboard_9; break;
            case GLFW_KEY_SPACE: inputButton = gfxtk::InputButton::Keyboard_Space; break;
            case GLFW_KEY_GRAVE_ACCENT: inputButton = gfxtk::InputButton::Keyboard_Backtick; break;
            case GLFW_KEY_MINUS: inputButton = gfxtk::InputButton::Keyboard_Hyphen; break;
            case GLFW_KEY_EQUAL: inputButton = gfxtk::InputButton::Keyboard_Equals; break;
            case GLFW_KEY_LEFT_BRACKET: inputButton = gfxtk::InputButton::Keyboard_LSquare; break;
            case GLFW_KEY_RIGHT_BRACKET: inputButton = gfxtk::InputButton::Keyboard_RSquare; break;
            case GLFW_KEY_BACKSLASH: inputButton = gfxtk::InputButton::Keyboard_BSlash; break;
            case GLFW_KEY_SEMICOLON: inputButton = gfxtk::InputButton::Keyboard_Semicolon; break;
            case GLFW_KEY_APOSTROPHE: inputButton = gfxtk::InputButton::Keyboard_Apostrophe; break;
            case GLFW_KEY_COMMA: inputButton = gfxtk::InputButton::Keyboard_Comma; break;
            case GLFW_KEY_PERIOD: inputButton = gfxtk::InputButton::Keyboard_Period; break;
            case GLFW_KEY_SLASH: inputButton = gfxtk::InputButton::Keyboard_FSlash; break;
            case GLFW_KEY_LEFT_SHIFT: inputButton = gfxtk::InputButton::Keyboard_LShift; break;
            case GLFW_KEY_LEFT_CONTROL: inputButton = gfxtk::InputButton::Keyboard_LCtrl; break;
            case GLFW_KEY_LEFT_ALT: inputButton = gfxtk::InputButton::Keyboard_LAlt; break;
            case GLFW_KEY_LEFT_SUPER: inputButton = gfxtk::InputButton::Keyboard_LSuper; break;
            case GLFW_KEY_RIGHT_SHIFT: inputButton = gfxtk::InputButton::Keyboard_RShift; break;
            case GLFW_KEY_RIGHT_CONTROL: inputButton = gfxtk::InputButton::Keyboard_RCtrl; break;
            case GLFW_KEY_RIGHT_ALT: inputButton = gfxtk::InputButton::Keyboard_RAlt; break;
            case GLFW_KEY_RIGHT_SUPER: inputButton = gfxtk::InputButton::Keyboard_RSuper; break;
            case GLFW_KEY_F1: inputButton = gfxtk::InputButton::Keyboard_F1; break;
            case GLFW_KEY_F2: inputButton = gfxtk::InputButton::Keyboard_F2; break;
            case GLFW_KEY_F3: inputButton = gfxtk::InputButton::Keyboard_F3; break;
            case GLFW_KEY_F4: inputButton = gfxtk::InputButton::Keyboard_F4; break;
            case GLFW_KEY_F5: inputButton = gfxtk::InputButton::Keyboard_F5; break;
            case GLFW_KEY_F6: inputButton = gfxtk::InputButton::Keyboard_F6; break;
            case GLFW_KEY_F7: inputButton = gfxtk::InputButton::Keyboard_F7; break;
            case GLFW_KEY_F8: inputButton = gfxtk::InputButton::Keyboard_F8; break;
            case GLFW_KEY_F9: inputButton = gfxtk::InputButton::Keyboard_F9; break;
            case GLFW_KEY_F10: inputButton = gfxtk::InputButton::Keyboard_F10; break;
            case GLFW_KEY_F11: inputButton = gfxtk::InputButton::Keyboard_F11; break;
            case GLFW_KEY_F12: inputButton = gfxtk::InputButton::Keyboard_F12; break;
            case GLFW_KEY_ESCAPE: inputButton = gfxtk::InputButton::Keyboard_Escape; break;
            case GLFW_KEY_BACKSPACE: inputButton = gfxtk::InputButton::Keyboard_Backspace; break;
            case GLFW_KEY_ENTER: inputButton = gfxtk::InputButton::Keyboard_Enter; break;
            case GLFW_KEY_TAB: inputButton = gfxtk::InputButton::Keyboard_Tab; break;
            case GLFW_KEY_KP_0: inputButton = gfxtk::InputButton::Keyboard_KP_0; break;
            case GLFW_KEY_KP_1: inputButton = gfxtk::InputButton::Keyboard_KP_1; break;
            case GLFW_KEY_KP_2: inputButton = gfxtk::InputButton::Keyboard_KP_2; break;
            case GLFW_KEY_KP_3: inputButton = gfxtk::InputButton::Keyboard_KP_3; break;
            case GLFW_KEY_KP_4: inputButton = gfxtk::InputButton::Keyboard_KP_4; break;
            case GLFW_KEY_KP_5: inputButton = gfxtk::InputButton::Keyboard_KP_5; break;
            case GLFW_KEY_KP_6: inputButton = gfxtk::InputButton::Keyboard_KP_6; break;
            case GLFW_KEY_KP_7: inputButton = gfxtk::InputButton::Keyboard_KP_7; break;
            case GLFW_KEY_KP_8: inputButton = gfxtk::InputButton::Keyboard_KP_8; break;
            case GLFW_KEY_KP_9: inputButton = gfxtk::InputButton::Keyboard_KP_9; break;
            case GLFW_KEY_KP_DIVIDE: inputButton = gfxtk::InputButton::Keyboard_KP_Divide; break;
            case GLFW_KEY_KP_MULTIPLY: inputButton = gfxtk::InputButton::Keyboard_KP_Multiply; break;
            case GLFW_KEY_KP_SUBTRACT: inputButton = gfxtk::InputButton::Keyboard_KP_Subtract; break;
            case GLFW_KEY_KP_ADD: inputButton = gfxtk::InputButton::Keyboard_KP_Add; break;
            case GLFW_KEY_KP_DECIMAL: inputButton = gfxtk::InputButton::Keyboard_KP_Decimal; break;
            case GLFW_KEY_KP_ENTER: inputButton = gfxtk::InputButton::Keyboard_KP_Enter; break;
            case GLFW_KEY_UP: inputButton = gfxtk::InputButton::Keyboard_Arrow_Up; break;
            case GLFW_KEY_DOWN: inputButton = gfxtk::InputButton::Keyboard_Arrow_Down; break;
            case GLFW_KEY_LEFT: inputButton = gfxtk::InputButton::Keyboard_Arrow_Left; break;
            case GLFW_KEY_RIGHT: inputButton = gfxtk::InputButton::Keyboard_Arrow_Right; break;
            case GLFW_KEY_INSERT: inputButton = gfxtk::InputButton::Keyboard_Insert; break;
            case GLFW_KEY_DELETE: inputButton = gfxtk::InputButton::Keyboard_Delete; break;
            case GLFW_KEY_HOME: inputButton = gfxtk::InputButton::Keyboard_Home; break;
            case GLFW_KEY_END: inputButton = gfxtk::InputButton::Keyboard_End; break;
            case GLFW_KEY_PAGE_UP: inputButton = gfxtk::InputButton::Keyboard_PageUp; break;
            case GLFW_KEY_PAGE_DOWN: inputButton = gfxtk::InputButton::Keyboard_PageDown; break;
            default:
                // For unknown keys we just return so no false events are triggered.
                return;
        }

        gfxtkWindow->processWindowButtonInput(inputButton, inputAction);
    }
}

void gfxtk_glfw_windowMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    auto gfxtkWindow = reinterpret_cast<gfxtk::backend::Window*>(glfwGetWindowUserPointer(window));

    if (gfxtkWindow && (action == GLFW_PRESS || action == GLFW_RELEASE)) {
        gfxtk::InputAction inputAction = gfxtk::InputAction::Release;
        gfxtk::InputPointer inputPointer;

        if (action == GLFW_PRESS) {
            inputAction = gfxtk::InputAction::Press;
        }

        switch (button) {
            case GLFW_MOUSE_BUTTON_LEFT: inputPointer = gfxtk::InputPointer::MouseLeft; break;
            case GLFW_MOUSE_BUTTON_MIDDLE: inputPointer = gfxtk::InputPointer::MouseMiddle; break;
            case GLFW_MOUSE_BUTTON_RIGHT: inputPointer = gfxtk::InputPointer::MouseRight; break;
            default:
                // For unknown buttons we just return so no false events are triggered.
                return;
        }

        gfxtkWindow->processWindowPointerInput(inputPointer, inputAction);
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
        std::function<void(int, int)> onFramebufferResized
) : window(glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr)),
    onFramebufferResized(std::move(onFramebufferResized)) {
    glfwSetWindowUserPointer(window, this);

    glfwGetFramebufferSize(window, &cachedFramebufferWidth, &cachedFramebufferHeight);

    glfwSetFramebufferSizeCallback(window, gfxtk_glfw_windowFramebufferResizeCallback);
    glfwSetKeyCallback(window, gfxtk_glfw_windowKeyCallback);
    glfwSetMouseButtonCallback(window, gfxtk_glfw_windowMouseButtonCallback);
}

gfxtk::backend::Window::Window(gfxtk::backend::Window&& other) noexcept  {
    window = other.window;
    cachedFramebufferWidth = other.cachedFramebufferWidth;
    cachedFramebufferHeight = other.cachedFramebufferHeight;
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

void gfxtk::backend::Window::processWindowFramebufferResized(int newWidth, int newHeight) {
    cachedFramebufferWidth = newWidth;
    cachedFramebufferHeight = newHeight;

    if (onFramebufferResized) {
        onFramebufferResized(newWidth, newHeight);
    }
}

void gfxtk::backend::Window::processWindowResized(int newWidth, int newHeight) {
    cachedWindowWidth = newWidth;
    cachedWindowHeight = newHeight;
}

void gfxtk::backend::Window::processWindowCursorPositionChanged(double newPosX, double newPosY) {
    cachedPointerX = float((newPosX / cachedWindowWidth) * cachedFramebufferWidth);
    cachedPointerY = float((newPosY / cachedWindowHeight) * cachedFramebufferHeight);
}

void gfxtk::backend::Window::processWindowButtonInput(gfxtk::InputButton inputButton, gfxtk::InputAction inputAction) {
    if (onButtonInput) {
        onButtonInput(inputButton, inputAction);
    }
}

void gfxtk::backend::Window::processWindowPointerInput(
        gfxtk::InputPointer inputPointer,
        gfxtk::InputAction inputAction
) {
    if (onPointerInput) {
        onPointerInput(inputPointer, inputAction);
    }
}
