#ifndef GFXTK_WINDOW_HPP
#define GFXTK_WINDOW_HPP

#include <memory>
#include <string>
#include <functional>
#include <gfxtk/gfxtk_internal.hpp>
#include <gfxtk/InputAction.hpp>
#include <gfxtk/InputAxis.hpp>
#include <gfxtk/InputButton.hpp>
#include <gfxtk/InputJoystick.hpp>
#include <gfxtk/InputPointer.hpp>
#include <glm/glm.hpp>

namespace gfxtk {
    namespace backend {
        struct Window;
    }

    class GFXTK_EXPORT Window {
        friend class Instance;
        friend class SwapChainConfig;

    public:
        static void init();
        static void deinit();
        static void pollEvents();

        [[nodiscard]]
        std::string const& getTitle() const;
        [[nodiscard]]
        int getFramebufferWidth() const;
        [[nodiscard]]
        int getFramebufferHeight() const;
        [[nodiscard]]
        glm::vec2 getPointerPosition() const;
        [[nodiscard]]
        bool getShouldClose() const;
        [[nodiscard]]
        float getSuggestedZoom() const;

        void setOnButtonInput(std::function<void(InputButton, InputAction)> onButtonInput);
        void setOnPointerInput(std::function<void(InputPointer, InputAction)> onPointerInput);

    private:
        static std::unique_ptr<Window> create(
                std::string const& title,
                int width,
                int height,
                std::function<void(int, int)> onResized
        );

        std::shared_ptr<backend::Window> _backendWindow;

        Window(std::string const& title, int width, int height, std::function<void(int, int)> const& onResized);

    };
}

#endif //GFXTK_WINDOW_HPP
