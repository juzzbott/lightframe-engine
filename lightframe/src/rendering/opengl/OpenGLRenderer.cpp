#include "OpenGLRenderer.h"

#include "rendering/Material.h"
#include "rendering/Mesh.h"

#include <glad/glad.h>

void OpenGLRenderer::beginFrame() {
    _renderQueue.clear();
    
    // reset stats
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
        
        Shader& shader = _shaderManager.get(command.material->getShader(RenderPass::Geometry));
        
        shader.use();
        shader.setMat4("uTransform", command.transform);
        shader.setInt("uTexture1", 0);
        //shader->setInt("uTexture1", 1);
        
        Texture& texture = _textureManager.get(command.material->getDiffuseMap());
        texture.bind();
        
        command.mesh->getVertexBuffer()->bind();
        command.mesh->getIndexBuffer()->bind();
        glDrawElements(GL_TRIANGLES, command.mesh->getIndexBuffer()->getIndexCount(), GL_UNSIGNED_INT, 0);
        
        
    }
}