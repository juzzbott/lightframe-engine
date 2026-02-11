#include "PerspectiveCamera.h"

#include "core/ObjectId.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

PerspectiveCamera::PerspectiveCamera(ObjectId id) 
    : GameObject3D(id), _settings(PerspectiveCameraSettings()) {}
    
PerspectiveCamera::PerspectiveCamera(ObjectId id, PerspectiveCameraSettings& settings)
    : GameObject3D(id), _settings(settings) {}
    
glm::mat4 PerspectiveCamera::buildViewProjectionMatrix() const {
    
    // Projection matrix param
    const float fov = glm::radians(_settings.fieldOfView);
    const float aspectRatio = _settings.viewWidth / _settings.viewHeight;
    
    // Create the perspective matrix
    const glm::mat4 projMatrix = glm::perspective(fov, aspectRatio, _settings.nearPlane, _settings.farPlane);
    
    // View matrix (isometric-style camera)
    const glm::vec3 cameraPos = transform.position;
    constexpr glm::vec3 targetPos = glm::vec3(0.0f, 0.0f, 0.0f);
    constexpr glm::vec3 upDir = glm::vec3(0.0f, 1.0f, 0.0f);
    return projMatrix * glm::lookAt(cameraPos, targetPos, upDir);
}
