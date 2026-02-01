/**
 * @file OpenGLShader.h
 * @author Justin McKay
 * @brief Defines the OpenGL implementation for the Shader class.
 * @date 2026-1-22
 */


#pragma once

#include <rendering/Shader.h>
#include <glad/glad.h>
#include <map>

class OpenGLShader final : public Shader {
public:
    
    /**
     * @brief Creates a new Shader instance.
     * @param shaderPath The file path to the shader source code.
     * @return std::unique_ptr<Shader> A new Shader object.
     */
    OpenGLShader(const std::string& shaderPath);

    /**
     * @brief Binds the shader program for subsequent draw calls.
     */
    void use() const override;

    /**
     * @brief Releases GPU resources associated with this shader program.
     */
    void destroy() override;
    
    /**
     * @brief Gets the OpenGL program object ID.
     * @return The OpenGL shader program ID.
     */
    unsigned int getShaderId() const override { return _shaderId; }
    
    /**
     * @brief Sets an integer uniform variable.
     * @param name The name of the uniform variable.
     * @param value The integer value to set.
     */
    void setInt(std::string name, int value) override;
    
    /**
     * @brief Sets a vec2 uniform variable.
     * @param name The name of the uniform variable.
     * @param v1 The first component value.
     * @param v2 The second component value.
     */
    void setFloat2(std::string name, float v1, float v2) override;

    /**
     * @brief Sets a vec4 uniform variable.
     * @param name The name of the uniform variable.
     * @param v1 The first component value.
     * @param v2 The second component value.
     * @param v3 The third component value.
     * @param v4 The fourth component value.
     */
    void setFloat4(std::string name, float v1, float v2, float v3, float v4) override;
    
    /**
     * @brief Sets a 4x4 matrix uniform variable.
     * @param name The name of the uniform variable.
     * @param matrix The 4x4 matrix value.
     */
    void setMat4(std::string name, glm::mat4 matrix) override;
    
private:
    GLuint _shaderId;
    std::map<std::string, GLint> _uniformLocCache;
    
    /**
     * @brief Compiles an individual shader stage from source.
     * @param src The shader source code.
     * @param type The OpenGL shader stage type.
     * @return The compiled shader object ID.
     */
    GLuint compileShader(std::string& src, GLenum type);

    /**
     * @brief Gets and caches the uniform location for the given name.
     * @param name The uniform variable name.
     * @return The uniform location, or -1 if not found.
     */
    GLint getUniformLoc(std::string& name);
};