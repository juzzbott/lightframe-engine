#pragma once

#include "resources/ResourceManager.h"
#include "rendering/Renderer.h"
#include "rendering/RendererApi.h"
#include "rendering/RenderQueue.h"

class OpenGLRenderer final : public Renderer {
public:

    /**
    * @brief Constructs an OpenGLRenderer with a reference to the ResourceManager. The ResourceManager is used to access textures, shaders, and other resources during rendering.
    * @param resourceManager Reference to the ResourceManager for accessing resources during rendering.
    */
    explicit OpenGLRenderer(ResourceManager& resourceManager);

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
    // Reference to the resource manager for accessing resources during rendering
    ResourceManager& _resourceManager;

    // The render queue for storing submitted render commands
    RenderQueue _renderQueue;

    // Stats for the current frame (number of draw calls, vertices rendered, etc.)
    RenderStats _renderStats;
    
    /**
     * @brief Executes the geometry rendering pass.
     */
    void executeGeometryPass();
};