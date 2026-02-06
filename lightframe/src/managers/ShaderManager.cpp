#include "ShaderManager.h"

#include "debug/Assertions.h"
#include "rendering/RendererApi.h"
#include "rendering/Shader.h"

#include <memory>
#include <unordered_map>

ShaderHandle ShaderManager::loadShader(const std::string& shaderPath, const std::string& shaderName) {
    std::unique_ptr<Shader> shader = Shader::create(shaderPath);
    
    ShaderHandle newHandle = ++_lastHandle;
    
    _shaderNameMap.try_emplace(shaderName, newHandle);
    _shaders.try_emplace(newHandle, std::move(shader));
    return newHandle;
}

Shader& ShaderManager::get(ShaderHandle shaderHandle) {
    LF_ASSERT_MSG(_shaders.contains(shaderHandle), std::format("No shader handle {} found.", shaderHandle));
    
    return *_shaders[shaderHandle];
}