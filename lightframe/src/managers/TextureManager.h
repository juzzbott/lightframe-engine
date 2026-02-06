#pragma once

#include "rendering/RendererApi.h"
#include "rendering/Texture.h"

#include <memory>
#include <unordered_map>

class TextureManager {
public:
    
    /**
     * @brief Loads a texture from file and assigns it a handle.
     * @param filePath The file path to the texture source.
     * @param textureName The name to associate with the texture.
     * @return TextureHandle The handle assigned to the loaded texture.
     */
    TextureHandle loadTexture(const std::string& filePath, const std::string& textureName);
    
    /**
     * @brief Retrieves a texture by its handle.
     * @param handle The handle of the texture to retrieve.
     * @return Texture& Reference to the requested Texture object.
     */
    Texture& get(TextureHandle handle);
    
private:
    // Maps texture names to their handles and stores texture instances by handle
    std::unordered_map<std::string, TextureHandle> _textureNameMap = {};
    
    // Map of texture handles to Texture instances
    std::unordered_map<TextureHandle, std::unique_ptr<Texture>> _textures = {};
    
    // Last assigned texture handle
    TextureHandle _lastHandle = 0;

};