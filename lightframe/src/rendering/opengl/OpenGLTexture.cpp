#include "OpenGLTexture.h"

#include <debug/Assertions.h>

#include <glad/glad.h>
#include <stb/stb_image.h>

static GLenum LfImageFormatToGlDataFormat(ImageFormat format) {
    switch (format) 
    {
        case ImageFormat::RGB8:     return GL_RGB;
        case ImageFormat::RGBA8:    return GL_RGBA;    
    }
    
    LF_ASSERT_MSG(false, "Unkown image format used for OpenGLTexture2D");
    return GL_NONE;
}

static GLenum LfImageFormatToGlInternalFormat(ImageFormat format) {
    switch (format) 
    {
        case ImageFormat::RGB8:     return GL_RGB8;
        case ImageFormat::RGBA8:    return GL_RGBA8;    
    }
    
    LF_ASSERT_MSG(false, "Unkown image format used for OpenGLTexture2D");
    return GL_NONE;
    
}

OpenGLTexture2D::OpenGLTexture2D(const TextureProps& textureProps)
    : _textureProps(textureProps), _width(textureProps.width), _height(textureProps.height) { 
        
    _internalFormat = LfImageFormatToGlInternalFormat(textureProps.imageFormat);
    _dataFormat = LfImageFormatToGlDataFormat(textureProps.imageFormat);
    
    glCreateTextures(GL_TEXTURE_2D, 1, &_textureId);
    glTextureStorage2D(_textureId, 1, _internalFormat, _width, _height);
    
    glTextureParameteri(_textureId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(_textureId, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTextureParameteri(_textureId, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(_textureId, GL_TEXTURE_WRAP_T, GL_REPEAT);    
    
}

OpenGLTexture2D::OpenGLTexture2D(const std::string path)
    : _path(path) {
        
    int width;
    int height;
    int channels;
    
    stbi_set_flip_vertically_on_load(1);
    stbi_uc* imgData = stbi_load(_path.c_str(), &width, &height, &channels, 0);
    
    if (imgData) {
        _isLoaded = true;
        
        _width = width;
        _height = height;
        
        GLenum internalFormat;
        GLenum dataFormat;
        
        if (channels == 4) {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        } else if (channels == 3) {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }
        
        _internalFormat = internalFormat;
        _dataFormat = dataFormat;
        
        LF_ASSERT_MSG(internalFormat & dataFormat, "Image format not supported for OpenGLTexture2D");
        
        
        glCreateTextures(GL_TEXTURE_2D, 1, &_textureId);
        glTextureStorage2D(_textureId, 1, _internalFormat, _width, _height);
        
        glTextureParameteri(_textureId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(_textureId, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        glTextureParameteri(_textureId, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(_textureId, GL_TEXTURE_WRAP_T, GL_REPEAT); 
        
        glTextureSubImage2D(_textureId, 0, 0, 0, _width, _height, _dataFormat, GL_UNSIGNED_BYTE, imgData);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        stbi_image_free(imgData);
    }
}

OpenGLTexture2D::~OpenGLTexture2D() {
    glDeleteTextures(1, &_textureId);
}

void OpenGLTexture2D::setData(void* data, unsigned int size) {
    unsigned int bytesPerPixel = _dataFormat == GL_RGBA ? 4 : 3;
    
    LF_ASSERT_MSG(size == _width * _height * bytesPerPixel, "Data must be entire texture.");
    
    glTextureSubImage2D(_textureId, 0, 0, 0, _width, _height, _dataFormat, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

void OpenGLTexture2D::bind(unsigned int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, _textureId);
}