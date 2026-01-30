#include "Shader.h"
#include "opengl/OpenGLShader.h"

#include <memory>

std::unique_ptr<Shader> Shader::create() {
    // TODO: Platform detection/selection
    return std::make_unique<OpenGLShader>();
}