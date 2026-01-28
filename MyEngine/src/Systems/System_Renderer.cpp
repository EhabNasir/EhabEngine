#include "System_Renderer.h"
#include "Core/Debug.h"

System_Renderer::System_Renderer(IRenderer* _renderer) : m_renderer(_renderer)
{

}

void System_Renderer::Register(GameObjects* _gameObject)
{
	m_objects.push_back(_gameObject);
}

void System_Renderer::Update(float)
{
    Debug::DebugPrintArguments("%f", m_objects.size());

    for (auto* obj : m_objects)
    {
        const auto& t = obj->GetTransform();
        m_renderer->DrawQuad(t.x, t.y, 0.5f, 0);
    }
}