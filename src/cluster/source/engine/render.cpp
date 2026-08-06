#include <pch.h>

#include "engine/opengl/engine.h"
#include "engine/render.h"

namespace ObsidianEdge {
void OE_API renderLoop(GLFWwindow *window, const std::atomic<bool> &isRunning,
                       std::atomic<std::vector<RenderObjData> *> &sharedRenderObjData, std::atomic<bool> &swapReady) {
    glfwMakeContextCurrent(window);

    std::vector<RenderObjData> copy;
    OpenGLEngine engine{};

    engine.init();

    while (isRunning) {
        if (!swapReady.load(std::memory_order_acquire)) {
            // TODO: Smart rotate buffer, selective modification

            auto *ptr = sharedRenderObjData.load(std::memory_order_acquire); // Copy to local
            copy = *ptr;
            swapReady.store(true, std::memory_order_release); // Request swap after copy completed
        }

        engine.uploadRenderData(copy);
        engine.update(0.0f);

        glfwSwapBuffers(window);
    }

    engine.yeet();
}
} // namespace ObsidianEdge
