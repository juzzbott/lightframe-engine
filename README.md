# Lightframe Engine

A modern, cross-platform 3D game engine written in C++23 with OpenGL rendering support.

## Overview

Lightframe Engine is a lightweight, high-performance game engine designed for learning and experimentation. It features a modular architecture with platform abstraction layers, a robust rendering system, and modern C++ design patterns.

## Features

- **Modern C++23**: Built using the latest C++ standards and best practices
- **Cross-Platform**: Support for Linux and Windows platforms with abstraction layers
- **OpenGL Rendering**: Hardware-accelerated graphics using OpenGL 4.5
- **Modular Architecture**: Clean separation of concerns with distinct subsystems
- **Shader Management**: Runtime shader compilation and management
- **Buffer Abstractions**: Modern vertex buffer and vertex array objects
- **Mesh System**: Efficient mesh representation and rendering
- **Logging System**: Built-in logging for debugging and diagnostics
- **Object ID System**: Unique identification for engine objects
- **Command Buffer**: Queued rendering commands for optimal performance

## Architecture

### Core Components

- **Engine**: Main engine lifecycle management (init, run, shutdown)
- **Window**: Cross-platform window creation and management (GLFW)
- **Platform Layer**: OS-specific implementations (Linux, Windows)
- **Logger**: Centralized logging system
- **Object ID**: Unique identifier generation for engine objects

### Rendering System

- **Renderer API**: Abstract rendering interface
- **OpenGL Backend**: Concrete OpenGL 4.5 implementation
- **Shader**: Shader program compilation and management
- **Buffer**: Vertex and index buffer abstractions
- **Vertex Array**: Vertex array object management
- **Mesh**: Mesh data structure and rendering
- **Material**: Material system (in development)
- **Command Buffer**: Command recording and execution
- **Render Queue**: Efficient rendering queue management

### Third-Party Dependencies

- **GLAD**: OpenGL function loader
- **GLFW**: Cross-platform window and input handling
- **GLM**: Mathematics library for graphics

## Building the Project

### Prerequisites

- CMake 3.10 or higher
- C++23 compatible compiler (GCC 12+, Clang 15+, MSVC 2022+)
- OpenGL 4.5 compatible graphics driver
- GLFW development libraries

### Build Instructions

#### Using the Build Script (Linux/macOS)

```bash
# Basic build
./build.sh

# Build a specific target
./build.sh -target test_bed

# Clean build
./build.sh -c

# Build and run
./build.sh -r

# Run tests
./build.sh -test
```

#### Manual CMake Build

```bash
# Configure
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug

# Build
cmake --build build

# Run the test bed
./build/bin/test_bed
```

### Build Options

- `-c`: Clean the build directory before building
- `-r`: Run the executable after building
- `-test`: Build and run unit tests
- `-target <name>`: Build a specific target (e.g., `test_bed`)

## Project Structure

```
lightframe-engine/
├── lightframe/              # Engine library source
│   ├── src/
│   │   ├── Engine.cpp/h    # Main engine class
│   │   ├── Window.cpp/h    # Window management
│   │   ├── core/           # Core utilities
│   │   ├── debug/          # Debug utilities and assertions
│   │   ├── platform/       # Platform-specific implementations
│   │   └── rendering/      # Rendering subsystem
│   │       └── opengl/     # OpenGL backend
│   └── third-party/        # External dependencies
├── test-bed/               # Test application
│   └── src/
│       └── main.cpp        # Test bed entry point
├── build/                  # Build output directory
├── CMakeLists.txt          # Root CMake configuration
├── build.sh                # Build helper script
└── README.md               # This file
```

## Usage Example

```cpp
#include "Window.h"
#include "platform/Platform.h"
#include "rendering/Shader.h"
#include "rendering/Mesh.h"

int main() {
    // Initialize platform
    Platform::get()->startup();
    
    // Create window
    Window window;
    window.init(WindowSettings {
        .width = 1280,
        .height = 720,
        .title = "My Application",
        .vSyncEnabled = true
    });
    
    // Initialize rendering resources
    // ... create shaders, meshes, etc.
    
    // Main loop
    while (window.isOpen()) {
        window.pollEvents();
        // Render frame
        window.swapBuffers();
    }
    
    // Cleanup
    Platform::get()->shutdown();
    return 0;
}
```

## Development

### Code Style

- C++23 standard features
- `camelCase` for variable names
- `_camelCase` for private member variables
- Doxygen-style comments for documentation
- Prefer `std::unique_ptr` over raw pointers
- OpenGL GLSL version 4.50.x

### VS Code Tasks

The project includes VS Code tasks for common operations:
- **build-engine**: Build the engine and test bed
- **run-tests**: Build and run unit tests

## Roadmap

- [ ] OpenGL rendering backend
- [ ] Physics integration
- [ ] Asset pipeline
- [ ] Scene management
- [ ] Entity Component System (ECS)
- [ ] Material system completion
- [ ] Audio system
- [ ] Advanced lighting models
- [ ] Post-processing effects

## License

This project is licensed under the Apache License 2.0. See the [LICENSE](LICENSE) file for details.

## Contributing

Contributions are welcome! Please ensure your code follows the project's coding standards and includes appropriate tests.

## Acknowledgments

- **GLAD**: OpenGL loader generator
- **GLFW**: Multi-platform library for OpenGL
- **GLM**: Mathematics library for graphics software based on GLSL specifications
