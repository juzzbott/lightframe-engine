#pragma once

#include "managers/TextureManager.h"
#include "managers/ShaderManager.h"
#include "RendererApi.h"

#include <memory>

class Renderer {
public:
    
    virtual void beginFrame() = 0;
    
    virtual void submit(const RenderCommand& command) = 0;
    
    virtual void endFrame() = 0;
    
    static std::unique_ptr<Renderer> create(ShaderManager& shaderManager, TextureManager& textureManager);
    
};