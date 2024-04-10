
#include <stdlib.h> // necesare pentru citirea shader-elor
#include <stdio.h>
#include <iostream>

#include "Camera.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#pragma comment (lib, "glfw3dll.lib")
#pragma comment (lib, "glew32.lib")
#pragma comment (lib, "OpenGL32.lib")

// settings
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 1000;

float radius = 10.0f;
float camX = 10.f;
float camZ = 10.f;
double oldMouseX = 0.f;
double oldMouseY = 0.f;

void increaseCamX() {
    camX += 0.1f;
}

void increaseCamZ() {
    camZ += 0.1f;
}

void decreaseCamX() {
    camX -= 0.1f;
}

void decreaseCamZ() {
    camZ -= 0.1f;
}

GLuint VaoId, VboId, IboId, ColorBufferId, VertexShaderId, FragmentShaderId, ProgramId;
GLuint ProjMatrixLocation, ViewMatrixLocation, WorldMatrixLocation;

Camera* pCamera = nullptr;

// Shader-ul de varfuri / Vertex shader (este privit ca un sir de caractere)
const GLchar* VertexShader =
{
   "#version 400\n"\
   "layout(location=0) in vec4 in_Position;\n"\
   "layout(location=1) in vec4 in_Color;\n"\
   "out vec4 ex_Color;\n"\
   "uniform mat4 ProjMatrix;\n"\
   "uniform mat4 ViewMatrix;\n"\
   "uniform mat4 WorldMatrix;\n"\
   "void main()\n"\
   "{\n"\
   "  gl_Position = ProjMatrix * ViewMatrix * WorldMatrix * in_Position;\n"\
   "  ex_Color = in_Color;\n"\
   "}\n"
};
// Shader-ul de fragment / Fragment shader (este privit ca un sir de caractere)
const GLchar* FragmentShader =
{
   "#version 400\n"\
   "in vec4 ex_Color;\n"\
   "out vec4 out_Color;\n"\
   "void main()\n"\
   "{\n"\
   "  out_Color = ex_Color;\n"\
   "}\n"
};

void CreateVBO()
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
void DestroyVBO()
{
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &ColorBufferId);
    glDeleteBuffers(1, &VboId);
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VaoId);
}
void CreateShaders()
{
    VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
    glCompileShader(VertexShaderId);

    FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
    glCompileShader(FragmentShaderId);

    ProgramId = glCreateProgram();
    glAttachShader(ProgramId, VertexShaderId);
    glAttachShader(ProgramId, FragmentShaderId);
    glLinkProgram(ProgramId);

    GLint Success = 0;
    GLchar ErrorLog[1024] = { 0 };

    glGetProgramiv(ProgramId, GL_LINK_STATUS, &Success);
    if (Success == 0) {
        glGetProgramInfoLog(ProgramId, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
        exit(1);
    }

    glValidateProgram(ProgramId);
    glGetProgramiv(ProgramId, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(ProgramId, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        exit(1);
    }

    glUseProgram(ProgramId);

    ProjMatrixLocation = glGetUniformLocation(ProgramId, "ProjMatrix");
    ViewMatrixLocation = glGetUniformLocation(ProgramId, "ViewMatrix");
    WorldMatrixLocation = glGetUniformLocation(ProgramId, "WorldMatrix");

}
void DestroyShaders()
{
    glUseProgram(0);

    glDetachShader(ProgramId, VertexShaderId);
    glDetachShader(ProgramId, FragmentShaderId);

    glDeleteShader(FragmentShaderId);
    glDeleteShader(VertexShaderId);

    glDeleteProgram(ProgramId);
}
void Initialize()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // culoarea de fond a ecranului
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);

    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    CreateVBO();
    CreateShaders();

    // Create camera
    pCamera = new Camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.5, 0.5, 10));
}

void RenderCube()
{
    glBindVertexArray(VaoId);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VboId);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IboId);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
}

void RenderFrame()
{
    glm::vec3 cubePositions[] = {
     glm::vec3(0.0f,  0.0f,   0.0f),
     glm::vec3(-5.0f,  5.0f,  5.0f),
     glm::vec3(-5.0f, -5.0f,  5.0f),
     glm::vec3(5.0f, -5.0f,  5.0f),
     glm::vec3(5.0f,  5.0f,  5.0f),
     glm::vec3(-5.0f,  5.0f, -5.0f),
     glm::vec3(-5.0f, -5.0f, -5.0f),
     glm::vec3(5.0f, -5.0f, -5.0f),
     glm::vec3(5.0f,  5.0f, -5.0f),
    };

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(ProgramId);

    glm::mat4 projection = pCamera->GetProjectionMatrix();
    glUniformMatrix4fv(ProjMatrixLocation, 1, GL_FALSE, glm::value_ptr(projection));

    //glm::mat4 view = pCamera->GetViewMatrix();
    //glUniformMatrix4fv(ViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(view));

    glm::mat4 view;
    
    view = pCamera->GetViewMatrix();
    glUniformMatrix4fv(ViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(view));

    for (unsigned int i = 0; i < sizeof(cubePositions) / sizeof(cubePositions[0]); i++) {
        // calculate the model matrix for each object and pass it to shader before drawing
        glm::mat4 worldTransf = glm::translate(glm::mat4(1.0), cubePositions[i]);
        glUniformMatrix4fv(WorldMatrixLocation, 1, GL_FALSE, glm::value_ptr(worldTransf));

        RenderCube();
    }
}

void Cleanup()
{
    DestroyShaders();
    DestroyVBO();

    delete pCamera;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void ProcessInput(GLFWwindow* window);

// timing
double deltaTime = 0.0f;    // time between current frame and last frame
double lastFrame = 0.0f;

int main()
{
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Lab 5", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glewInit();

    Initialize();

    // render loop
    while (!glfwWindowShouldClose(window)) {
        // per-frame time logic
        double currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // render
        RenderFrame();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        ProcessInput(window);
        
        glfwPollEvents();
    }

    Cleanup();

    // glfw: terminate, clearing all previously allocated GLFW resources
    glfwTerminate();
    return 0;
}

void ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        //pCamera->increaseFOV();
        pCamera->ProcessInput(ECameraMovementType::FORWARD, deltaTime);
        RenderFrame();
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        //pCamera->decreaseFOV();
        pCamera->ProcessInput(ECameraMovementType::BACKWARD, deltaTime);
        RenderFrame();
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        pCamera->ProcessInput(ECameraMovementType::LEFT, deltaTime);
        RenderFrame();
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        pCamera->ProcessInput(ECameraMovementType::RIGHT, deltaTime);
        RenderFrame();
    }

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        pCamera->ProcessInput(ECameraMovementType::UP, deltaTime);
        RenderFrame();
    }

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        pCamera->ProcessInput(ECameraMovementType::DOWN, deltaTime);
        RenderFrame();
    }


    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        pCamera->Reset(width, height);
        RenderFrame();
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    pCamera->Reshape(width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    double newIncreaseX = xpos - oldMouseX;
    double newIncreaseY = -1 * (ypos - oldMouseY);
    pCamera->ProcessMouseMovement((int)newIncreaseX, (int)newIncreaseY, deltaTime);
    RenderFrame();
    oldMouseX = xpos;
    oldMouseY = ypos;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yOffset)
{
    //if (yOffset > 0)
    //    pCamera->increaseFov();
    //else
    //    pCamera->decreaseFov();
    RenderFrame();
}
//-----------------------------------------------------------------