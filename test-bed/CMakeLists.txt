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
# Lightframe Engine Test Bed Application
# ========================================
add_executable(test_bed
        src/main.cpp
)

target_include_directories(test_bed PRIVATE
        "src"
)

if (WIN32)
    target_link_libraries(test_bed 
        PUBLIC 
            opengl32 glfw3
        PRIVATE 
            lightframe)
    target_compile_definitions(test_bed PUBLIC LF_PLATFORM_WINDOWS)
elseif (UNIX)
    target_link_libraries(test_bed 
        PUBLIC 
            glfw GL
        PRIVATE 
            lightframe)
    target_include_directories(test_bed PRIVATE /usr/include ../lightframe/third-party)
    link_directories(/usr/lib /usr/local/lib)
    target_compile_definitions(test_bed PUBLIC LF_PLATFORM_LINUX)
endif ()

# ========================================
# Build Configurations
# ========================================
foreach (target test_bed)

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