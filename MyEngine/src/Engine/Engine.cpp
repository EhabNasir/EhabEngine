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
        float deltaTime = m_timer.GetDeltaTime();
        
        Tick(deltaTime);

        //Temperory frame cap
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    ShutDown();
}

void Engine::Init()
{
    std::cout << "Engine Start\n";

    m_isRunning = true;

    m_timer = Timer();
}

void Engine::Tick(float _deltaTime)
{

}

void Engine::ShutDown()
{
    std::cout << "Engine Shutdown\n";
}