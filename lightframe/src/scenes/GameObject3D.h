#pragma once

#include "GameObject.h"
#include "core/ObjectId.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Transform3D {
    glm::vec3 position = glm::vec3(0);
    glm::vec3 rotation = glm::vec3(0);
    glm::vec3 scale = glm::vec3(1);

    /**
     * @brief Creates a model matrix from the position, rotation, and scale of this transform. The model matrix is used to transform vertices from local space to world space during rendering.
     * The model matrix is calculated by first applying scaling, then rotation (in ZYX order), and finally translation.
     * @return The model matrix representing the transformation of this object in world space.
     */
    glm::mat4 createModelMatrix() const {

        glm::mat4 translation = glm::translate(glm::mat4(1.0f), position);

        glm::mat4 rx = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1, 0, 0));
        glm::mat4 ry = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0, 1, 0));
        glm::mat4 rz = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0, 0, 1));
        glm::mat4 rotationMat = rz * ry * rx;

        glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), scale);

        return translation * rotationMat * scaleMat;
    }
};

class GameObject3D : public GameObject {
public:
    /**
     * @brief Constructs a GameObject3D with a unique ObjectId.
     */
    GameObject3D();

    /**
     * @brief Constructs a GameObject3D with the specified ObjectId.
     * @param id The ObjectId to assign to this GameObject3D.
     */
    explicit GameObject3D(ObjectId id);

    Transform3D transform;

};