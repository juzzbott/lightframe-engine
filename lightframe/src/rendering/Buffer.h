#pragma once

#include "debug/Assertions.h"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

/**
 * @brief Enumeration of shader data types for vertex buffer layouts.
 */
enum class ShaderDataType {
    Float = 1,
    Float2,
    Float3,
    Float4, 
    Mat3,
    Mat4,
    Int,
    Int2,
    Int3,
    Int4,
    Bool
};

static uint32_t shaderDataTypeSize(ShaderDataType type) {
    switch (type) {
        case ShaderDataType::Float:    return 4;
        case ShaderDataType::Float2:   return 4 * 2;
        case ShaderDataType::Float3:   return 4 * 3;
        case ShaderDataType::Float4:   return 4 * 4;
        case ShaderDataType::Mat3:     return 4 * 3 * 3;
        case ShaderDataType::Mat4:     return 4 * 4 * 4;
        case ShaderDataType::Int:      return 4;
        case ShaderDataType::Int2:     return 4 * 2;
        case ShaderDataType::Int3:     return 4 * 3;
        case ShaderDataType::Int4:     return 4 * 4;
        case ShaderDataType::Bool:     return 1;
    }
    
    return 0;
}

/**
 * @brief Represents a single element in a vertex buffer layout.
 */
struct BufferElement {
    /** Name of the vertex attribute */
    std::string name;
    /** Data type of the vertex attribute */
    ShaderDataType dataType;
    /** Size in bytes of the attribute */
    uint32_t size;
    /** Byte offset within the vertex structure */
    size_t offset;
    /** Whether the attribute should be normalized */
    bool normalised;
    
    BufferElement() = default;
    BufferElement(const std::string& name, ShaderDataType dataType, bool normalised)
        : name(name), dataType(dataType), size(shaderDataTypeSize(dataType)), offset(0), normalised(normalised) {
    }
    
    uint32_t getElementCount() const {
        switch (dataType) {
            case ShaderDataType::Float:    return 1;
            case ShaderDataType::Float2:   return 2;
            case ShaderDataType::Float3:   return 3;
            case ShaderDataType::Float4:   return 4;
            case ShaderDataType::Mat3:     return 3;
            case ShaderDataType::Mat4:     return 4;
            case ShaderDataType::Int:      return 1;
            case ShaderDataType::Int2:     return 2;
            case ShaderDataType::Int3:     return 3;
            case ShaderDataType::Int4:     return 4;
            case ShaderDataType::Bool:     return 1;
        }
    
        return 0;
    }
};

/**
 * @brief Defines the layout of vertex buffer data with elements and stride.
 */
class BufferLayout {
public:

    /**
     * @brief Default constructor for an empty buffer layout.
     */
    BufferLayout() {}

    /**
     * @brief Constructs a buffer layout with the specified elements.
     * @param elements Initializer list of BufferElement objects defining the layout.
     */
    BufferLayout(std::initializer_list<BufferElement> elements);
    
    /**
     * @brief Returns the total stride of the buffer layout.
     */
    uint32_t getStride() const { return _stride; }
    
    /**
     * @brief Returns the elements of the buffer layout.
     */
    const std::vector<BufferElement>& getElements() const { return _elements; }

    /**
     * @brief Returns the number of values per vertex based on the buffer elements and their data types.
     * This is calculated by summing the element counts of each buffer element, which corresponds to the number of individual values (e.g., floats) that make up a single vertex.
     * @return The total number of values per vertex.
     */
    const unsigned int getVertexLength() const { return _vertexLength; }

    /**
     * @brief Returns an iterator to the beginning of the buffer elements.
     * @return Iterator to the first element.
     */
    std::vector<BufferElement>::iterator begin() { return _elements.begin(); }

    /**
     * @brief Returns an iterator to the end of the buffer elements.
     * @return Iterator past the last element.
     */
    std::vector<BufferElement>::iterator end() { return _elements.end(); }

    /**
     * @brief Returns a const iterator to the beginning of the buffer elements.
     * @return Const iterator to the first element.
     */
    std::vector<BufferElement>::const_iterator begin() const { return _elements.begin(); }

    /**
     * @brief Returns a const iterator to the end of the buffer elements.
     * @return Const iterator past the last element.
     */
    std::vector<BufferElement>::const_iterator end() const { return _elements.end(); }

private:
    // Collection of buffer elements defining the vertex layout
    std::vector<BufferElement> _elements;
    // Total byte stride between consecutive vertices
    uint32_t _stride;

    // The number of values per vertex, calculated from the buffer element and shader type sizes.
    uint32_t _vertexLength;
    
    /**
     * @brief Calculates the offset and stride for the buffer layout.
     */
    void calcOffsetStride();
    
};

class VertexBuffer {
public:

    /**
     * @brief Creates a new VertexBuffer instance.
     * @return std::unique_ptr<VertexBuffer> A new VertexBuffer object.
     */
    static std::unique_ptr<VertexBuffer> create();

    /**
     * @brief Creates a new VertexBuffer instance with vertex data.
     * @param vertices Pointer to the vertex data.
     * @param size Size of the vertex data in bytes.
     * @return std::unique_ptr<VertexBuffer> A new VertexBuffer object with the provided data.
     */
    static std::unique_ptr<VertexBuffer> create(float* vertices, uint32_t size);
    
    /**
     * @brief Gets the layout of this vertex buffer.
     * @return const BufferLayout& The buffer layout.
     */
    virtual const BufferLayout& getLayout() const = 0;
    
    /**
     * @brief Sets the layout of this vertex buffer.
     * @param layout The buffer layout to set.
     */
    virtual void setLayout(const BufferLayout& layout) = 0;

    /**
     * @brief Binds this vertex buffer for use in rendering.
     */
    virtual void bind() const = 0;

    /**
     * @brief Unbinds this vertex buffer.
     */
    virtual void unbind() const = 0;

    /**
     * @brief Gets the OpenGL renderer ID for this vertex buffer.
     * @return unsigned int The renderer ID.
     */
    virtual unsigned int getRendererId() const = 0;

    /**
     * @brief Gets the number of vertices in this vertex buffer.
     * @return unsigned int The vertex count.
     */
    virtual unsigned int getVertexCount() const = 0;
    
};

class IndexBuffer {
public:
    /**
     * @brief Creates a new IndexBuffer instance with index data.
     * @param indices Pointer to the index data.
     * @param count Number of indices.
     * @return std::unique_ptr<IndexBuffer> A new IndexBuffer object with the provided data.
     */
    static std::unique_ptr<IndexBuffer> create(unsigned int* indices, uint32_t count);

    /**
     * @brief Binds this index buffer for use in rendering.
     */
    virtual void bind() const = 0;

    /**
     * @brief Unbinds this index buffer.
     */
    virtual void unbind() const = 0;

    /**
     * @brief Gets the OpenGL renderer ID for this index buffer.
     * @return unsigned int The renderer ID.
     */
    virtual unsigned int getRendererId() const = 0;
    
    /**
     * @brief Gets the number of indices in this index buffer.
     * @return unsigned int The index count.
     */
    virtual unsigned int getIndexCount() const = 0;
};