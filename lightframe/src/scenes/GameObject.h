
#pragma once

#include "core/ObjectId.h"

#include "components/Component.h"

#include <memory>
#include <vector>

// Forward declare Scene to avoid circular dependency between GameObject and Scene.
class Scene;

class GameObject {
public:

    /**
     * @brief Constructs a GameObject with the given ObjectId. The ObjectId is used for unique identification of the game object within the scene.
     * @param id The ObjectId to assign to this game object.
     */
    explicit GameObject(ObjectId id);

    /**
     * @brief Destroys the GameObject.
     */
    virtual ~GameObject() = default;

    /**
     * @brief Gets the unique ObjectId of this game object.
     * @return The ObjectId of this game object.
     */
    ObjectId getId() const { return _id; }

    /**
     * @brief Sets the scene that owns this game object. This is called by the Scene when the game object is added to the scene.
     * @param scene The scene that owns this game object. This is a non-owning pointer, as the scene owns its game objects.
     */
    void setScene(Scene* scene) { _scene = scene; }

    /**
     * @brief Gets the scene that owns this game object.
     * @return The scene that owns this game object. This is a non-owning pointer, as the scene owns its game objects.
     */
    Scene* getScene() const { return _scene; }

    /**
     * @brief Sets the parent game object for this game object. This establishes a parent-child relationship between the two game objects, but does not transfer ownership (the scene still owns all game objects).
     * @param gameObject The parent game object to set for this game object. This is a non-owning reference, as the scene owns all game objects.
     */
    void setParent(const GameObject& gameObject) { _parentId = gameObject.getId(); }

    /**
     * @brief Adds a component of type T to this game object. The game object takes ownership of the component.
     * @tparam T The type of component to add (must derive from Component).
     * @param args Arguments to forward to the constructor of the component.
     * @return Pointer to the added component (owned by the game object).
     */
    template<typename T, typename... Args>
    T* addComponent(Args&&... args) {
        static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");
        auto component = std::make_unique<T>(std::forward<Args>(args)...);
        T* rawPtr = component.get();
        rawPtr->setGameObject(this);
        _components.push_back(std::move(component));
        return rawPtr;
    }

    /**
     * @brief Gets the first component of type T attached to this game object.
     * @tparam T The type of component to get (must derive from Component).
     * @return Pointer to the component of type T if found, or nullptr if not found.
     */
    template<typename T>
    T* getComponent() const {
        static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");
        for (const auto& component : _components) {
            if (auto* typed = dynamic_cast<T*>(component.get())) {
                return typed;
            }
        }
        return nullptr;
    }

    template<class T>
    T *addChild(T &&child);

private:
    ObjectId _id = ObjectId::empty();
    ObjectId _parentId = ObjectId::empty();
    
    // Non-owning pointer to the scene that owns this game object
    Scene* _scene = nullptr;

    std::vector<std::unique_ptr<Component>> _components;
};