/**
 * @file MeshRenderer.h
 * @author Justin McKay
 * @brief Component that can be attached to a game object to render a mesh. This component would typically hold a reference to a Mesh and a Material,
 * and would be responsible for submitting the mesh to the renderer with the appropriate material properties during the rendering phase of the game loop.
 * @date 2026-02-11
 */

#pragma once
#include "Component.h"

#include "rendering/Mesh.h"
#include "rendering/Material.h"

class MeshRenderer : public Component {
public:

    /**
     * @brief Constructs a MeshRenderer component with the given mesh and material. The MeshRenderer does not take ownership of the mesh or material, as they are typically managed by a resource manager.
     * @param mesh Non-owning pointer to the mesh to render (owned by a resource manager).
     * @param material Non-owning pointer to the material to use for rendering (owned by a resource manager).
     */
    MeshRenderer(Mesh* mesh, Material* material) : _mesh(mesh), _material(material) {}

    /**
     * @brief Gets the mesh to render. This is a non-owning pointer, as the mesh is managed by a resource manager.
     * @return Non-owning pointer to the mesh to render (owned by a resource manager).
     */
    Mesh* getMesh() const { return _mesh; }

    /**
     * @brief Gets the material to use for rendering. This is a non-owning pointer, as the material is managed by a resource manager.
     * @return Non-owning pointer to the material to use for rendering (owned by a resource manager).
     */
    Material* getMaterial() const { return _material; }

private:
    // Non-owning pointer to the mesh to render (owned by a resource manager).
    Mesh* _mesh;

    // Non-owning pointer to the material to use for rendering (owned by a resource manager).
    Material* _material;
};
