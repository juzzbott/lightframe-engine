#pragma once

#include "rendering/RendererApi.h"
#include "rendering/Shader.h"

#include <memory>
#include <unordered_map>

class ShaderManager {
public:
    
    /**
     * @brief Loads a shader from file and assigns it a handle.
     * @param filePath The file path to the shader source.
     * @param shaderName The name to associate with the shader.
     * @return ShaderHandle The handle assigned to the loaded shader.
     */
    ShaderHandle loadShader(const std::string& filePath, const std::string& shaderName);
    
    /**
     * @brief Retrieves a shader by its handle.
     * @param handle The handle of the shader to retrieve.
     * @return Shader& Reference to the requested Shader object.
     */
    Shader& get(ShaderHandle handle);
    
private:
    // Maps shader names to their handles and stores shader instances by handle
    std::unordered_map<std::string, ShaderHandle> _shaderNameMap = {};
    
    // Map of shader handles to Shader instances
    std::unordered_map<ShaderHandle, std::unique_ptr<Shader>> _shaders = {};
    
    // Last assigned shader handle
    ShaderHandle _lastHandle = 0;

};