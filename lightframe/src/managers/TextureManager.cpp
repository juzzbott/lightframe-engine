#include "TextureManager.h"

#include "debug/Assertions.h"
#include "rendering/RendererApi.h"
#include "rendering/Texture.h"

#include <memory>
#include <unordered_map>

TextureHandle TextureManager::loadTexture(const std::string& texturePath, const std::string& textureName) {
    std::unique_ptr<Texture2D> texture = Texture2D::create(texturePath);
    
    TextureHandle newHandle = ++_lastHandle;
    
    _textureNameMap.try_emplace(textureName, newHandle);
    _textures.try_emplace(newHandle, std::move(texture));
    return newHandle;
}

Texture& TextureManager::get(TextureHandle textureHandle) {
    LF_ASSERT_MSG(_textures.contains(textureHandle), std::format("No texture handle {} found.", textureHandle));
    
    return *_textures[textureHandle];
}