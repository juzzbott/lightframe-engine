#include "RenderQueue.h"
#include "Renderer.h"

#include <algorithm>

void RenderQueue::submit(const RenderCommand& command) {
    _commands.push_back(command);
}

void RenderQueue::sort() {
    std::sort(_commands.begin(), _commands.end(), [](const RenderCommand& a, const RenderCommand& b) {
        return a.renderPass < b.renderPass;
    });
}

void RenderQueue::clear() {
    _commands.clear();
}