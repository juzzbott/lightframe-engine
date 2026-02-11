/**
 * @file GameObjectTemplates.h
 * @author Justin McKay
 * @brief [...add brief description...]
 * @date 2026-02-11
 */

#pragma once

#include "GameObject.h"
#include "Scene.h"
#include <type_traits>

/**
 * @brief Adds a child game object to this game object. The scene takes ownership of the child game object, but this game object establishes a parent-child relationship with the child.
 * @tparam T The type of child game object to add (must derive from GameObject).
 * @param child The child game object to add (will be moved). The scene takes ownership of the child, but this game object establishes a parent-child relationship with the child.
 * @return Pointer to the added child game object (owned by the scene).
 */
template<typename T>
T* GameObject::addChild(T&& child) {
    static_assert(std::is_base_of_v<GameObject, T>, "T must derive from GameObject");

    // Add to scene (scene owns all GameObjects, even children)
    T* childPtr = _scene->addGameObject(std::forward<T>(child));

    // Set parent-child relationship (non-owning, as scene owns all GameObjects)
    childPtr->setParent(*this);
    return childPtr;
}