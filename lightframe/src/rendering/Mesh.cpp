#include "Mesh.h"
#include <cmath>

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

/**
 * @brief Generates sphere mesh data with configurable resolution.
 * @param latitudeSegments Number of segments along latitude (vertical divisions).
 * @param longitudeSegments Number of segments along longitude (horizontal divisions).
 * @param outVertices Output vector for vertex data (pos, color, texCoords).
 * @param outIndices Output vector for indices.
 */
static void generateSphereMeshData(int latitudeSegments, int longitudeSegments, std::vector<float>& outVertices, std::vector<unsigned int>& outIndices) {
    constexpr float PI = 3.14159265359f;

    // Default color (can be changed per-vertex if desired)
    const float r = 0.7f, g = 0.7f, b = 0.9f;
    for (int y = 0; y <= latitudeSegments; ++y) {
        float v = float(y) / latitudeSegments;
        float theta = v * PI; // [0, PI]
        for (int x = 0; x <= longitudeSegments; ++x) {
            float u = float(x) / longitudeSegments;
            float phi = u * 2.0f * PI; // [0, 2PI]
            // Spherical to Cartesian
            float px = std::sin(theta) * std::cos(phi);
            float py = std::cos(theta);
            float pz = std::sin(theta) * std::sin(phi);
            // Position
            outVertices.push_back(px * 0.5f); // scale to radius 0.5
            outVertices.push_back(py * 0.5f);
            outVertices.push_back(pz * 0.5f);
            // Color (can be set to something else if desired)
            outVertices.push_back(r);
            outVertices.push_back(g);
            outVertices.push_back(b);
            // TexCoords
            outVertices.push_back(u);
            outVertices.push_back(v);
        }
    }
    // Indices
    for (int y = 0; y < latitudeSegments; ++y) {
        for (int x = 0; x < longitudeSegments; ++x) {
            int i0 = y * (longitudeSegments + 1) + x;
            int i1 = i0 + longitudeSegments + 1;
            int i2 = i0 + 1;
            int i3 = i1 + 1;
            // Two triangles per quad
            outIndices.push_back(i0);
            outIndices.push_back(i1);
            outIndices.push_back(i2);
            outIndices.push_back(i2);
            outIndices.push_back(i1);
            outIndices.push_back(i3);
        }
    }
}

Mesh Mesh::createSphereMesh(int latitudeSegments, int longitudeSegments) {

    std::vector<float> sphereVertices;
    std::vector<unsigned int> sphereIndices;

    generateSphereMeshData(latitudeSegments, longitudeSegments, sphereVertices, sphereIndices);

    BufferLayout layout = BufferLayout({
        BufferElement("pos", ShaderDataType::Float3, false),
        BufferElement("color", ShaderDataType::Float3, false),
        BufferElement("texCoords", ShaderDataType::Float2, false)
    });

    std::unique_ptr<VertexBuffer> vertexBuf = VertexBuffer::create(sphereVertices.data(), sphereVertices.size() * sizeof(float));
    vertexBuf->setLayout(layout);

    std::unique_ptr<IndexBuffer> indexBuf = IndexBuffer::create(sphereIndices.data(), sphereIndices.size() * sizeof(unsigned int));

    std::unique_ptr<VertexArray> vertexArray = VertexArray::create();
    vertexArray->addVertexBuffer(vertexBuf.get());
    vertexArray->setIndexBuffer(indexBuf.get());

    return Mesh(std::move(vertexBuf), std::move(indexBuf), std::move(vertexArray));
}