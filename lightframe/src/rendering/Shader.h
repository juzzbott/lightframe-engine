#pragma once

#include <glm/glm.hpp>

#include <string>
#include <memory>

class Shader {
public:
    /**
     * @brief Creates a new Shader instance.
     * @return std::unique_ptr<Shader> A new Shader object.
     */
    static std::unique_ptr<Shader> create();
    
    /**
     * @brief Loads vertex and fragment shader source code.
     * @param vertSrc The vertex shader source code.
     * @param fragSrc The fragment shader source code.
     * @return bool True if shaders loaded successfully, false otherwise.
     */
    virtual bool loadShader(std::string& vertSrc, std::string& fragSrc) = 0;

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
};