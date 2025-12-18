#define GLFW_EXPOSE_NATIVE_WIN32

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "Renderer_BGFX.h"

bool Renderer_BGFX::Init(void* windowHandle)
{
    bgfx::Init init{};
    init.type = bgfx::RendererType::Count;
    init.resolution.width = 800;
    init.resolution.height = 600;
    init.resolution.reset = BGFX_RESET_VSYNC;

    // -----------------------------
    // Platform data (CORRECT WAY)
    // -----------------------------
    bgfx::PlatformData pd{};
    pd.nwh = glfwGetWin32Window(
        static_cast<GLFWwindow*>(windowHandle)
    );
    pd.ndt = nullptr;
    pd.context = nullptr;
    pd.backBuffer = nullptr;
    pd.backBufferDS = nullptr;

    init.platformData = pd;

    // -----------------------------
    // Init bgfx
    // -----------------------------
    if (!bgfx::init(init))
        return false;

    bgfx::setViewRect(0, 0, 0, 800, 600);
    bgfx::setViewClear(
        0,
        BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
        0x303030ff,
        1.0f,
        0
    );

    return true;
}

void Renderer_BGFX::BeginFrame()
{
	bgfx::touch(0);
}
void Renderer_BGFX::EndFrame()
{
	bgfx::frame();
}

void Renderer_BGFX::Shutdown()
{
	bgfx::shutdown();
}

// Debug rendering (for now)
void Renderer_BGFX::DrawQuad(float x, float y)
{

}