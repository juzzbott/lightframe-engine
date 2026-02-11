/**
 * @file Component.h
 * @author Justin McKay
 * @brief Base class for components that can be attached to game objects in a scene.
 * Components encapsulate specific functionality or behavior that can be added to game objects, allowing for flexible and modular design.
 * Examples of components include renderable meshes, physics colliders, scripts, and more.
 * @date 2026-02-11
 */

#pragma once

// Forward declaration of GameObject to avoid circular dependency.
class GameObject;

class Component {
public:
    virtual ~Component() = default;

    /**
     * @brief Sets the game object that this component is attached to. This is called by the GameObject when the component is added.
     * @param gameObject The game object that this component is attached to. This is a non-owning pointer, as the game object owns its components.
     */
    void setGameObject(GameObject* gameObject) { _gameObject = gameObject; }

    /**
    * @brief Gets the game object that this component is attached to.
    * @return A pointer to the game object that this component is attached to. This is a non-owning pointer, as the game object owns its components.
    */
    GameObject* getGameObject() const { return _gameObject; }

private:
    // Non-owning pointer to the game object this component is attached to.
    GameObject* _gameObject = nullptr;
};