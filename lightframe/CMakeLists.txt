# ========================================
# Dependencies
# ========================================

# GLFW (system installed)
find_package(glfw3 CONFIG REQUIRED)

# Explicitly set the policy to prefer GLVND
if(POLICY CMP0072)
    cmake_policy(SET CMP0072 NEW)
endif()

# OpenGL
find_package(OpenGL REQUIRED)

# ========================================
# Lightframe Engine Library
# ========================================
add_library(lightframe
        src/Engine.h
        src/Engine.cpp
        src/Window.h
        src/Window.cpp
        src/debug/Assertions.h
        src/platform/Platform.h
        src/platform/Platform.cpp
        src/platform/LinuxPlatform.h
        src/platform/LinuxPlatform.cpp
        src/platform/WindowsPlatform.h
        src/platform/WindowsPlatform.cpp
        src/core/Logger.h
        src/core/Logger.cpp
        src/core/ObjectId.h
        src/core/ObjectId.cpp
        src/resources/ResourceManager.h
        src/resources/ResourceManager.cpp
        src/rendering/Buffer.h
        src/rendering/Buffer.cpp
        src/rendering/Material.h
        src/rendering/Material.cpp
        src/rendering/Mesh.h
        src/rendering/Mesh.cpp
        src/rendering/Renderer.h
        src/rendering/Renderer.cpp
        src/rendering/RenderQueue.h
        src/rendering/RenderQueue.cpp
        src/rendering/Shader.h
        src/rendering/Shader.cpp
        src/rendering/Texture.h
        src/rendering/Texture.cpp
        src/rendering/VertexArray.h
        src/rendering/VertexArray.cpp
        src/rendering/opengl/OpenGLShader.h
        src/rendering/opengl/OpenGLShader.cpp
        src/rendering/opengl/OpenGLBuffer.h
        src/rendering/opengl/OpenGLBuffer.cpp
        src/rendering/opengl/OpenGLTexture.h
        src/rendering/opengl/OpenGLTexture.cpp
        src/rendering/opengl/OpenGLVertexArray.h
        src/rendering/opengl/OpenGLVertexArray.cpp
        src/rendering/opengl/OpenGLRenderer.h
        src/rendering/opengl/OpenGLRenderer.cpp
        src/scenes/GameObject.h
        src/scenes/GameObject.cpp
        src/scenes/GameObject3D.h
        src/scenes/PerspectiveCamera.h
        src/scenes/PerspectiveCamera.cpp
        src/scenes/Scene.h
        src/scenes/Scene.cpp
        src/glad.c
        third-party/stb/stb_image.cpp
        src/scenes/components/Component.h
        src/scenes/components/MeshRenderer.cpp
        src/scenes/components/MeshRenderer.h
        src/scenes/GameObject3D.cpp
        src/scenes/GameObjectTemplates.h
        src/scenes/SceneTemplates.h
)

target_include_directories(lightframe 
    PUBLIC
        "src"
        "third-party"
)

if (WIN32)
    target_link_libraries(lightframe PRIVATE opengl32 glfw3)
    target_compile_definitions(lightframe PUBLIC LF_PLATFORM_WINDOWS)
elseif (UNIX)
    target_link_libraries(lightframe PRIVATE glfw GL)
    target_include_directories(lightframe PRIVATE /usr/include)
    link_directories(/usr/lib /usr/local/lib)
    target_compile_definitions(lightframe PUBLIC LF_PLATFORM_LINUX)
endif ()

# ========================================
# Build Configurations
# ========================================
foreach (target lightframe)

    set_target_properties(${target} PROPERTIES LINKER_LANGUAGE CXX)

    target_compile_definitions(${target} PRIVATE
            $<$<CONFIG:Debug>:DEBUG>
            $<$<CONFIG:Release>:NDEBUG>
    )
    target_compile_options(${target} PRIVATE
            $<$<CONFIG:Debug>:-g>
            $<$<CONFIG:Release>:-O3>
    )
endforeach ()