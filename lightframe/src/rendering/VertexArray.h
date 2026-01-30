#pragma once

#include "Buffer.h"

#include <memory>

class VertexArray {
public: 

    static std::unique_ptr<VertexArray> create();
    
    virtual void addVertexBuffer(VertexBuffer* vertexBuffer) = 0;
    virtual void setIndexBuffer(IndexBuffer* indexBuffer) = 0;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;
    virtual unsigned int getRendererId() const = 0;
};