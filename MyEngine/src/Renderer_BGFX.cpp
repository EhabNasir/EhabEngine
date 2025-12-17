#include "Renderer_BGFX.h"

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

bool Renderer_BGFX::Init()
{
    //bgfx::PlatformData pd{};
    //pd.nwh = hwnd;   // native window handle
    //bgfx::setPlatformData(pd);

    bgfx::Init init;
    init.type = bgfx::RendererType::Count; // auto-select backend
    init.resolution.width = 800;
    init.resolution.height = 600;
    init.resolution.reset = BGFX_RESET_VSYNC;

    if (!bgfx::init(init))
        return false;

    bgfx::setViewClear(
        0,
        BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
        0x303030ff,
        1.0f,
        0
    );

    bgfx::setViewRect(0, 0, 0, 800, 600);

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