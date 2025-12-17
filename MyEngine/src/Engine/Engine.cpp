#include <iostream>
#include <thread>
#include <algorithm>

#include "Engine.h"
#include "Renderer_BGFX.h"

void Engine::Run()
{
    Init();

    //Engine Loop
    while (m_isRunning)
    {
        //frame timing
        //float deltaTime = m_timer.GetDeltaTime();
        float frameData = m_timer.GetDeltaTime();
        accumulator += frameData;

        //spiral of death prevention
        accumulator = std::min(accumulator, maxAccumulator);

        int steps = 0;

        const int maxSteps = 5;

        //begin rendering frame
        m_renderer->BeginFrame();

        while (accumulator >= FPS60 && steps < maxSteps)
        {
            //Fixed timestep
            FixedUpdate(FPS60);


            accumulator -= FPS60;

            steps++;
        }

        //Variable timestep
        Update(frameData);

        for (auto& system : m_systems)
        {
            system->Update(frameData);
        }

        m_renderer->EndFrame();
    }
    
    ShutDown();
}

void Engine::Init()
{
    std::cout << "~EHAB ENGINE~\n";

    m_isRunning = true;

    m_timer.Reset();

    //set renderer
    m_renderer = std::make_unique<Renderer_BGFX>();
    m_renderer->Init();

    //create physics system
    auto physics = std::make_unique<System_Physics>();

    physics->InstantiateGameObject();

    //add system to vector
    m_systems.push_back(std::move(physics));

}

void Engine::Update(float _deltaTime)
{

}

void Engine::FixedUpdate(float _fixedTime)
{
    for (auto& system : m_systems)
    {
        system->FixedUpdate(FPS60);
    }
}

void Engine::ShutDown()
{
    std::cout << "Engine Shutdown\n";
}