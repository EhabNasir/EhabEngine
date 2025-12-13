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
        auto now = clock::now();
        std::chrono::duration<float> delta = now - m_lastTime;
        m_lastTime = now;

        float deltaTime = delta.count();

        Tick(deltaTime);

        //Temperory frame cap
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    ShutDown();
}

void Engine::Init()
{
   //using clock = std::chrono::high_resolution_clock;

    m_lastTime = clock::now();

    std::cout << "Engine Start\n";

    m_isRunning = true;

}

void Engine::Tick(float _deltaTime)
{
}

void Engine::ShutDown()
{
    std::cout << "Engine Shutdown\n";
}