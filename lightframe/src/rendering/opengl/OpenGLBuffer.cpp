#include "OpenGLBuffer.h"

#include <glad/glad.h>

#include <cstdint>

/***
 * VERTEX BUFFERS
 ***/

OpenGLVertexBuffer::OpenGLVertexBuffer() : _vertexElementCount(0) {
    glGenBuffers(1, &_rendererId);
    glBindBuffer(GL_ARRAY_BUFFER, _rendererId);
}

OpenGLVertexBuffer::OpenGLVertexBuffer(const float* vertices, uint32_t size) {
    glGenBuffers(1, &_rendererId);
    glBindBuffer(GL_ARRAY_BUFFER, _rendererId);
    // Upload vertex data to GPU
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    _vertexElementCount = size / sizeof(float);
    
}

OpenGLVertexBuffer::~OpenGLVertexBuffer() {
    if (_rendererId > 0) {
        glDeleteBuffers(1, &_rendererId);
        _rendererId = 0;
    }
}

void OpenGLVertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, _rendererId);
}

void OpenGLVertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/***
 * INDEX BUFFERS
 ***/

OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int* indices, uint32_t size)
    : _size(size) {
    glGenBuffers(1, &_rendererId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererId);
    // Upload vertex data to GPU
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}
 
OpenGLIndexBuffer::~OpenGLIndexBuffer() {
    if (_rendererId > 0) {
        glDeleteBuffers(1, &_rendererId);
        _rendererId = 0;
    }
}

void OpenGLIndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererId);
}

void OpenGLIndexBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}