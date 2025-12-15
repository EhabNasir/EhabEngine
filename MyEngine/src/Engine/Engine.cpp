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

        while (accumulator >= FPS60)
        {
            //Fixed timestep
            FixedUpdate(FPS60);
            accumulator -= FPS60;
        }

        //Variable timestep
        Update(frameData);

        //Temperory frame cap
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
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