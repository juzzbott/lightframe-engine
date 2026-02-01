#include "Shader.h"
#include "opengl/OpenGLShader.h"
#include "core/Logger.h"
#include "core/Strings.h"

#include <fstream>
#include <sstream>
#include <memory>

std::unique_ptr<Shader> Shader::create(const std::string& shaderPath) {
    // TODO: Platform detection/selection
    return std::make_unique<OpenGLShader>(shaderPath);
}

std::unordered_map<ShaderType, std::string> Shader::loadShaderSources(const std::string& shaderPath) {
    
    std::ifstream file(shaderPath);
    if (!file.is_open()) {
        LOG_WARN("Failed to open shader file: {}", shaderPath);
        return {};
    }
    
    std::unordered_map<ShaderType, std::string> shaderSources;
    
    std::string line;
    std::string currentSection;
    std::stringstream currentSource;
    
    while (std::getline(file, line)) {
        if (line.find("//:") == 0) {
            
            // If the current section is not empty, set the source from the previous section and start a new section
            if (!currentSection.empty()) {
                shaderSources[shaderTypeFromName(currentSection)] = currentSource.str();
                
                // Clear current source for next section
                currentSource.str("");
                currentSource.clear();
            }
            
            currentSection = line.substr(3); // skip "//:"
            
        } else {
            // We're in the main shader source section so add the line to the current source
            currentSource << line << '\n';
        }
    }
    
    // Set the last source into the map
    if (!currentSection.empty()) {
        shaderSources[shaderTypeFromName(currentSection)] = currentSource.str();
    }
    
    return shaderSources;
}

ShaderType Shader::shaderTypeFromName(std::string& name) {
    if (name.length() == 0) {
        return ShaderType::Unknown;
    }
    
    if (strEqualsCi(trim(name), "vertex")) {
        return ShaderType::Vertex;
    }
    
    if (strEqualsCi(trim(name), "fragment")) {
        return ShaderType::Fragment;
    }
    
    // Unknown string, so return unknown
    return ShaderType::Unknown;
}