#include "OpenGLVertexArray.h"

#include "debug/Assertions.h"
#include "rendering/Buffer.h"

#include <glad/glad.h>

static GLenum shaderDataTypeToGlType(ShaderDataType dataType) {
    switch (dataType) {
        case ShaderDataType::Float:
        case ShaderDataType::Float2:
        case ShaderDataType::Float3:
        case ShaderDataType::Float4:
        case ShaderDataType::Mat3:
        case ShaderDataType::Mat4:
            return GL_FLOAT;
        case ShaderDataType::Int:
        case ShaderDataType::Int2:
        case ShaderDataType::Int3:
        case ShaderDataType::Int4:
            return GL_INT;
        case ShaderDataType::Bool:
            return GL_BOOL;
    }
    
    return 0;
}

OpenGLVertexArray::OpenGLVertexArray() {
    glGenVertexArrays(1, &_rendererId);
    glBindVertexArray(_rendererId);
}

OpenGLVertexArray::~OpenGLVertexArray() {
    if (_rendererId >= 0) {
        glDeleteVertexArrays(1, &_rendererId);
        _rendererId = 0;
    }
}

void OpenGLVertexArray::addVertexBuffer(VertexBuffer* vertexBuffer) {
    
    if (!vertexBuffer) {
        return;
    }
    
    // Bind the vao and vbo
    bind();
    vertexBuffer->bind();
    
    // How this works - glVertexAttribPointer
    // First param - 0 - location with shader, i.e. location = 0.
    // Next is number of values for that data type at that location. We set location = 0 as a vec3, so 3 values
    // Next is data type of the values
    // Next determines if data is normalized - Initally false as we don't want to normalize the data
    // Next is stride, how many bytes in total for this location. we have 3 float of 4 bytes each, so 12 in this case
    // Last is the offset, as we only have 3 values in this layout, the offset will always null 0 or null in this case
    // In the future, this will be how many bytes for the specific location
    
    // Iterate through the elements in the vertex layout and set the buffer layout for the vao
    const auto& bufferLayout = vertexBuffer->getLayout();
    for (auto& element : bufferLayout) {
        
        switch (element.dataType) {
            case ShaderDataType::Float:
            case ShaderDataType::Float2:
            case ShaderDataType::Float3:
            case ShaderDataType::Float4:
            {
                glEnableVertexAttribArray(_vertexBufferIndex);
                glVertexAttribPointer(
                    _vertexBufferIndex,
                    element.getElementCount(),
                    shaderDataTypeToGlType(element.dataType), 
                    element.normalised ? GL_TRUE : GL_FALSE,
                    bufferLayout.getStride(),
                    (const void*)element.offset
                );
                _vertexBufferIndex++;
                break;
            }
        }
    }
    
    _vertexBuffers.push_back(vertexBuffer);
}

void OpenGLVertexArray::setIndexBuffer(IndexBuffer* indexBuffer) {
    _indexBuffer = indexBuffer;
}

void OpenGLVertexArray::bind() const {
    glBindVertexArray(_rendererId);
    if (_indexBuffer) {   
        _indexBuffer->bind();
    }
}

void OpenGLVertexArray::unbind() const {
    glBindVertexArray(0);
}