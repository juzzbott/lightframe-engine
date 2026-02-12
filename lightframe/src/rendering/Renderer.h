#pragma once

#include "resources/ResourceManager.h"
#include "RendererApi.h"
#include "scenes/Scene.h"

#include <memory>

struct RenderStats {
    uint32_t drawCalls = 0;
    uint32_t verticesRendered = 0;
    uint32_t objectsRendered = 0;
};

class Renderer {
public:
    /**
     * @brief Virtual destructor for proper cleanup of derived renderer classes.
     * This ensures that when a Renderer pointer is deleted, the destructor of the derived class is called, allowing for proper resource cleanup specific to the rendering API being used.
     */
    virtual ~Renderer() = default;

    /**
     * @brief Renders the given scene. This method is responsible for submitting all renderable objects in the scene to the GPU for rendering. The implementation of this method will depend on the specific rendering API being used (e.g., OpenGL, DirectX, Vulkan).
     * @param scene The scene to render, containing game objects and a camera.
     */
    void renderScene(const Scene& scene);

    /**
     * @brief Factory method to create a Renderer instance. This method abstracts away the details of which rendering API is being used and allows for easy switching between different rendering backends. The implementation of this method will typically check the platform or configuration settings to determine which Renderer subclass to instantiate (e.g., OpenGLRenderer, DirectXRenderer).
     * @param resourceManager Reference to the ResourceManager, which may be needed by the Renderer to access textures, shaders, and other resources during rendering.
     * @return A unique pointer to a Renderer instance.
     */
    static std::unique_ptr<Renderer> create(ResourceManager& resourceManger);

protected:

    /**
     * @brief Begins a new frame for rendering. This method is called at the start of the renderScene method and is responsible for setting up any necessary state or clearing buffers before rendering begins. The implementation will depend on the specific rendering API being used.
     */
    virtual void beginFrame() = 0;

    /**
     * @brief Submits a render command to the GPU. This method is called for each renderable object in the scene and is responsible for sending the necessary data (e.g., mesh, material, transform) to the GPU for rendering. The implementation will depend on the specific rendering API being used and may involve binding vertex buffers, setting shader parameters, and issuing draw calls.
     * @param command The RenderCommand containing all necessary information for rendering a single object (mesh, material, transform, render pass).
     */
    virtual void submit(const RenderCommand& command) = 0;

    /**
     * @brief Ends the current frame for rendering. This method is called at the end of the renderScene method and is responsible for finalizing any state or presenting the rendered frame to the screen. The implementation will depend on the specific rendering API being used.
     */
    virtual void endFrame() = 0;

};