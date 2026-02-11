#pragma once

#include "managers/TextureManager.h"
#include "managers/ShaderManager.h"
#include "RendererApi.h"
#include "scenes/Scene.h"

#include <memory>

class Renderer {
public:

    void renderScene(const Scene& scene);
    
    static std::unique_ptr<Renderer> create(ShaderManager& shaderManager, TextureManager& textureManager);

protected:

    virtual void beginFrame() = 0;

    virtual void submit(const RenderCommand& command) = 0;

    virtual void endFrame() = 0;

};