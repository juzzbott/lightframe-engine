# Copilot Instructions

---
applyTo: "**/*.cpp,**/*.h"
---

Use Doxygen-style comments for all C++ functions.

Prefer `std::unique_ptr` over raw pointers.

Use `camelCase` for variable names.
Use `_camelCase` for private member variables.

Ensure that all code generated is targeted for C++23 and C 17.

OpenGL GLSL should target version 4.50.x

When documenting private member variables, for single line comments, prefer double slash comments on the line immediately above. For example: 
// Comment on a single line.
int _privateInt = 0
 
For multi-line comments, prefer the full /** */ style comments.