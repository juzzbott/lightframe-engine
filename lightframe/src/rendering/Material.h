#pragma once

#include "RendererApi.h"

#include <unordered_map>

class Material {
public:
    Material() = default;
    
    /**
     * @brief Adds a shader for a specific render pass.
     * @param renderPass The render pass for which to add the shader.
     * @param shaderHandle The handle of the shader to add.
     */
    void addShader(RenderPass renderPass, ShaderHandle shaderHandle);
    
    /**
     * @brief Retrieves the shader handle for a specific render pass.
     * @param renderPass The render pass for which to get the shader.
     * @return ShaderHandle The handle of the shader associated with the render pass.
     */
    ShaderHandle getShader(RenderPass renderPass);
    
    /**
     * @brief Sets the diffuse map for the material.
     * @param diffuseMapHandle The handle of the diffuse texture to set.
     */
    void setDiffuseMap(TextureHandle diffuseMapHandle) { _diffuseMap = diffuseMapHandle; }
    
    /**
     * @brief Retrieves the diffuse map handle for the material.
     * @return TextureHandle The handle of the diffuse texture associated with the material.
     */
    const TextureHandle getDiffuseMap() const { return _diffuseMap; }
    
private:
    std::unordered_map<RenderPass, ShaderHandle> _shaders;
    
    TextureHandle _diffuseMap;   
    
};