#pragma once

#include "scenes/Scene.h"

#include <memory>

// Forward declarations
class Mesh;
class Material;
class ResourceManager;

/**
 * @brief Handle type for referencing GPU buffer objects.
 *
 * Used to identify vertex buffers, index buffers, and other buffer resources.
 */
using BufferHandle = uint32_t;

/**
 * @brief Handle type for referencing GPU texture objects.
 *
 * Used to identify texture resources for sampling in shaders.
 */
using TextureHandle = uint32_t;

/**
 * @brief Handle type for referencing compiled shader programs.
 *
 * Identifies a compiled and linked shader program on the GPU.
 */
using ShaderHandle = uint32_t;

/**
 * @brief Handle type for referencing rendering pipelines.
 *
 * Encapsulates shader programs and rendering state configurations.
 */
using PipelineHandle = uint32_t;

/**
 * @brief Handle type for referencing uniform buffer objects.
 *
 * Used to identify uniform buffers for shader parameter updates.
 */
using UniformHandle = uint32_t;

enum class PolygonMode : uint32_t {
    Fill = 1,
    Line,
    Point
};

enum class CullMode : uint32_t {
    None = 0,
    Front,
    Back
};

struct RenderState {
    PolygonMode polygonMode = PolygonMode::Fill;
    CullMode cullMode = CullMode::Back;
    bool depthTestEnabled = true;
    bool depthWriteEnabled = true;
    bool blendEnabled = false;
};

/**
 * @brief Defines the render pass for a render command.
 *
 * Used to categorise rendering commands into different stages of the rendering pipeline (e.g., shadow pass, geometry pass, UI pass).
 */
enum class RenderPass : uint8_t {
    Shadow = 1,
    Geometry,
    UI
};

/**
 * @typedef PipelineHandle
 * @brief A handle representing a rendering pipeline.
 */
struct RenderCommand {
    Mesh* mesh;
    Material* material;
    glm::mat4 transform;
    RenderPass renderPass;
    RenderState renderState;
};

/**
 * @brief Struct to hold rendering statistics for performance monitoring and debugging.
 *
 * This struct can be used to track the number of draw calls, vertices rendered, and objects rendered during a frame. It can be useful for optimizing rendering performance and identifying bottlenecks in the rendering pipeline.
 */
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

    /**
     * @brief Applies the specified render state settings. This method is called for each render command to set the appropriate rendering state (e.g., polygon mode, cull mode, depth test, blending) before issuing draw calls. The implementation will depend on the specific rendering API being used and may involve setting OpenGL states, DirectX rasterizer states, or Vulkan pipeline states.
     * @param renderState The RenderState struct containing the desired rendering state settings for the current render command.
     */
    virtual void applyRenderState(const RenderState& renderState) = 0;

};