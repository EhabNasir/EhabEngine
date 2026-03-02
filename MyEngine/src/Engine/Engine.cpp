#include <iostream>
#include <thread>
#include <algorithm>

#include "Engine.h"
#include "Systems/System_Renderer.h"
#include "Renderer_BGFX.h"
#include "Core/Debug.h"

void Engine::Run()
{
    Init();

    //Camera SetUp
    m_camera.xPos = 0.0f;
    m_camera.yPos = 90.0f;
    m_camera.zoom = 1.0f;

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
        m_renderer->BeginFrame(m_camera);

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

            if(m_systems.size() > 1)
                Debug::DebugPrintArguments("Help");
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



    //Creating window
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // IMPORTANT: bgfx manages graphics not opengl

    window = glfwCreateWindow(
        1920,
        1080,
        "EhabEngine",
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
    m_renderer = new Renderer_BGFX();
    m_renderer->Init(window);
    //creating and adding rendering
    auto rendering = new System_Renderer(m_renderer);

    m_systems.push_back(std::move(rendering));
    //create physics system
    auto physics = new System_Physics();

    physics->InstantiateGameObject();

    for (auto obj : physics->GetGameObjects())
    {
        rendering->Register(obj);
    }

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

    glfwDestroyWindow(window);
    glfwTerminate();
}