/**
 * @file SceneTemplates.h
 * @author Justin McKay
 * @brief [...add brief description...]
 * @date 2026-02-11
 */

#pragma once

#include "GameObject.h"
#include "Scene.h"
#include <type_traits>

/**
 * @brief Adds a game object to the scene. The scene takes ownership of the object.
 * @tparam T The type of game object to add (must derive from GameObject).
 * @param gameObject The game object to add to the scene (will be moved).
 * @return Pointer to the added game object (owned by the scene).
 */
template<typename T, typename... Args>
T* Scene::addGameObject(Args&&... args) {
    static_assert(std::is_base_of_v<GameObject, T>, "T must derive from GameObject");
    auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
    T* rawPtr = ptr.get();
    rawPtr->setScene(this);
    _gameObjects.push_back(std::move(ptr));
    return rawPtr;
}