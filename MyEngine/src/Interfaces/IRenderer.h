#pragma once

class IRenderer
{
public:
    virtual ~IRenderer() = default;

    virtual bool Init() = 0;
    virtual void Shutdown() = 0;

    virtual void BeginFrame() = 0;
    virtual void EndFrame() = 0;

    // Debug rendering (for now)
    virtual void DrawQuad(float x, float y) = 0;
};
