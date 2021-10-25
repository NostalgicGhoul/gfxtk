#include "Texture.hpp"

std::shared_ptr<gfxtk::backend::Texture> gfxtk::backend::Texture::createRefOnly(VkImage vulkanImage) {
    return std::make_shared<Texture>(static_cast<VkDevice>(VK_NULL_HANDLE), vulkanImage);
}

gfxtk::backend::Texture::~Texture() {
    if (vulkanDevice != VK_NULL_HANDLE) {
        vkDestroyImage(vulkanDevice, vulkanImage, nullptr);
    }
}
