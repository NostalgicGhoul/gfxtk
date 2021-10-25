#ifndef GFXTK_BINDGROUPLAYOUTENTRY_HPP
#define GFXTK_BINDGROUPLAYOUTENTRY_HPP

#include <cstdint>
#include <cassert>
#include "ShaderStageFlags.hpp"
#include "BindingLayoutType.hpp"
#include "BufferBindingLayout.hpp"
#include "SamplerBindingLayout.hpp"
#include "TextureBindingLayout.hpp"
#include "StorageTextureBindingLayout.hpp"

namespace gfxtk {
    struct BindGroupLayoutEntry {
        uint32_t binding;
        ShaderStageFlags shaderStages;

        BindingLayoutType bindingType() const { return _bindingType; }
        BufferBindingLayout buffer() const {
            assert(_bindingType == BindingLayoutType::Buffer &&
                   "`buffer` called on non-buffer `BindGroupLayoutEntry`!");
            return _buffer;
        }
        SamplerBindingLayout sampler() const {
            assert(_bindingType == BindingLayoutType::Sampler &&
                   "`sampler` called on non-sampler `BindGroupLayoutEntry`!");
            return _sampler;
        }
        TextureBindingLayout texture() const {
            assert(_bindingType == BindingLayoutType::Texture &&
                   "`texture` called on non-texture `BindGroupLayoutEntry`!");
            return _texture;
        }
        StorageTextureBindingLayout storageTexture() const {
            assert(_bindingType == BindingLayoutType::Texture &&
                   "`storageTexture` called on non-storage-texture `BindGroupLayoutEntry`!");
            return _storageTexture;
        }

        BindGroupLayoutEntry(uint32_t binding, ShaderStageFlags shaderStages, BufferBindingLayout buffer)
                : binding(binding), shaderStages(shaderStages), _bindingType(BindingLayoutType::Buffer),
                  _buffer(buffer) {}
        BindGroupLayoutEntry(uint32_t binding, ShaderStageFlags shaderStages, SamplerBindingLayout sampler)
                : binding(binding), shaderStages(shaderStages), _bindingType(BindingLayoutType::Sampler),
                  _sampler(sampler) {}
        BindGroupLayoutEntry(uint32_t binding, ShaderStageFlags shaderStages, TextureBindingLayout texture)
                : binding(binding), shaderStages(shaderStages), _bindingType(BindingLayoutType::Texture),
                  _texture(texture) {}
        BindGroupLayoutEntry(uint32_t binding, ShaderStageFlags shaderStages, StorageTextureBindingLayout storageTexture)
                : binding(binding), shaderStages(shaderStages), _bindingType(BindingLayoutType::Texture),
                  _storageTexture(storageTexture) {}
        ~BindGroupLayoutEntry() {
            switch (_bindingType) {
                case BindingLayoutType::Buffer:
                    _buffer.~BufferBindingLayout();
                    break;
                case BindingLayoutType::Sampler:
                    _sampler.~SamplerBindingLayout();
                    break;
                case BindingLayoutType::Texture:
                    _texture.~TextureBindingLayout();
                    break;
                case BindingLayoutType::StorageTexture:
                    _storageTexture.~StorageTextureBindingLayout();
                    break;
            }
        }

    private:
        BindingLayoutType _bindingType;

        union {
            BufferBindingLayout _buffer;
            SamplerBindingLayout _sampler;
            TextureBindingLayout _texture;
            StorageTextureBindingLayout _storageTexture;
        };

    };
}

#endif //GFXTK_BINDGROUPLAYOUTENTRY_HPP
