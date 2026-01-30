#pragma once

#include <glm/glm.hpp>
#include <variant>

class Mesh;
class Material;

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

/**
 * @brief Defines the type of geometric primitives to render.
 * 
 * Specifies how vertex data should be interpreted during draw calls.
 */
enum class PrimitiveType {
    Triangles,  ///< Interpret vertices as triangles (3 vertices per primitive)
    Lines       ///< Interpret vertices as lines (2 vertices per primitive)
};

/**
 * @brief Command to bind a rendering pipeline.
 * 
 * Activates the specified pipeline for subsequent draw operations.
 */
struct BindPipelineCommand {
    PipelineHandle pipeline;
};

/**
 * @brief Command to bind a vertex buffer.
 * 
 * Sets the active vertex buffer for vertex attribute data.
 */
struct BindVertexBufferCommand {
    BufferHandle vertexBuffer;
};

/**
 * @brief Command to bind an index buffer.
 * 
 * Sets the active index buffer for indexed draw calls.
 */
struct BindIndexBufferCommand {
    BufferHandle indexBuffer;
};

/**
 * @brief Command to bind a uniform buffer to a binding point.
 * 
 * Makes a uniform buffer available to shaders at the specified binding point.
 */
struct BindUniformBufferCommand {
    PipelineHandle pipeline;
    UniformHandle uniformBuffer;
    uint32_t bindingPoint;
};

/**
 * @brief Command to draw indexed geometry.
 * 
 * Renders geometry using the currently bound pipeline and buffers.
 */
struct DrawIndexedCommand {
    uint32_t indexCount;
    uint32_t instanceCount = 1;
    uint32_t firstIndex;
};

/**
 * @brief Variant type containing all possible renderer API commands.
 * 
 * Uses std::variant to provide type-safe command storage with proper
 * field names for each command type.
 */
using RendererApiCommand = std::variant<
    BindPipelineCommand,
    BindVertexBufferCommand,
    BindIndexBufferCommand,
    BindUniformBufferCommand,
    DrawIndexedCommand
>;  

/**
 * @typedef PipelineHandle
 * @brief A handle representing a rendering pipeline.
 */
struct RenderCommand {
    PipelineHandle pipeline;
    Mesh* mesh;
    Material* material;
    glm::mat4 transform;
    UniformHandle modelUniform;
};