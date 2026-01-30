#include "OpenGLShader.h"

#include <core/Logger.h>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>

bool OpenGLShader::loadShader(std::string& vertSrc, std::string& fragSrc) {
    
    GLuint vertShaderId = compileShader(vertSrc, GL_VERTEX_SHADER);
    GLuint fragShaderId = compileShader(fragSrc, GL_FRAGMENT_SHADER);
    
    if (vertShaderId == 0 || fragShaderId == 0) {
        return false;
    }
    
    GLuint shaderId = glCreateProgram();
    glAttachShader(shaderId, vertShaderId);
    glAttachShader(shaderId, fragShaderId);
    
    GLint shaderSuccess;
    glLinkProgram(shaderId);
    glGetProgramiv(shaderId, GL_LINK_STATUS, &shaderSuccess);
    if (!shaderSuccess) {
        char infoLog[512];
        glGetProgramInfoLog(shaderId, 512, nullptr, infoLog);
        LOG_WARN("Error linking shading program: {}", infoLog);
        return false;
    }
    
    glDeleteShader(vertShaderId);
    glDeleteShader(fragShaderId);
    
    _shaderId = shaderId;
    return true;
    
}

void OpenGLShader::use() const { 
    if (_shaderId <= 0) {
        LOG_TRACE("Attempted to use shader with invalid program id.");
        return;
    }
    glUseProgram(_shaderId);
}

void OpenGLShader::destroy() {
    if (_shaderId <= 0) {
        LOG_TRACE("Attempted to delete shader with invalid program id.");
        return;
    }
    glDeleteProgram(_shaderId);
    _shaderId = 0;
}

void OpenGLShader::setInt(std::string name, int value) {
    GLint uniformLoc = getUniformLoc(name);
    
    if (uniformLoc == -1) {
        LOG_TRACE("Unable to find uniform with name {} in shader id {}.", name, _shaderId);
        return;
    }
    glUniform1i(uniformLoc, value);
}

void OpenGLShader::setFloat2(std::string name, float v1, float v2) {
    GLint uniformLoc = getUniformLoc(name);
    
    if (uniformLoc == -1) {
        LOG_TRACE("Unable to find uniform with name {} in shader id {}.", name, _shaderId);
        return;
    }
    glUniform2f(uniformLoc, v1, v2);
}

void OpenGLShader::setFloat4(std::string name, float v1, float v2, float v3, float v4) {
    GLint uniformLoc = getUniformLoc(name);
    
    if (uniformLoc == -1) {
        LOG_TRACE("Unable to find uniform with name {} in shader id {}.", name, _shaderId);
        return;
    }
    glUniform4f(uniformLoc, v1, v2, v3, v4);
}

void OpenGLShader::setMat4(std::string name, glm::mat4 matrix) {
    GLint uniformLoc = getUniformLoc(name);
    
    if (uniformLoc == -1) {
        LOG_TRACE("Unable to find uniform with name {} in shader id {}.", name, _shaderId);
        return;
    }
    glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
}

GLuint OpenGLShader::compileShader(std::string& src, GLenum type) {
    
    GLuint shader = glCreateShader(type);
    const char* srcPtr = src.c_str();
    glShaderSource(shader, 1, &srcPtr, nullptr);
    glCompileShader(shader);
    
    GLint shaderSuccess;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderSuccess);
    if (!shaderSuccess) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        LOG_WARN("Shader compiliation failed. Error: {}", infoLog);
    }
    
    return shader;
}

GLint OpenGLShader::getUniformLoc(std::string& name) {
    
    // Find the element in the map if it exists by the uniform name.
    // If it exists, return the value in the map.
    auto it = _uniformLocCache.find(name);
    if (it != _uniformLocCache.end()) {
        return it->second;
    }
    
    // Get the location from the OpenGL server and add to cache if found
    GLint uniformLoc = glGetUniformLocation(_shaderId, name.c_str());
    if (uniformLoc != -1) {
        _uniformLocCache.emplace(name, uniformLoc);
    }
    
    return uniformLoc;
}