#pragma once

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#include "Interfaces/IRenderer.h"
#include <bx/math.h>

class Renderer_BGFX : public IRenderer
{
    bool Init(void* windowHandle) override;
    void Shutdown() override;

    void BeginFrame() override;
    void EndFrame() override;

    // Debug rendering (for now)
    void DrawQuad(float x, float y) override;

    bgfx::VertexLayout m_layout;
    bgfx::ProgramHandle m_program;

    bgfx::VertexBufferHandle m_vbh = BGFX_INVALID_HANDLE;
    bgfx::IndexBufferHandle  m_ibh = BGFX_INVALID_HANDLE;

};