#include "Engine.h"
#include <iostream>
#include <thread>

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

        int steps;

        const int maxSteps = 5;

        while (accumulator >= FPS60 && steps < maxSteps)
        {
            //Fixed timestep
            FixedUpdate(FPS60);
            accumulator -= FPS60;

            steps++;
        }

        //Variable timestep
        Update(frameData);
    }
    
    ShutDown();
}

void Engine::Init()
{
    std::cout << "Engine Start\n";

    m_isRunning = true;

    m_timer.Reset();
}

void Engine::Update(float _deltaTime)
{

}

void Engine::FixedUpdate(float _fixedTime)
{

}

void Engine::ShutDown()
{
    std::cout << "Engine Shutdown\n";
}