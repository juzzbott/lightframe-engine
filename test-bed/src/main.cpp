#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Window.h"
#include "rendering/Shader.h"
#include "rendering/Buffer.h"
#include "rendering/VertexArray.h"
#include "rendering/Mesh.h"
#include "platform/Platform.h"

glm::vec2 offset(-2.0f, 1.0f);

int main() {
    
    // Startup the platform
    Platform::get()->startup();
    
    // Start application and init window
    Window window;
    window.init(WindowSettings {
        .width = 1280,
        .height = 720,
        .title = "Lightframe Testbed",
        .vSyncEnabled = true
    });
    
    
    std::string vertexShaderSrc = R"(
        #version 450 core
        layout (location = 0) in vec3 position;
        layout (location = 1) in vec3 color;
        
        out vec3 vColor;
        
        uniform vec2 uOffset;
        uniform mat4 uProjection;
        uniform mat4 uView;
        
        void main() {
            vColor = color;
            gl_Position = uProjection * uView * vec4(position.x + uOffset.x, position.y + uOffset.y, position.z, 1.0);
        }
    )";
    
    std::string fragmentShaderSrc = R"(
        #version 450 core
        
        in vec3 vColor;
        
        out vec4 FragColor;
        
        void main() {
            FragColor = vec4(vColor, 1.0);
        }
    )";
    
    std::unique_ptr<Shader> shader = Shader::create();
    shader->loadShader(vertexShaderSrc, fragmentShaderSrc);
    
    Mesh cubeMesh = Mesh::createCubeMesh();
    
    // Projection matrix param
    float fov = glm::radians(45.0f);
    float aspectRatio = 1280.0f / 720.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;
    
    // Create the perspective matrix
    glm::mat4 projMatrix = glm::perspective(fov, aspectRatio, nearPlane, farPlane);
    
    // View matrix (isometric-style camera)
    glm::vec3 cameraPos = glm::normalize(glm::vec3(1.0f, 1.0f, 1.0f)) * 5.0f;
    glm::vec3 targetPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 upDir = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 view = glm::lookAt(cameraPos, targetPos, upDir);

    
    while (!window.shouldClose()) {
        window.clear();
        
        shader->use();
        shader->setFloat2("uOffset", offset.x, offset.y);
        shader->setMat4("uProjection", projMatrix);
        shader->setMat4("uView", view);
        
        cubeMesh.getVertexBuffer()->bind();
        cubeMesh.getIndexBuffer()->bind();
        glDrawElements(GL_TRIANGLES, cubeMesh.getIndexBuffer()->getIndexCount(), GL_UNSIGNED_INT, 0);
        
        window.pollEvents();
        window.swapBuffers();
    }
    
    shader->destroy();
    
    window.shutdown();
    
    // Shutdown the platform
    Platform::get()->shutdown();
    
    return 0;
}