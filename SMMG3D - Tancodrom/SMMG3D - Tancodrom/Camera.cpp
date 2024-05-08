#include <GL/glew.h>
#pragma comment (lib, "glew32.lib")

#include "Program.h"
#include "Scene.h"
#include "Camera.h"
#include "InputManager.h"

Camera::Camera(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation) :
    SceneObject(position, size, rotation),
    m_isFirstPerson(false)
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

SceneObject* Camera::GetTank() const
{
    return m_tank;
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

void Camera::SetTank(SceneObject* tank)
{
    m_tank = tank;
}

void Camera::ProcessInput()
{
    SceneObject* ptr;
    if (InputManager::KeyDown(GLFW_KEY_E))
        m_isFirstPerson = !m_isFirstPerson;

    if (m_isFirstPerson) {
        glm::quat tankRotationQuat = glm::quat(glm::radians(m_tank->GetRotation()));
        glm::quat cameraOffsetQuat = glm::quat(glm::vec3(glm::radians(3.0f), 0.0f, glm::radians(-7.0f)));
        glm::quat finalOffsetQuat = tankRotationQuat * cameraOffsetQuat;
        glm::vec3 cameraOffset = glm::vec3(finalOffsetQuat * glm::vec4(0.0f, 3.0f, -7.0f, 1.0f));

        m_position = m_tank->GetPosition() + cameraOffset;
        m_rotation = m_tank->GetRotation();
        ptr = m_tank;
    }
    else ptr = this;
    float velocity = (float)(m_cameraSpeedFactor * Scene::GetDeltaTime());

    //move
    if (InputManager::KeyDown(GLFW_KEY_W))
        ptr->Move(GetForward() * velocity);
    if (InputManager::KeyDown(GLFW_KEY_A))
        ptr->Move(-GetRight() * velocity);
    if (InputManager::KeyDown(GLFW_KEY_S))
        ptr->Move(-GetForward() * velocity);
    if (InputManager::KeyDown(GLFW_KEY_D))
        ptr->Move(GetRight() * velocity);

    //rotation
    if (ptr == this)
        ptr->Rotate(glm::vec3(-InputManager::MouseMoveY() * m_mouseSensitivity * Scene::GetDeltaTime(),
            -InputManager::MouseMoveX() * m_mouseSensitivity * Scene::GetDeltaTime(),
            0));
    else
        ptr->Rotate(glm::vec3(0, -InputManager::MouseMoveX() * m_mouseSensitivity * Scene::GetDeltaTime(), 0));



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
