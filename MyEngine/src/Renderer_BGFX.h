#pragma once
#include "Interfaces/IRenderer.h"

class Renderer_BGFX : IRenderer
{
    bool Init() override;
    void Shutdown() override;

    void BeginFrame() override;
    void EndFrame() override;

    // Debug rendering (for now)
    void DrawQuad(float x, float y) override;
};