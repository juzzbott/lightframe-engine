#pragma once

#include <memory>
#include <string>

/**
 * @enum ImageFormat
 * @brief Enumeration of supported image color formats for textures.
 */
enum class ImageFormat {
    None = 0,  ///< No format specified
    RGB8,      ///< 8-bit RGB color format
    RGBA8      ///< 8-bit RGBA color format with alpha channel
};

/**
 * @struct TextureProps
 * @brief Properties and configuration for texture creation.
 */
struct TextureProps {
    unsigned int width;              ///< Texture width in pixels
    unsigned int height;             ///< Texture height in pixels
    ImageFormat imageFormat;         ///< Color format of the texture
    bool generateMips = true;        ///< Whether to generate mipmaps for the texture
};

/**
 * @class Texture
 * @brief Abstract base class for texture resources.
 * 
 * Provides an interface for texture operations and properties that all 
 * texture implementations must support.
 */
class Texture {
public:
    /// Virtual destructor for proper cleanup of derived classes.
    virtual ~Texture() = default;
    
    /**
     * @brief Retrieves the texture properties.
     * @return Const reference to TextureProps structure containing texture configuration
     */
    virtual const TextureProps& getTextureProperties() const = 0;
    
    /**
     * @brief Gets the width of the texture.
     * @return Texture width in pixels
     */
    virtual const unsigned int getWidth() const = 0;
    
    /**
     * @brief Gets the height of the texture.
     * @return Texture height in pixels
     */
    virtual const unsigned int getHeight() const = 0;
    
    /**
     * @brief Gets the renderer-specific texture ID.
     * @return Unique identifier for this texture in the rendering API
     */
    virtual const unsigned int getTextureId() const = 0;
    
    /**
     * @brief Sets texture data.
     * 
     * @param data Pointer to the texture data buffer
     * @param size Size of the data buffer in bytes
     */
    virtual void setData(void* data, unsigned int size) = 0;
    
    /**
     * @brief Binds this texture to a specific slot.
     * 
     * @param slot Texture slot to bind to (default: 0)
     */
    virtual void bind(unsigned int slot = 0) const = 0;
    
    /**
     * @brief Checks if the texture has been successfully loaded.
     * @return True if the texture is loaded and ready for use, false otherwise
     */
    virtual bool isLoaded() const = 0;
};

/**
 * @class Texture2D
 * @brief 2D texture implementation.
 * 
 * Concrete implementation of the Texture interface for 2D textures.
 * Provides factory methods for creating textures from properties or files.
 */
class Texture2D : public Texture {
public:
    /// Virtual destructor for proper cleanup.
    virtual ~Texture2D() = default;
    
    /**
     * @brief Creates a 2D texture with the specified properties.
     * 
     * @param textureSpec Reference to TextureProps containing texture configuration
     * @return Unique pointer to the created Texture2D instance
     */
    static std::unique_ptr<Texture2D> create(const TextureProps& textureSpec);
    
    /**
     * @brief Creates a 2D texture from a file.
     * 
     * @param path File path to the texture image
     * @return Unique pointer to the created Texture2D instance loaded from file
     */
    static std::unique_ptr<Texture2D> create(const std::string path);
};