#ifndef GFXTK_BACKEND_VULKAN_BINDGROUPENTRY_HPP
#define GFXTK_BACKEND_VULKAN_BINDGROUPENTRY_HPP

#include <memory>
#include <gfxtk/BindingType.hpp>
#include "Sampler.hpp"
#include "TextureView.hpp"
#include "Buffer.hpp"
#include "TextureLayout.hpp"

namespace gfxtk::backend {
    struct BindGroupEntry {
        static std::shared_ptr<BindGroupEntry> create(backend::Buffer* buffer, size_t offset, size_t size) {
            return std::make_shared<BindGroupEntry>(buffer, offset, size);
        }
        static std::shared_ptr<BindGroupEntry> create(backend::Sampler* sampler) {
            return std::make_shared<BindGroupEntry>(sampler);
        }
        static std::shared_ptr<BindGroupEntry> create(backend::TextureView* textureView, gfxtk::TextureLayout textureLayout) {
            return std::make_shared<BindGroupEntry>(textureView, textureLayout);
        }

        BindGroupEntry(backend::Buffer* buffer, size_t offset, size_t size)
                : _bindingType(BindingType::Buffer), _buffer(buffer), _bufferOffset(offset), _bufferSize(size) {}
        explicit BindGroupEntry(backend::Sampler* sampler)
                : _bindingType(BindingType::Sampler), _sampler(sampler) {}
        explicit BindGroupEntry(backend::TextureView* textureView, gfxtk::TextureLayout textureLayout)
                : _bindingType(BindingType::TextureView), _textureView(textureView), _textureLayout(textureLayout) {}

        [[nodiscard]]
        BindingType bindingType() const { return _bindingType; }
        [[nodiscard]]
        Buffer* getBuffer() const {
            assert(_bindingType == BindingType::Buffer && "`getBuffer` called on non-buffer `BindGroupEntry`!");
            return _buffer;
        }
        [[nodiscard]]
        size_t getBufferOffset() const {
            assert(_bindingType == BindingType::Buffer && "`getBufferOffset` called on non-buffer `BindGroupEntry`!");
            return _bufferOffset;
        }
        [[nodiscard]]
        size_t getBufferSize() const {
            assert(_bindingType == BindingType::Buffer && "`getBufferSize` called on non-buffer `BindGroupEntry`!");
            return _bufferSize;
        }
        [[nodiscard]]
        Sampler* getSampler() const {
            assert(_bindingType == BindingType::Sampler && "`getSampler` called on non-sampler `BindGroupEntry`!");
            return _sampler;
        }
        [[nodiscard]]
        TextureView* getTextureView() const {
            assert(_bindingType == BindingType::TextureView &&
                   "`getTextureView` called on non-texture-view `BindGroupEntry`!");
            return _textureView;
        };
        [[nodiscard]]
        gfxtk::TextureLayout getTextureLayout() const {
            assert(_bindingType == BindingType::TextureView &&
                   "`getTextureLayout` called on non-texture-view `BindGroupEntry`!");
            return _textureLayout;
        }

    private:
        BindingType _bindingType;
        // All of these are basically temporary references, so I'm not going to deal with destructor calls.
        union {
            struct {
                Buffer* _buffer;
                size_t _bufferOffset;
                size_t _bufferSize;
            };
            Sampler* _sampler;
            struct {
                TextureView* _textureView;
                gfxtk::TextureLayout _textureLayout;
            };
        };

    };
}

#endif //GFXTK_BACKEND_VULKAN_BINDGROUPENTRY_HPP
