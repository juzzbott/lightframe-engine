/**
 * @file ResourceManager.h
 * @author Justin McKay
 * @brief [...add brief description...]
 * @date 2026-02-12
 */

#pragma once

#include "debug/Assertions.h"

// Resource types
#include "rendering/Material.h"
#include "rendering/Mesh.h"
#include "rendering/Shader.h"
#include "rendering/Texture.h"

#include <variant>
#include <memory>

using ResourceVariant = std::variant<
    std::unique_ptr<Texture2D>,
    std::unique_ptr<Shader>,
    std::unique_ptr<Mesh>,
    std::unique_ptr<Material>
>;

using ResourceHandle = uint32_t;

class ResourceManager {
public:


    template<typename T>
    ResourceHandle load(const std::string& filePath, const std::string& resourceName) {

        ResourceVariant resource;
        if constexpr (std::is_same_v<T, Texture2D>) {
            resource = Texture2D::create(filePath);
        } else if constexpr (std::is_same_v<T, Shader>) {
            resource = Shader::create(filePath);
        } else {
            LF_ASSERT_MSG(false, "Unable to load unknown resource type.");
        }

        ResourceHandle newHandle = ++_lastHandle;

        _resourceNameMap.try_emplace(resourceName, newHandle);
        _resources.try_emplace(newHandle, std::move(resource));
        return newHandle;
    }


    template<typename T>
    T& get(ResourceHandle handle) {
        LF_ASSERT_MSG(_resources.contains(handle), std::format("No resource handle {} found.", handle));

        return *std::get<std::unique_ptr<T>>(_resources[handle]);
    }

private:
    // Maps resource names to their handles
    std::unordered_map<std::string, ResourceHandle> _resourceNameMap = {};

    // Map of resource handles to resource type instances
    std::unordered_map<ResourceHandle, ResourceVariant> _resources = {};

    // Last assigned texture handle
    ResourceHandle _lastHandle = 0;

};