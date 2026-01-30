#include "VertexArray.h"

#include "rendering/opengl/OpenGLVertexArray.h"

#include <memory>

std::unique_ptr<VertexArray> VertexArray::create() {
    return std::make_unique<OpenGLVertexArray>();
}