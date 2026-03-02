#pragma once

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#include "Core/Vector3.h"
#include "Interfaces/IRenderer.h"
#include "Systems/Camera.h"
#include <bx/math.h>

class Renderer_BGFX : public IRenderer
{
    bool Init(void* windowHandle) override;
    void Shutdown() override;

    void BeginFrame(const Camera& camera) override;
    void EndFrame() override;

    // Debug rendering (for now)
    void DrawQuad(float x, float y, float _sizeX, float _sizeY) override;

    bgfx::VertexLayout m_layout;
    bgfx::ProgramHandle m_program;

    bgfx::VertexBufferHandle m_vbh = BGFX_INVALID_HANDLE;
    bgfx::IndexBufferHandle  m_ibh = BGFX_INVALID_HANDLE;

private:
    uint16_t m_width = 1920;
    uint16_t m_height = 1080;

    float m_projMatrix[16];
};