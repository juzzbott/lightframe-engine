#pragma once

#include <glm/glm.hpp>

#include <string>
#include <memory>
#include <unordered_map>

enum class ShaderType {
    Unknown = 0,
    Vertex,
    Fragment
};

class Shader {
public:

    /**
     * @brief Creates a new Shader instance.
     * @param shaderPath The file path to the shader source code.
     * @return std::unique_ptr<Shader> A new Shader object.
     */
    static std::unique_ptr<Shader> create(const std::string& shaderPath);

    /**
     * @brief Activates this shader for rendering.
     */
    virtual void use() const = 0;

    /**
     * @brief Destroys and releases shader resources.
     */
    virtual void destroy() = 0;

    /**
     * @brief Gets the OpenGL shader program ID.
     * @return unsigned int The shader program ID.
     */
    virtual unsigned int getShaderId() const = 0;
    
    /**
     * @brief Sets an integer uniform variable.
     * @param name The name of the uniform variable.
     * @param value The integer value to set.
     */
    virtual void setInt(std::string name, int value) = 0;
    
    /**
     * @brief Sets a 2-component float uniform variable.
     * @param name The name of the uniform variable.
     * @param v1 The first float value.
     * @param v2 The second float value.
     */
    virtual void setFloat2(std::string name, float v1, float v2) = 0;

    /**
     * @brief Sets a 4-component float uniform variable.
     * @param name The name of the uniform variable.
     * @param v1 The first float value.
     * @param v2 The second float value.
     * @param v3 The third float value.
     * @param v4 The fourth float value.
     */
    virtual void setFloat4(std::string name, float v1, float v2, float v3, float v4) = 0;
    
    /**
     * @brief Sets a 4x4 matrix uniform variable.
     * @param name The name of the uniform variable.
     * @param matrix The 4x4 matrix value.
     */
    virtual void setMat4(std::string name, glm::mat4 matrix) = 0;
    
    /**
     * @brief Loads shader source code from a file, separating different shader stages.
     * @param shaderPath The file path to the shader source code.
     * @return std::unordered_map<ShaderType, std::string> A map of shader stage types to their source code.
     */
    static std::unordered_map<ShaderType, std::string> loadShaderSources(const std::string& shaderPath);
    
    /**
     * @brief Converts a shader type name to its corresponding ShaderType enum value.
     * @param name The name of the shader type (e.g., "vertex", "fragment").
     * @return ShaderType The corresponding ShaderType enum value.
     */
    static ShaderType shaderTypeFromName(std::string& name);
};