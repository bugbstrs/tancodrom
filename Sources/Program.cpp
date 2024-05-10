#include <iostream>

#include "Program.h"
#include "Scene.h"
#include "InputManager.h"

GLuint Program::m_programId;
GLFWwindow* Program::m_window;
unsigned int Program::m_screenWidth;
unsigned int Program::m_screenHeight;
Shader Program::m_shadowMappingShader;
Shader Program::m_shadowMappingDepthShader;
Shader Program::m_skyboxShader;

void Program::Run()
{
    // glfw: initialize and configure
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    if (mode != NULL)
    {
        m_screenWidth = mode->width;
        m_screenHeight = mode->height;

        m_window = glfwCreateWindow(m_screenWidth, m_screenHeight, "Tancodrom", NULL, NULL);

        if (m_window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            exit(-1);
        }
    }
    else
    {
        std::cout << "Failed to get video mode" << std::endl;
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(m_window);
    glfwSetFramebufferSizeCallback(m_window, FramebufferSizeCallback);
    glfwSetCursorPosCallback(m_window, InputManager::MouseCallback);
    glfwSetScrollCallback(m_window, InputManager::ScrollCallback);

    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    Initialize();

    Scene::Run();
}

GLuint Program::GetProgramID()
{
    return m_programId;
}

GLFWwindow* Program::GetWindow()
{
    return m_window;
}

unsigned int Program::GetScreenWidth()
{
    return m_screenWidth;
}

unsigned int Program::GetScreenHeight()
{
    return m_screenHeight;
}

void Program::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    if (width == 0 || height == 0)
        return;
    m_screenWidth = width;
    m_screenHeight = height;
}

void Program::Initialize()
{
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);

    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    CreateShaders();
}

void Program::CreateShaders()
{
    m_shadowMappingShader.Initialize("ShadowMapping");
    m_shadowMappingDepthShader.Initialize("ShadowMappingDepth");
    m_skyboxShader.Initialize("skybox");
}
