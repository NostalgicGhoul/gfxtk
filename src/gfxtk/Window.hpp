#ifndef GFXTK_WINDOW_HPP
#define GFXTK_WINDOW_HPP

#include <memory>
#include <string>
#include <functional>

namespace gfxtk {
    namespace backend {
        class Window;
    }

    class Window {
        friend class Instance;
        friend class SwapChainConfig;

    public:
        static void init();
        static void deinit();
        static void pollEvents();

        [[nodiscard]]
        std::string const& getTitle() const;
        [[nodiscard]]
        int getWidth() const;
        [[nodiscard]]
        int getHeight() const;
        [[nodiscard]]
        bool getShouldClose() const;

    private:
        static std::unique_ptr<Window> create(
                std::string const& title,
                int width,
                int height,
                std::function<void(int, int)> onResized
        );

        std::shared_ptr<backend::Window> _backendWindow;

        Window(std::string const& title, int width, int height, std::function<void(int, int)> onResized);

    };
}

#endif //GFXTK_WINDOW_HPP
