#include "Buffer.h"

#include "opengl/OpenGLBuffer.h"

/**
 * Buffer Layout
 */

BufferLayout::BufferLayout(std::initializer_list<BufferElement> elements)
    : _elements(elements) {
    calcOffsetStride();
}

void BufferLayout::calcOffsetStride() {
    size_t offset = 0;
    _stride = 0;
    _vertexLength = 0;
    for (auto& element : _elements) {
        element.offset = offset;
        offset += element.size;
        _stride += element.size;
        _vertexLength += element.getElementCount();
    }
}

/**
 * Vertex Buffer
 */

std::unique_ptr<VertexBuffer> VertexBuffer::create() {
    return std::make_unique<OpenGLVertexBuffer>();
}

std::unique_ptr<VertexBuffer> VertexBuffer::create(float* vertices, uint32_t size) {
    return std::make_unique<OpenGLVertexBuffer>(vertices, size);
}

/**
 * Index Buffer
 */

std::unique_ptr<IndexBuffer> IndexBuffer::create(unsigned int* indices, uint32_t count) {
    return std::make_unique<OpenGLIndexBuffer>(indices, count);
}