#pragma once

#include "managers/ShaderManager.h"
#include "managers/TextureManager.h"
#include "rendering/Renderer.h"
#include "rendering/RendererApi.h"
#include "rendering/RenderQueue.h"

class OpenGLRenderer final : public Renderer {
public:

    OpenGLRenderer(ShaderManager& shaderManager, TextureManager& textureManager)
        : _shaderManager(shaderManager), _textureManager(textureManager) {}

    /**
     * @brief Begins the frame for rendering.
     */
    void beginFrame() override;
    
    /**
     * @brief Submits a render command to the renderer.
     * @param command The render command to submit.
     */
    void submit(const RenderCommand& command) override;
    
    /**
     * @brief Ends the frame for rendering.
     */
    void endFrame() override;
    
private:
    // Reference to the shader manager for accessing shaders during rendering
    ShaderManager& _shaderManager;
    
    // Reference to the texture manager for accessing textures during rendering
    TextureManager& _textureManager;

    // The render queue for storing submitted render commands
    RenderQueue _renderQueue;
    
    /**
     * @brief Executes the geometry rendering pass.
     */
    void executeGeometryPass();
};