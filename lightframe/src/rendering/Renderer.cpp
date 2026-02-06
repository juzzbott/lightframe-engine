#include "Renderer.h"

#include "managers/ShaderManager.h"
#include "managers/TextureManager.h"
#include "rendering/opengl/OpenGLRenderer.h"

#include <memory>

std::unique_ptr<Renderer> Renderer::create(ShaderManager& shaderManager, TextureManager& textureManager) {
    return std::make_unique<OpenGLRenderer>(shaderManager, textureManager);
}