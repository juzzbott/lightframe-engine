#pragma once

#include "PerspectiveCamera.h"

#include <memory>
#include <vector>

// Forward declare GameObject to avoid circular dependency between Scene and GameObject.
class GameObject;

class Scene {
public:

    /**
     * @brief Constructs a Scene with the given name. The name is used for identification and debugging purposes.
     * @param name The name of the scene, used for identification and debugging purposes.
     */
    explicit Scene(const std::string& name);

    /**
     * @brief Gets all game objects in the scene.
     * @return Const reference to the vector of game objects.
     */
    const std::vector<std::unique_ptr<GameObject>>& getGameObjects() const { return _gameObjects; }

    template<class T, class ... Args>
    T *addGameObject(Args &&... args);

    // The main camera for the scene. This is a public member for easy access, but it can be modified directly by game logic or systems as needed.
    PerspectiveCamera worldCamera;
    
private:
    std::string _name;
    
    // Scene owns all game objects
    std::vector<std::unique_ptr<GameObject>> _gameObjects;

};