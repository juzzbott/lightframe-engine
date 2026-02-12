#include "Renderer.h"

#include "resources/ResourceManager.h"
#include "rendering/opengl/OpenGLRenderer.h"
#include "scenes/Scene.h"
#include "scenes/components/MeshRenderer.h"

#include <memory>

std::unique_ptr<Renderer> Renderer::create(ResourceManager& resourceManager) {
    return std::make_unique<OpenGLRenderer>(resourceManager);
}

void Renderer::renderScene(const Scene& scene) {

    beginFrame();

    for (const auto& gameObject : scene.getGameObjects()) {

        // try and cast to a GameObject3D type. If not able to cast, continue to next
        const auto* gameObject3D = dynamic_cast<const GameObject3D*>(gameObject.get());
        if (!gameObject3D) {
            continue;
        }

        const auto* meshRenderer = gameObject->getComponent<MeshRenderer>();
        if (!meshRenderer) {
            continue;
        }

        RenderState renderState;
        renderState.polygonMode = PolygonMode::Line;
        renderState.cullMode = CullMode::None;

        RenderCommand command = {
            .mesh = meshRenderer->getMesh(),
            .material = meshRenderer->getMaterial(),
            .transform = scene.worldCamera.buildViewProjectionMatrix() * gameObject3D->transform.createModelMatrix(),
            .renderPass = RenderPass::Geometry,
            .renderState = renderState
        };
        submit(command);

    }

    endFrame();
}