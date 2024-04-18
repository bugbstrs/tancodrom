#include <GL/glew.h>
#pragma comment (lib, "glew32.lib")

#include "Program.h"
#include "Scene.h"
#include "Camera.h"
#include "InputManager.h"

Camera::Camera(const glm::vec3& position, const glm::vec3 rotation)
{
    SetPosition(position);

    m_width = glfwGetVideoMode(glfwGetPrimaryMonitor())->width;
    m_height = glfwGetVideoMode(glfwGetPrimaryMonitor())->height;

    m_lastX = m_width / 2.0f;
    m_lastY = m_height / 2.0f;
    m_bFirstMouseMove = true;

    m_FOV = 70.0f;

    ProjMatrixLocation = glGetUniformLocation(Program::GetProgramID(), "ProjMatrix");
    ViewMatrixLocation = glGetUniformLocation(Program::GetProgramID(), "ViewMatrix");
}

void Camera::Update()
{
    Reshape();

    ProcessInput();

    glm::mat4 projection = GetProjectionMatrix();
    glUniformMatrix4fv(ProjMatrixLocation, 1, GL_FALSE, glm::value_ptr(projection));

    glm::mat4 view = GetViewMatrix();
    glUniformMatrix4fv(ViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(view));
}

const glm::mat4 Camera::GetViewMatrix() const
{
    return glm::lookAt(GetPosition(), GetPosition() + GetForward(), GetUp());
}

const glm::mat4 Camera::GetProjectionMatrix() const
{
    float aspectRatio = ((float)(m_width)) / m_height;

    return glm::perspective(glm::radians(m_FOV), aspectRatio, m_zNEAR, m_zFAR);
}

void Camera::ProcessInput()
{
    float velocity = (float)(cameraSpeedFactor * Scene::GetDeltaTime());

    if (InputManager::KeyDown(GLFW_KEY_W))
        Move(Scene::Forward() * velocity);
    if (InputManager::KeyDown(GLFW_KEY_A))
        Move(-Scene::Right() * velocity);
    if (InputManager::KeyDown(GLFW_KEY_S))
        Move(-Scene::Forward() * velocity);
    if (InputManager::KeyDown(GLFW_KEY_D))
        Move(Scene::Right() * velocity);
}

void Camera::MouseControl(float xPos, float yPos)
{
    //if (m_bFirstMouseMove)
    //{
    //    m_lastX = xPos;
    //    m_lastY = yPos;
    //    m_bFirstMouseMove = false;
    //}

    //float xChange = xPos - m_lastX;
    //float yChange = m_lastY - yPos;
    //m_lastX = xPos;
    //m_lastY = yPos;

    //if (fabs(xChange) <= 1e-6 && fabs(yChange) <= 1e-6)
    //{
    //    return;
    //}
    //xChange *= mouseSensitivity;
    //yChange *= mouseSensitivity;

    //ProcessMouseMovement(xChange, yChange);
}

void Camera::ProcessMouseScroll(float yOffset)
{
    //if (m_FOV >= 1.0f && m_FOV <= 90.0f)
    //{
    //    m_FOV -= yOffset;
    //}
    //if (m_FOV <= 1.0f)
    //    m_FOV = 1.0f;
    //if (m_FOV >= 90.0f)
    //    m_FOV = 90.0f;
}

void Camera::ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch)
{
    //m_yaw += xOffset;
    //m_pitch += yOffset;

    //if (constrainPitch)
    //{
    //    if (m_pitch > 89.0f)
    //        m_pitch = 89.0f;
    //    if (m_pitch < -89.0f)
    //        m_pitch = -89.0f;
    //}
}

void Camera::Reshape()
{
    m_width = Program::GetScreenWidth();
    m_height = Program::GetScreenHeight();

    glViewport(0, 0, m_width, m_height);
}
