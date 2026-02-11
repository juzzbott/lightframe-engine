#pragma once

#include "GameObject3D.h"

#include <glm/glm.hpp>

struct PerspectiveCameraSettings {
    float fieldOfView = 45.0f;
    float viewWidth = 1280.0f;
    float viewHeight = 720.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;
};

class PerspectiveCamera final : public GameObject3D {
public:
    
    /**
     * @brief Constructs a PerspectiveCamera with the given ObjectId and default settings.
     * @param objectId The ObjectId for this camera.
     */
    explicit PerspectiveCamera(ObjectId objectId);
    
    /**
     * @brief Constructs a PerspectiveCamera with the given ObjectId and custom settings.
     * @param objectId The ObjectId for this camera.
     * @param settings The settings for this camera, including field of view, view dimensions, and clipping planes.
     */
    PerspectiveCamera(ObjectId objectId, PerspectiveCameraSettings& settings);
    
    /**
     * Builds the view-projection matrix for this camera. 
     * The projection matrix is calculated using a perspective projection, 
     * and the view matrix is calculated using a lookAt function based on the camera's 
     * position and orientation.
     * @return The combined view-projection matrix for this camera.
     */
    glm::mat4 buildViewProjectionMatrix() const;
    
private:
    PerspectiveCameraSettings _settings;
    
};