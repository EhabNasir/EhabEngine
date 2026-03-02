#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define GLFW_EXPOSE_NATIVE_WIN32

#include "direct.h"
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
    char cwd[512];
    _getcwd(cwd, sizeof(cwd));
    BX_TRACE("CWD = %s", cwd);
    BX_TRACE("Trying to open: %s", path);

    FILE* file = fopen(path, "rb");
    BX_ASSERT(file, "errrr");
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
    init.type = bgfx::RendererType::Direct3D11;
    init.resolution.width = 1920;
    init.resolution.height = 1080;
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

    //Setting view projection
    bgfx::setViewRect(0, 0, 0, 1920, 1080);
    float view[16];
    float proj[16];

    //Build projection matrix
    //Map world coordinates to NDC
    bx::mtxIdentity(view);
    bx::mtxOrtho(proj,
        -float(m_width / 2.0f), float(m_width / 2.0f),
        -float(m_height / 2.0f), float(m_height / 2.0f),
        -1.0f, 1.0f, 
        0.0f,
        bgfx::getCaps()->homogeneousDepth);

    bgfx::setViewTransform(0, view, proj);
    bgfx::setViewClear(
        0,
        BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
        0x303030ff,
        1.0f,
        0);

    bgfx::ShaderHandle fs = LoadShader("../../../Shaders/bin/dx11/simple.fs.bin");
    bgfx::ShaderHandle vs = LoadShader("../../../Shaders/bin/dx11/simple.vs.bin");

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

void Renderer_BGFX::BeginFrame(const Camera& camera)
{
	bgfx::touch(0);

    //Setting view projection
    bgfx::setViewRect(0, 0, 0, m_width, m_height);

    //bx::mtxIdentity(proj);

    float view[16];
    float proj[16];

    //bx::mtxIdentity(view);
    // Build view matrix from camera position
    bx::mtxTranslate(view, -camera.xPos, -camera.yPos, 0.0f);

    // Build projection with zoom applied
    float halfWidth = (m_width / 2.0f) / camera.zoom;
    float halfHeight = (m_height / 2.0f) / camera.zoom;

    bx::mtxOrtho(
        proj,
        -halfWidth, halfWidth,   // left, right
        -halfHeight, halfHeight,  // bottom, top
        -1.0f, 1.0f,             // near, far
        0.0f,
        bgfx::getCaps()->homogeneousDepth
    );

    bgfx::setViewTransform(0, view, proj);
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
void Renderer_BGFX::DrawQuad(float _posX, float _posY, float _sizeX, float _sizeY)
{       
    // Identity transform
    float mtxTrans[16];
    float mtxScale[16];
    float mtxRotate[16];

    float mtx[16];
    //bx::mtxIdentity(mtx);
    bx::mtxScale(mtxScale, _sizeX, _sizeY, 1.0f);
    bx::mtxTranslate(mtxTrans, _posX, _posY, 0.0f);
    bx::mtxIdentity(mtxRotate);

    //bx::mtxSRT(mtx, );

    bx::mtxMul(mtx, mtxTrans, mtxScale);
    //bx::mtxMul(mtx, mtxScale, mtxRotate);
    //bx::mtxMul(mtx, mtxRotate, mtxTrans);

    bgfx::setTransform(mtx);

    bgfx::setVertexBuffer(0, m_vbh);
    bgfx::setIndexBuffer(m_ibh);
    //bgfx::setState(BGFX_STATE_DEFAULT);
    bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A);

    bgfx::submit(0, m_program);
}