#pragma once

#include <string>

// Forward declaration to avoid including GLFW in header
struct GLFWwindow;

struct WindowSettings {
    int width;
    int height;
    std::string title;
    bool vSyncEnabled;
};

class Window {
public:

    /**
     * @brief Initializes the window with the specified settings.
     * @param windowProps The settings to configure the window (width, height, title, vSync).
     * @return true if initialization succeeded, false otherwise.
     */
    bool init(WindowSettings windowProps);
    
    /**
     * @brief Shuts down the window and releases associated resources.
     */
    void shutdown();
    
    /**
     * @brief Polls for and processes pending window events.
     */
    void pollEvents();
    
    /**
     * @brief Checks if the window should close.
     * @return true if the window has been requested to close, false otherwise.
     */
    bool shouldClose() const;
    
    /**
     * @brief Swaps the front and back buffers for this window.
     */
    void swapBuffers();
    
    /**
     * @brief Clears the window's color buffer.
     */
    void clear();
    
private:
    // Pointer to the underlying GLFW window
    GLFWwindow* _windowPtr;
};