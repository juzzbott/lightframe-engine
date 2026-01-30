#include "Window.h"

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
    // TODO: Implement input
    if (action == GLFW_PRESS)
    {
        switch (key)
        {
            default:
            break;
        }
    }
}

bool Window::init(WindowSettings windowProps) {
    #ifdef LF_PLATFORM_LINUX
    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
    #endif
    #ifdef LF_PLATFORM_WINDOWS
    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_WIN32);
    #endif
    
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW." << std::endl;
        return false;        
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    _windowPtr = glfwCreateWindow(windowProps.width, windowProps.height, windowProps.title.c_str(), nullptr, nullptr);
    if (_windowPtr == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    
    glfwSetKeyCallback(_windowPtr, keyCallback);
    
    glfwMakeContextCurrent(_windowPtr);
    
    // Now that we have a context, load OpenGL functions using GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD." << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glEnable(GL_DEPTH_TEST);
    
    // Set initial clear color
    glClearColor(0.2f, 0.4f, 0.6f, 1.0f);
    
    return true;
}

void Window::shutdown() {
    
    if (_windowPtr != nullptr) {   
        glfwDestroyWindow(_windowPtr);
        _windowPtr = nullptr;
    }
    
    glfwTerminate();
}

void Window::pollEvents() {
    glfwPollEvents();
}

bool Window::shouldClose() const {
    return _windowPtr ? glfwWindowShouldClose(_windowPtr) : true;
}

void Window::swapBuffers() {
    if (_windowPtr) {   
        glfwSwapBuffers(_windowPtr);
    }
}

void Window::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}