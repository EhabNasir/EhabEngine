#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define GLFW_EXPOSE_NATIVE_WIN32

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <fstream>

#include "Renderer_BGFX.h"

struct PosVertex
{
    float x;
    float y;
    float z;
};

static PosVertex s_vertices[] =
{
    { -0.5f,  0.5f, 0.0f },
    {  0.5f,  0.5f, 0.0f },
    {  0.5f, -0.5f, 0.0f },
    { -0.5f, -0.5f, 0.0f },
};

static const uint16_t s_indices[] =
{
    0, 1, 2,
    0, 2, 3
};

static bgfx::ShaderHandle LoadShader(const char* path)
{
    FILE* file = fopen(path, "rb");
    if (!file)
        return BGFX_INVALID_HANDLE;

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    const bgfx::Memory* mem = bgfx::alloc(size + 1);
    fread(mem->data, 1, size, file);
    fclose(file);

    mem->data[mem->size - 1] = '\0'; // bgfx requires null-terminated shader data

    return bgfx::createShader(mem);
}


bool Renderer_BGFX::Init(void* windowHandle)
{
    bgfx::Init init{};
    init.type = bgfx::RendererType::Count;
    init.resolution.width = 800;
    init.resolution.height = 600;
    init.resolution.reset = BGFX_RESET_VSYNC;

    // -----------------------------
    // Platform data (CORRECT WAY)
    // -----------------------------
    bgfx::PlatformData pd{};
    pd.nwh = glfwGetWin32Window(
        static_cast<GLFWwindow*>(windowHandle)
    );
    pd.ndt = nullptr;
    pd.context = nullptr;
    pd.backBuffer = nullptr;
    pd.backBufferDS = nullptr;

    init.platformData = pd;

    // -----------------------------
    // Init bgfx
    // -----------------------------
    if (!bgfx::init(init))
        return false;

    bgfx::setViewRect(0, 0, 0, 800, 600);
    bgfx::setViewClear(
        0,
        BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
        0x303030ff,
        1.0f,
        0
    );

    bgfx::ShaderHandle vs = LoadShader("shaders/bin/dx11/simple.vs.bin");
    bgfx::ShaderHandle fs = LoadShader("shaders/bin/dx11/simple.fs.bin");

    BX_ASSERT(bgfx::isValid(vs), "Vertex shader invalid");
    BX_ASSERT(bgfx::isValid(fs), "Fragment shader invalid");
    m_program = bgfx::createProgram(vs, fs, true);
    BX_ASSERT(bgfx::isValid(m_program), "Program invalid");


    m_layout.begin()
        .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
        .end();

    m_vbh = bgfx::createVertexBuffer(
        bgfx::makeRef(s_vertices, sizeof(s_vertices)),
        m_layout
    );

    m_ibh = bgfx::createIndexBuffer(
        bgfx::makeRef(s_indices, sizeof(s_indices))
    );

    return true;
}

void Renderer_BGFX::BeginFrame()
{
	bgfx::touch(0);

    float view[16];
    float proj[16];

    bx::mtxIdentity(view);
    bx::mtxIdentity(proj);

    bgfx::setViewTransform(0, view, proj);
    // Identity transform
    float mtx[16];
    bx::mtxIdentity(mtx);
    //bgfx::setTransform(mtx);

    bgfx::setVertexBuffer(0, m_vbh);
    bgfx::setIndexBuffer(m_ibh);
    //bgfx::setState(BGFX_STATE_DEFAULT);
    bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A);




    bgfx::submit(0, m_program);
}
void Renderer_BGFX::EndFrame()
{
	bgfx::frame();
}

void Renderer_BGFX::Shutdown()
{
	bgfx::shutdown();
}

// Debug rendering (for now)
void Renderer_BGFX::DrawQuad(float x, float y)
{

}