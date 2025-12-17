#include "System_Renderer.h"
-
System_Renderer::System_Renderer(IRenderer& _renderer) : m_renderer(_renderer)
{

}

System_Renderer::Register(GameObjects* _gameObject)
{
	m_objects.push_back(_gameObject);
}

void System_Render::Update(float)
{
    for (auto* obj : m_objects)
    {
        const auto& t = obj->GetTransform();
        m_renderer.DrawQuad(t.x, t.y);
    }
}