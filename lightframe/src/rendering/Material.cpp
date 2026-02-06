#include "Material.h"

#include <unordered_map>

void Material::addShader(RenderPass renderPass, ShaderHandle shaderHandle) {
    if (shaderHandle > 0) {
        _shaders.try_emplace(renderPass, shaderHandle);
    }
}

ShaderHandle Material::getShader(RenderPass renderPass) {
    // Check if map contains key. If not, return 0
    if (_shaders.contains(renderPass)) {
        return _shaders[renderPass];
    }
    return 0;
}