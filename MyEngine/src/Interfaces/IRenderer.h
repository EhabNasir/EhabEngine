#pragma once

struct Camera;

class IRenderer
{
public:
    virtual ~IRenderer() = default;

    virtual bool Init(void* windowHandle) = 0;
    virtual void Shutdown() = 0;

    virtual void BeginFrame(const Camera& camera) = 0;
    virtual void EndFrame() = 0;

    // Debug rendering (for now)
    virtual void DrawQuad(float x, float y, float _sizeX, float _sizeY) = 0;
};
