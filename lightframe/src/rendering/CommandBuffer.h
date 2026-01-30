#pragma once

#include "RendererApi.h"
#include "RenderQueue.h"

/**
 * @class CommandBuffer
 * @brief A buffer that stores and manages renderer API commands.
 *
 * The CommandBuffer acts as a container for low-level rendering commands,
 * allowing for batch execution and deferred rendering operations.
 */
class CommandBuffer {
public:
    /**
     * @brief Default constructor for CommandBuffer.
     */
    CommandBuffer() = default;
    
    /**
     * @brief Destructor for CommandBuffer.
     *
     * Cleans up any resources and stored commands in the buffer.
     */
    ~CommandBuffer() = default;
    
    /**
     * @brief Adds a renderer API command to the buffer.
     *
     * Appends a new command to the internal command list. The command
     * will be stored until the buffer is executed or cleared.
     *
     * @param command The renderer API command to add to the buffer.
     */
    void build(RenderQueue& queue);
    
    /**
     * @brief Clears all commands from the buffer.
     *
     * Removes all stored commands, resetting the buffer to an empty state.
     * This is typically called after commands have been executed or when
     * resetting the rendering state.
     */
    void clear();
    
    /**
     * @brief Retrieves the list of stored renderer API commands.
     *
     * Returns a const reference to the internal vector of renderer API commands,
     * allowing read-only access to the commands stored in the buffer.
     *
     * @return A const reference to the vector of renderer API commands.
     */
    const std::vector<RendererApiCommand>& getCommands() const { return _commands; }
    
private:
    std::vector<RendererApiCommand> _commands; ///< Internal storage for renderer API commands.
};