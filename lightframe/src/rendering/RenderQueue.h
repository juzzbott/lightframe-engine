#pragma once

#include "RendererApi.h"

#include <vector>

/**
 * @class RenderQueue
 * @brief Manages a queue of render commands for efficient batch rendering.
 *
 * The RenderQueue collects render commands during the frame and provides
 * functionality to sort and organize them for optimal rendering performance.
 */
class RenderQueue {
public:
    /**
     * @brief Default constructor for RenderQueue.
     */
    RenderQueue() = default;
    
    /**
     * @brief Destructor for RenderQueue.
     *
     * Cleans up any resources held by the render queue.
     */
    ~RenderQueue() = default;

    /**
     * @brief Submits a render command to the queue.
     *
     * Adds a new render command to the internal command buffer. Commands
     * submitted will be processed during the rendering phase.
     *
     * @param command The render command to add to the queue.
     */
    void submit(const RenderCommand& command);
    
    /**
     * @brief Sorts the render commands in the queue.
     *
     * Organizes commands for optimal rendering order. This typically involves
     * sorting by depth, material, or other criteria to minimize state changes
     * and improve rendering performance.
     */
    void sort();
    
    /**
     * @brief Retrieves the list of render commands.
     *
     * Returns a const reference to the internal vector of render commands,
     * allowing read-only access to the queued commands.
     *
     * @return A const reference to the vector of render commands.
     */
    const std::vector<RenderCommand>& getCommands() const { return _commands;};
    
    /**
     * @brief Clears all render commands from the queue.
     *
     * Removes all stored commands, resetting the queue to an empty state.
     * This is typically called after rendering is complete for the frame or at 
     * the start of a new frame.
     */
    void clear();
    
private:
    std::vector<RenderCommand> _commands;
    
};