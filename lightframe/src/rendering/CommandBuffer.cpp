#include "CommandBuffer.h"
#include "RenderQueue.h"
#include "RendererApi.h"
#include "Mesh.h"
#include "Material.h"

/**
 * @brief Builds the command buffer from the given render queue.
 *
 * Iterates over all render commands in the queue and generates the appropriate
 * renderer API commands for each, including pipeline, vertex/index buffer, uniform buffer,
 * and draw commands. Ensures correct pipeline binding and resource setup for each draw call.
 *
 * @param queue Reference to the RenderQueue containing render commands for this frame.
 */
void CommandBuffer::build(RenderQueue& queue) {
    PipelineHandle currentPipeline = 0;
    for (const auto& cmd : queue.getCommands()) {
        if (cmd.pipeline != currentPipeline) {
            // Bind the current pipeline
            BindPipelineCommand bindPipelineCmd {
                .pipeline = cmd.pipeline
            };
            _commands.push_back(bindPipelineCmd);
            currentPipeline = cmd.pipeline;
        }
        BindVertexBufferCommand bindVboCmd {
            .vertexBuffer = cmd.mesh->getVertexBuffer()->getRendererId()
        };
        _commands.push_back(bindVboCmd);
        BindIndexBufferCommand bindIboCmd {
            .indexBuffer = cmd.mesh->getIndexBuffer()->getRendererId()
        };
        _commands.push_back(bindIboCmd);
        BindUniformBufferCommand bindUboCmd {
            .pipeline = cmd.pipeline,
            .uniformBuffer = cmd.modelUniform,
            .bindingPoint = 1 // 1 for now, this relates to binding = 1 uniform ObjectUBO
        };
        _commands.push_back(bindUboCmd);
        DrawIndexedCommand drawCmd {
            .indexCount = cmd.mesh->getIndexBuffer()->getIndexCount(),
            .instanceCount = 1,
            .firstIndex = 0
        };
        _commands.push_back(drawCmd);
    }
}

/**
 * @brief Clears all commands from the command buffer.
 *
 * Removes all previously recorded renderer API commands, preparing the buffer
 * for a new frame or set of render commands.
 */
void CommandBuffer::clear() {
    _commands.clear();
}