#define GLFW_INCLUDE_NONE
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window.h"
#include "resources/ResourceManager.h"
#include "rendering/Material.h"
#include "rendering/Mesh.h"
#include "rendering/Renderer.h"
#include "platform/Platform.h"
#include "scenes/Scene.h"
#include "scenes/SceneTemplates.h"
#include <rendering/RendererApi.h>

#include "scenes/components/MeshRenderer.h"

glm::vec2 offset(-2.0f, 1.0f);

struct Transform {
    glm::vec3 position = glm::vec3(0);
    glm::vec3 rotation = glm::vec3(0);
    glm::vec3 scale = glm::vec3(1);
};

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
    
    Scene scene = Scene("main_level");
    scene.worldCamera.transform.position = glm::vec3(0.0f, -3.5f, 3.5f);
    
    ResourceManager resourceManager;
    ShaderHandle shaderHndl = resourceManager.load<Shader>("/home/justin/Development/lightframe-engine/test-bed/assets/shaders/default.shader", "default");
    TextureHandle textureHndl = resourceManager.load<Texture2D>("/home/justin/Pictures/wallhaven-5g2y73.jpg", "frog_man");
    
    std::unique_ptr<Renderer> renderer = Renderer::create(resourceManager);
    
    Mesh cubeMesh = Mesh::createCubeMesh();
    Mesh sphereMesh = Mesh::createSphereMesh(640, 640);
    
    Material material;
    material.addShader(RenderPass::Geometry, shaderHndl);
    material.setDiffuseMap(textureHndl);

    auto* player = scene.addGameObject<GameObject3D>(ObjectId());
    player->transform.position = glm::vec3(0.0f, 0.0f, 0.0f);
    player->transform.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    scene.getGameObjects()[0]->addComponent<MeshRenderer>(&cubeMesh, &material);

    auto* player2 = scene.addGameObject<GameObject3D>(ObjectId());
    player2->transform.position = glm::vec3(2.0f, -1.0f, 0.0f);
    player2->transform.rotation = glm::vec3(45.0f, 45.0f, 0.0f);
    scene.getGameObjects()[1]->addComponent<MeshRenderer>(&cubeMesh, &material);

    auto* player3 = scene.addGameObject<GameObject3D>(ObjectId());
    player3->transform.position = glm::vec3(-2.0f, 1.0f, 0.0f);
    player3->transform.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    scene.getGameObjects()[2]->addComponent<MeshRenderer>(&sphereMesh, &material);

    // Main Application Loop
    while (!window.shouldClose()) {
        window.clear();
        
        // Renderer 
        renderer->renderScene(scene);
        
        window.pollEvents();
        window.swapBuffers();
    }
    
    window.shutdown();
    
    // Shutdown the platform
    Platform::get()->shutdown();
    
    return 0;
}