#include "Mesh.h"

#include <memory>

Mesh::Mesh(std::unique_ptr<VertexBuffer> vertexBuffer, std::unique_ptr<IndexBuffer> indexBuffer, 
    std::unique_ptr<VertexArray> vertexArray)
    : _vertexBuffer(std::move(vertexBuffer)), _indexBuffer(std::move(indexBuffer)), _vertexArray(std::move(vertexArray)) { }
    
Mesh Mesh::createCubeMesh() {
    
    std::vector<float> cubeVertices = {
        // +X face
        0.5f,-0.5f,-0.5f, 0.92f, 0.23f, 0.18f, 0.0f, 0.0f,
        0.5f, 0.5f,-0.5f, 0.85f, 0.31f, 0.22f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.88f, 0.40f, 0.30f, 1.0f, 1.0f,
        0.5f,-0.5f, 0.5f, 0.95f, 0.28f, 0.20f, 1.0f, 0.0f,

        // -X face
        -0.5f,-0.5f, 0.5f, 0.18f, 0.60f, 0.85f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.22f, 0.65f, 0.90f, 0.0f, 1.0f,
        -0.5f, 0.5f,-0.5f, 0.30f, 0.70f, 0.95f, 1.0f, 1.0f,
        -0.5f,-0.5f,-0.5f, 0.15f, 0.55f, 0.80f, 1.0f, 0.0f,

        // +Y face
        -0.5f, 0.5f,-0.5f, 0.30f, 0.85f, 0.35f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.40f, 0.90f, 0.45f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.50f, 0.95f, 0.55f, 1.0f, 1.0f,
        0.5f, 0.5f,-0.5f, 0.35f, 0.88f, 0.40f, 1.0f, 0.0f,

        // -Y face
        -0.5f,-0.5f, 0.5f, 0.75f, 0.75f, 0.20f, 0.0f, 0.0f,
        -0.5f,-0.5f,-0.5f, 0.80f, 0.80f, 0.25f, 0.0f, 1.0f,
        0.5f,-0.5f,-0.5f, 0.85f, 0.85f, 0.30f, 1.0f, 1.0f,
        0.5f,-0.5f, 0.5f, 0.78f, 0.78f, 0.22f, 1.0f, 0.0f,

        // +Z face
        -0.5f,-0.5f, 0.5f, 0.70f, 0.35f, 0.85f, 0.0f, 0.0f,
         0.5f,-0.5f, 0.5f, 0.75f, 0.40f, 0.90f, 1.0f, 0.0f,
         0.5f, 0.5f, 0.5f, 0.80f, 0.45f, 0.95f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.72f, 0.38f, 0.88f, 0.0f, 1.0f,

        // -Z face
         0.5f,-0.5f,-0.5f, 0.35f, 0.35f, 0.35f, 0.0f, 0.0f,
        -0.5f,-0.5f,-0.5f, 0.45f, 0.45f, 0.45f, 1.0f, 0.0f,
        -0.5f, 0.5f,-0.5f, 0.55f, 0.55f, 0.55f, 1.0f, 1.0f,
         0.5f, 0.5f,-0.5f, 0.65f, 0.65f, 0.65f, 0.0f, 1.0f,
    };
    
    std::vector<unsigned int> cubeIndices = {
        0, 1, 2,  2, 3, 0,        // +X
        4, 5, 6,  6, 7, 4,        // -X
        8, 9,10, 10,11, 8,        // +Y
        12,13,14, 14,15,12,       // -Y
        16,17,18, 18,19,16,       // +Z
        20,21,22, 22,23,20        // -Z
    };
    
    // Create and bind vertex buffer & index buffer
    BufferLayout layout = BufferLayout({ 
        BufferElement("pos", ShaderDataType::Float3, false), 
        BufferElement("color", ShaderDataType::Float3, false),
        BufferElement("texCoords", ShaderDataType::Float2, false)
    });
    std::unique_ptr<VertexBuffer> vertexBuf = VertexBuffer::create(cubeVertices.data(), cubeVertices.size() * sizeof(float));
    vertexBuf->setLayout(layout);
    
    std::unique_ptr<IndexBuffer> indexBuf = IndexBuffer::create(cubeIndices.data(), cubeIndices.size() * sizeof(unsigned int)); 
    
    std::unique_ptr<VertexArray> vertexArray = VertexArray::create();
    vertexArray->addVertexBuffer(vertexBuf.get());
    vertexArray->setIndexBuffer(indexBuf.get());
    
    return Mesh(std::move(vertexBuf), std::move(indexBuf), std::move(vertexArray));
    
}