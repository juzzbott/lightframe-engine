#pragma once

#include "rendering/Texture.h"

#include <glad/glad.h>

#include <string>

/**
 * @class OpenGLTexture2D
 * @brief OpenGL implementation of 2D textures.
 * 
 * Concrete implementation of Texture2D using OpenGL as the rendering backend.
 * Manages OpenGL texture objects and provides methods for texture operations
 * specific to OpenGL rendering.
 */
class OpenGLTexture2D final : public Texture2D {
public:

    /**
     * @brief Constructs an OpenGLTexture2D with specified texture properties.
     */
    OpenGLTexture2D(const TextureProps& textureSpec);
    
    /**
     * @brief Constructs an OpenGLTexture2D by loading from a file path.
     */
    OpenGLTexture2D(const std::string path);

    /// Virtual destructor for proper cleanup of OpenGL resources.
    virtual ~OpenGLTexture2D();
    
    /**
     * @brief Retrieves the texture properties.
     * @return Const reference to TextureProps containing texture configuration
     */
    const TextureProps& getTextureProperties() const override { return _textureProps; }
    
    /**
     * @brief Gets the width of the texture.
     * @return Texture width in pixels
     */
    const unsigned int getWidth() const override { return _width; }
    
    /**
     * @brief Gets the height of the texture.
     * @return Texture height in pixels
     */
    const unsigned int getHeight() const override { return _height; }
    
    /**
     * @brief Gets the OpenGL texture ID.
     * @return OpenGL texture handle
     */
    const unsigned int getTextureId() const override { return _textureId; }
    
    /**
     * @brief Sets texture data.
     * 
     * Uploads pixel data to the OpenGL texture object.
     * 
     * @param data Pointer to the texture data buffer
     * @param size Size of the data buffer in bytes
     */
    void setData(void* data, unsigned int size) override;
    
    /**
     * @brief Binds this texture to a specific slot.
     * 
     * Makes the texture active for rendering operations on the specified slot.
     * 
     * @param slot Texture slot to bind to (default: 0)
     */
    void bind(unsigned int slot = 0) const override;
    
    /**
     * @brief Checks if the texture has been successfully loaded.
     * @return True if the texture is initialized and ready, false otherwise
     */
    bool isLoaded() const override { return _isLoaded; }
    
private:
    // OpenGL texture handle
    GLuint _textureId;
    
    // Texture dimensions
    unsigned int _width;
    unsigned int _height;
    
    // Texture properties and configuration
    TextureProps _textureProps;
    
    // OpenGL specific formats
    GLenum _internalFormat;
    GLenum _dataFormat;
    
    // File path for texture loading
    std::string _path;
    
    bool _isLoaded = false;
};