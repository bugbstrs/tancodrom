#include <GL/glew.h>
#pragma comment (lib, "glew32.lib")

#include "Program.h"
#include "Scene.h"
#include "Camera.h"
#include "InputManager.h"

Camera::Camera(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation) :
    SceneObject(position, size, rotation)
{
    m_width = glfwGetVideoMode(glfwGetPrimaryMonitor())->width;
    m_height = glfwGetVideoMode(glfwGetPrimaryMonitor())->height;

    m_FOV = 70.0f;
}

void Camera::Update()
{
    Reshape();

    ProcessInput();
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
    float velocity = (float)(m_cameraSpeedFactor * Scene::GetDeltaTime());

    //move
    if (InputManager::KeyDown(GLFW_KEY_W))
        Move(GetForward() * velocity);
    if (InputManager::KeyDown(GLFW_KEY_A))
        Move(-GetRight() * velocity);
    if (InputManager::KeyDown(GLFW_KEY_S))
        Move(-GetForward() * velocity);
    if (InputManager::KeyDown(GLFW_KEY_D))
        Move(GetRight() * velocity);

    //rotation
    Rotate(glm::vec3(-InputManager::MouseMoveY() * m_mouseSensitivity,
        -InputManager::MouseMoveX() * m_mouseSensitivity,
        0));

    if (m_rotation.x > 89.0f)
        m_rotation.x = 89.0f;
    if (m_rotation.x < -89.0f)
        m_rotation.x = -89.0f;

    //zoom
    m_FOV -= InputManager::ScrollY();
    if (m_FOV <= 45.0f)
        m_FOV = 45.0f;
    if (m_FOV >= 90.0f)
        m_FOV = 90.0f;
}

void Camera::Reshape()
{
    m_width = Program::GetScreenWidth();
    m_height = Program::GetScreenHeight();

    glViewport(0, 0, m_width, m_height);
}
