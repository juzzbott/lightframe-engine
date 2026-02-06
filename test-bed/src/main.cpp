#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window.h"
#include "managers/ShaderManager.h"
#include "managers/TextureManager.h"
#include "rendering/Shader.h"
#include "rendering/Material.h"
#include "rendering/Mesh.h"
#include "rendering/Renderer.h"
#include "platform/Platform.h"
#include <rendering/RendererApi.h>

glm::vec2 offset(-2.0f, 1.0f);

struct Transform {
    glm::vec3 position = glm::vec3(0);
    glm::vec3 rotation = glm::vec3(0);
    glm::vec3 scale = glm::vec3(1);
};
    
glm::mat4 createModelMatrix(Transform& transform) {
    
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), transform.position);
    
    glm::mat4 rx = glm::rotate(glm::mat4(1.0f), glm::radians(transform.rotation.x), glm::vec3(1, 0, 0));
    glm::mat4 ry = glm::rotate(glm::mat4(1.0f), glm::radians(transform.rotation.y), glm::vec3(0, 1, 0));
    glm::mat4 rz = glm::rotate(glm::mat4(1.0f), glm::radians(transform.rotation.z), glm::vec3(0, 0, 1));
    glm::mat4 rotation = rz * ry * rx;
    
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), transform.scale);
    
    return translation * rotation * scale;
}

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
    
    ShaderManager shaderManager;
    ShaderHandle shaderHndl = shaderManager.loadShader("/home/justin/Development/lightframe-engine/test-bed/assets/shaders/default.shader", "default");
    
    TextureManager textureManager;
    TextureHandle textureHndl = textureManager.loadTexture("/home/justin/Pictures/wallhaven-5g2y73.jpg", "frog_man");
    
    std::unique_ptr<Renderer> renderer = Renderer::create(shaderManager, textureManager);
    
    Mesh cubeMesh = Mesh::createCubeMesh();
    //std::unique_ptr<Texture2D> texture = Texture2D::create("/home/justin/Pictures/wallhaven-5g2y73.jpg");
    //std::unique_ptr<Texture2D> texture2 = Texture2D::create("/home/justin/Pictures/wallhaven-5wj3z7.jpg");
    
    // Projection matrix param
    float fov = glm::radians(45.0f);
    float aspectRatio = 1280.0f / 720.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;
    
    // Create the perspective matrix
    glm::mat4 projMatrix = glm::perspective(fov, aspectRatio, nearPlane, farPlane);
    
    // View matrix (isometric-style camera)
    glm::vec3 cameraPos = glm::normalize(glm::vec3(0.0f, -1.0f, 1.0f)) * 5.0f;
    glm::vec3 targetPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 upDir = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 view = glm::lookAt(cameraPos, targetPos, upDir);

    Transform transform;
    glm::mat4 modelProj = createModelMatrix(transform);
    
    Material material;
    material.addShader(RenderPass::Geometry, shaderHndl);
    material.setDiffuseMap(textureHndl);
    
    RenderCommand command = {
        .mesh = &cubeMesh,
        .material = &material,
        .transform = projMatrix * view * modelProj,
        .renderPass = RenderPass::Geometry,
    };
    
    
    while (!window.shouldClose()) {
        window.clear();
        
        // Renderer 
        renderer->beginFrame();
        renderer->submit(command);
        renderer->endFrame();
        
        window.pollEvents();
        window.swapBuffers();
    }
    
    window.shutdown();
    
    // Shutdown the platform
    Platform::get()->shutdown();
    
    return 0;
}