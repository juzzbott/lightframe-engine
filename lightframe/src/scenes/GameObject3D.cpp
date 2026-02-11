/**
 * @file GameObject3D.cpp
 * @author Justin McKay
 * @brief [...add brief description...]
 * @date 2026-02-11
 */

#include "GameObject3D.h"
#include "GameObject.h"

GameObject3D::GameObject3D() : GameObject(ObjectId()) {}

GameObject3D::GameObject3D(ObjectId id) : GameObject(id) {}