#pragma once

#include "rendering/Buffer.h"
#include "rendering/VertexArray.h"

#include <memory>

/**
 * @brief Represents a mesh with vertex data, indices, and vertex array configuration.
 */
class Mesh {
public:
    /**
     * @brief Constructs a mesh and takes ownership of the provided buffers and vertex array.
     * @param vertexBuffer The vertex buffer containing vertex data.
     * @param indexBuffer The index buffer containing index data.
     * @param vertexArray The vertex array object defining the vertex layout.
     */
    Mesh(std::unique_ptr<VertexBuffer> vertexBuffer, 
        std::unique_ptr<IndexBuffer> indexBuffer, 
        std::unique_ptr<VertexArray> vertexArray);
    
    /**
     * @brief Gets the vertex buffer for this mesh.
     * @return VertexBuffer* Raw pointer to the vertex buffer (mesh retains ownership).
     */
    VertexBuffer* getVertexBuffer() { return _vertexBuffer.get(); }
    
    /**
     * @brief Gets the index buffer for this mesh.
     * @return IndexBuffer* Raw pointer to the index buffer (mesh retains ownership).
     */
    IndexBuffer* getIndexBuffer() { return _indexBuffer.get(); }
    
    /**
     * @brief Gets the vertex array object for this mesh.
     * @return VertexArray* Raw pointer to the vertex array (mesh retains ownership).
     */
    VertexArray* getVertexArray() { return _vertexArray.get(); }
    
    /**
     * @brief Creates a cube mesh with predefined vertex and index data.
     */
    static Mesh createCubeMesh();
        
private:
    // Vertex buffer containing mesh vertex data
    std::unique_ptr<VertexBuffer> _vertexBuffer;
    // Index buffer containing mesh index data
    std::unique_ptr<IndexBuffer> _indexBuffer;
    // Vertex array object defining vertex attribute layout
    std::unique_ptr<VertexArray> _vertexArray;
};