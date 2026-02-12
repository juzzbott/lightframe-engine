#include "OpenGLRenderer.h"

#include "core/Logger.h"

#include "rendering/Renderer.h"
#include "rendering/Material.h"
#include "rendering/Mesh.h"

#include <glad/glad.h>

OpenGLRenderer::OpenGLRenderer(ResourceManager& resourceManager)
        : _resourceManager(resourceManager) {}

void OpenGLRenderer::beginFrame() {
    _renderQueue.clear();
    
    // reset stats
    _renderStats = RenderStats();
}

void OpenGLRenderer::submit(const RenderCommand& command) {
    _renderQueue.submit(command);
}

void OpenGLRenderer::endFrame() {
    
    // Execute the render passes
    executeGeometryPass();
    
}

/**
 * RENDER PASSES
 */

void OpenGLRenderer::executeGeometryPass() {
    
    // Iterate through the render commands and draw
    for (auto command : _renderQueue.getCommands()) {
        
        auto& shader = _resourceManager.get<Shader>(command.material->getShader(RenderPass::Geometry));
        
        shader.use();
        shader.setMat4("uTransform", command.transform);
        shader.setInt("uTexture1", 0);
        //shader->setInt("uTexture1", 1);
        
        auto& texture = _resourceManager.get<Texture2D>(command.material->getDiffuseMap());
        texture.bind();

        // Bind the VAO
        command.mesh->getVertexArray()->bind();

        glDrawElements(GL_TRIANGLES, command.mesh->getIndexBuffer()->getIndexCount(), GL_UNSIGNED_INT, 0);

        // Update stats
        _renderStats.drawCalls++;
        _renderStats.verticesRendered += command.mesh->getVertexBuffer()->getVertexCount();
        _renderStats.objectsRendered++;
    }

    // Log render stats
    LOG_INFO("Render stats: draw calls = {}, vertices rendered = {}, objects rendered = {}",
        _renderStats.drawCalls, _renderStats.verticesRendered, _renderStats.objectsRendered);
}