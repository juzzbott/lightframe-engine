#include "Scene.h"

#include "core/ObjectId.h"
#include "scenes/PerspectiveCamera.h"

#include <string>

Scene::Scene(const std::string& name) 
    : _name(name), worldCamera(PerspectiveCamera(ObjectId())) {}