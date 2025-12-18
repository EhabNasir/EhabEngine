#include <iostream>
#include <thread>
#include <algorithm>

#include "Engine.h"
#include "Renderer_BGFX.h"

void Engine::Run()
{
    Init();

    //Engine Loop
    while (!glfwWindowShouldClose(window) && m_isRunning)
    {
        glfwPollEvents();
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

    //create physics system
    auto physics = std::make_unique<System_Physics>();

    physics->InstantiateGameObject();

    //add system to vector
    m_systems.push_back(std::move(physics));

    //Creating window
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // IMPORTANT: bgfx manages graphics not opengl

    window = glfwCreateWindow(
        800,
        600,
        "MyEngine",
        nullptr,
        nullptr
    );

    if (!window)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    bgfx::renderFrame();

    //set renderer
    m_renderer = std::make_unique<Renderer_BGFX>();
    m_renderer->Init(window);
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

    glfwDestroyWindow(window);
    glfwTerminate();
}