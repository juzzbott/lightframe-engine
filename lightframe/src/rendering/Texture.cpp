#include "Texture.h"

#include "rendering/opengl/OpenGLTexture.h"

#include <memory>
#include <string>

std::unique_ptr<Texture2D> Texture2D::create(const TextureProps& textureProps) {
    return std::make_unique<OpenGLTexture2D>(textureProps);
}

std::unique_ptr<Texture2D> Texture2D::create(const std::string path) {
    return std::make_unique<OpenGLTexture2D>(path);
}