#include <iostream>

#include "Program.h"
#include "Scene.h"

GLuint Program::m_programId;
GLFWwindow* Program::m_window;
unsigned int Program::m_screenWidth;
unsigned int Program::m_screenHeight;

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

        m_window = glfwCreateWindow(m_screenWidth, m_screenHeight, "Tancodrom", glfwGetPrimaryMonitor(), NULL);

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

    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    Initialize();

    Scene::Start();
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

GLuint VaoId, VboId, IboId, ColorBufferId, VertexShaderId, FragmentShaderId, ProgramId;

void Program::Initialize()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);

    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    CreateVBO();
    CreateShaders();
}

void Program::CreateVBO()
{
    // indexurile cubului
    unsigned int Indices[] = {
     0,1,2,
     0,2,3,
     1,5,6,
     1,6,2,
     5,4,7,
     5,7,6,
     4,0,3,
     4,3,7,
     0,5,1,
     0,4,5,
     3,2,6,
     3,6,7
    };

    // varfurile cubului
    GLfloat Vertices[] = {
     0.0f, 0.0f, 1.0f, 1.0f,
     1.0f, 0.0f, 1.0f, 1.0f,
     1.0f, 1.0f, 1.0f, 1.0f,
     0.0f, 1.0f, 1.0f, 1.0f,
     0.0f, 0.0f, 0.0f, 1.0f,
     1.0f, 0.0f, 0.0f, 1.0f,
     1.0f, 1.0f, 0.0f, 1.0f,
     0.0f, 1.0f, 0.0f, 1.0f
    };
    // culorile, ca atribute ale varfurilor
    GLfloat Colors[] = {
     1.0f, 0.0f, 0.0f, 1.0f,
     0.0f, 1.0f, 0.0f, 1.0f,
     0.0f, 0.0f, 1.0f, 1.0f,
     1.0f, 0.0f, 0.0f, 1.0f,
     0.0f, 1.0f, 0.0f, 1.0f,
     0.0f, 0.0f, 1.0f, 1.0f,
     1.0f, 0.0f, 0.0f, 1.0f,
     0.0f, 1.0f, 0.0f, 1.0f
    };

    // se creeaza un buffer nou
    glGenBuffers(1, &VboId);
    // este setat ca buffer curent
    glBindBuffer(GL_ARRAY_BUFFER, VboId);
    // punctele sunt "copiate" in bufferul curent
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

    // se creeaza / se leaga un VAO (Vertex Array Object) - util cand se utilizeaza mai multe VBO
    glGenVertexArrays(1, &VaoId);
    glBindVertexArray(VaoId);

    // se activeaza lucrul cu atribute; atributul 0 = pozitie
    glEnableVertexAttribArray(0);
    //
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

    // un nou buffer, pentru culoare
    glGenBuffers(1, &ColorBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
    // atributul 1 =  culoare
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

    // un nou buffer pentru indexuri
    glGenBuffers(1, &IboId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Program::CreateShaders()
{
    ProgramId = glCreateProgram();

    glUseProgram(ProgramId);
}
