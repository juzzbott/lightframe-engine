#pragma once

#include "rendering/Buffer.h"
#include "rendering/VertexArray.h"

#include <glad/glad.h>

#include <memory>
#include <vector>

class OpenGLVertexArray final : public VertexArray {
public: 

    /**
     * @brief Constructs a new OpenGL vertex array object.
     */
    OpenGLVertexArray();
    
    /**
     * @brief Deconstructor a OpenGL vertex array object, releasing any bound vertex arrays.
     */
    ~OpenGLVertexArray();

    /**
     * @brief Adds a vertex buffer to this vertex array object.
     * @param vertexBuffer Reference to the vertex buffer to attach.
     */
    void addVertexBuffer(VertexBuffer* vertexBuffer) override;

    /**
     * @brief Sets the index buffer used by this vertex array object.
     * @param indexBuffer Reference to the index buffer to bind.
     */
    void setIndexBuffer(IndexBuffer* indexBuffer) override;

    /**
     * @brief Binds this vertex array object in OpenGL.
     */
    void bind() const;

    /**
     * @brief Unbinds the currently bound vertex array object.
     */
    void unbind() const;

    /**
     * @brief Retrieves the OpenGL renderer identifier for this VAO.
     * @return unsigned int The renderer ID assigned by OpenGL.
     */
    unsigned int getRendererId() const { return _rendererId; };
    
private:
    // OpenGL-assigned vertex array object identifier.
    GLuint _rendererId;
    // Collection of vertex buffers attached to this VAO.
    std::vector<VertexBuffer*> _vertexBuffers;
    // Index buffer associated with this VAO.
    IndexBuffer* _indexBuffer;
    // Current vertex buffer index for attribute setup.
    unsigned int _vertexBufferIndex = 0;
};