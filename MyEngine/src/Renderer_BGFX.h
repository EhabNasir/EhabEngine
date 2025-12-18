#pragma once
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#include "Interfaces/IRenderer.h"

class Renderer_BGFX : public IRenderer
{
    bool Init(void* windowHandle) override;
    void Shutdown() override;

    void BeginFrame() override;
    void EndFrame() override;

    // Debug rendering (for now)
    void DrawQuad(float x, float y) override;
};