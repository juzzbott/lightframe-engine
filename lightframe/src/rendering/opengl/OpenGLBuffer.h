/**
 * @file OpenGLBuffer.h
 * @author Justin McKay
 * @brief Defines the OpenGL implementation for the VertexBuffer and IndexBuffer types.
 * @date 2026-1-22
 */

#pragma once

#include "rendering/Buffer.h"

#include <glad/glad.h>

#include <cstdint>

class OpenGLVertexBuffer final : public VertexBuffer {
public:

    /**
     * @brief Constructs an empty OpenGL vertex buffer object.
     */
    OpenGLVertexBuffer();

    /**
     * @brief Constructs an OpenGL vertex buffer with initial data.
     * @param vertices Pointer to vertex data.
     * @param size Size of the vertex data in bytes.
     */
    OpenGLVertexBuffer(const float* vertices, uint32_t size);
    
    /**
     * @brief Deconstructs the OpenGL vertex buffer, releasing any allocated resources.
     */
    ~OpenGLVertexBuffer();
    
    /**
     * @brief Gets the layout of this vertex buffer.
     * @return const BufferLayout& The buffer layout.
     */
    const BufferLayout& getLayout() const override { return _layout; };
    
    /**
     * @brief Sets the layout of this vertex buffer.
     * @param layout The buffer layout to set.
     */
    void setLayout(const BufferLayout& layout) override { _layout = layout; };

    /**
     * @brief Binds this vertex buffer to the OpenGL context.
     */
    void bind() const override;

    /**
     * @brief Unbinds this vertex buffer from the OpenGL context.
     */
    void unbind() const override;

    /**
     * @brief Retrieves the OpenGL renderer identifier for this vertex buffer.
     * @return unsigned int Renderer ID issued by OpenGL.
     */
    unsigned int getRendererId() const override { return _rendererId; };

    /**
     * @brief Gets the number of vertices in this vertex buffer.
     * @return unsigned int The vertex count.
     */
    unsigned int getVertexCount() const override { return _vertexElementCount / _layout.getVertexLength(); }
    
private:
    // OpenGL-generated buffer identifier.
    GLuint _rendererId;
    BufferLayout _layout;
    uint32_t _vertexElementCount;
};

class OpenGLIndexBuffer final : public IndexBuffer {
public:

    /**
     * @brief Constructs an OpenGL index buffer with index data.
     * @param indices Pointer to index data.
     * @param size Number of indices contained in the buffer.
     */
    OpenGLIndexBuffer(unsigned int* indices, uint32_t size);
    
    /**
     * @brief Deconstructs the OpenGL index buffer, releasing any allocated resources.
     */
    ~OpenGLIndexBuffer();

    /**
     * @brief Binds this index buffer to the OpenGL context.
     */
    void bind() const override;

    /**
     * @brief Unbinds this index buffer from the OpenGL context.
     */
    void unbind() const override;

    /**
     * @brief Retrieves the OpenGL renderer identifier for this index buffer.
     * @return unsigned int Renderer ID issued by OpenGL.
     */
    unsigned int getRendererId() const override { return _rendererId; };
    
    /**
     * @brief Gets the number of indices in this index buffer.
     * @return unsigned int The index count.
     */
    unsigned int getIndexCount() const override { return _size; }
    
private:
    // OpenGL-generated buffer identifier.
    GLuint _rendererId;
    uint32_t _size;
};