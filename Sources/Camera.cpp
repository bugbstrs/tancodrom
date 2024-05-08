#include <GL/glew.h>
#pragma comment (lib, "glew32.lib")

#include "Program.h"
#include "Scene.h"
#include "Camera.h"
#include "InputManager.h"
#include "Tank.h"
#include "Helicopter.h"

Camera::Camera(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation) :
    SceneObject(position, size, rotation),
    m_pov{ FreeCamera }
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

POV Camera::GetCameraPOV()
{
    return m_pov;
}

void Camera::SetTank(SceneObject* tank)
{
    m_tank = tank;
    dynamic_cast<Tank*>(m_tank)->SetCamera(this);
}

void Camera::SetHelicopter(SceneObject* helicopter)
{
    m_helicopter = helicopter;
    dynamic_cast<Helicopter*>(m_helicopter)->SetCamera(this);
}

void Camera::ProcessInput()
{
    if (InputManager::KeyDown(GLFW_KEY_Z))
        m_pov = m_pov == TankCamera ? FreeCamera : TankCamera;
    if (InputManager::KeyDown(GLFW_KEY_X))
        m_pov = m_pov == HelicopterCamera ? FreeCamera : HelicopterCamera;

    if (m_pov == TankCamera)
    {
        glm::quat tankRotationQuat = glm::quat(glm::radians(m_tank->GetRotation()));
        glm::quat cameraOffsetQuat = glm::quat(glm::vec3(glm::radians(3.0f), 0.0f, glm::radians(-7.0f)));
        glm::quat finalOffsetQuat = tankRotationQuat * cameraOffsetQuat;
        glm::vec3 cameraOffset = glm::vec3(finalOffsetQuat * glm::vec4(0.0f, 3.0f, -7.0f, 1.0f));

        m_position = m_tank->GetPosition() + cameraOffset;
        m_rotation = m_tank->GetRotation();

        return;
    }

    if (m_pov == HelicopterCamera)
    {
        glm::quat helicopterRotationQuat = glm::quat(glm::radians(m_helicopter->GetRotation() * -m_helicopter->GetForward()));
        glm::quat cameraOffsetQuat = glm::quat(glm::vec3(glm::radians(5.0f), glm::radians(-1.0f), glm::radians(-10.0f)));
        glm::quat finalOffsetQuat = helicopterRotationQuat * cameraOffsetQuat;
        glm::vec3 cameraOffset = glm::vec3(finalOffsetQuat * glm::vec4(-1.0f, 5.0f, -10.0f, 1.0f));

        m_position = m_helicopter->GetPosition() + cameraOffset;
        m_rotation = m_helicopter->GetRotation() * -m_helicopter->GetForward();
        m_rotation.x += 30;

        return;
    }

    float moveSpeed = (float)(m_cameraSpeedFactor * Scene::GetDeltaTime());
    float rotationSpeed = (float)(m_mouseSensitivity * Scene::GetDeltaTime());

    //move
    if (InputManager::KeyDown(GLFW_KEY_W))
        Move(GetForward() * moveSpeed);
    if (InputManager::KeyDown(GLFW_KEY_A))
        Move(-GetRight() * moveSpeed);
    if (InputManager::KeyDown(GLFW_KEY_S))
        Move(-GetForward() * moveSpeed);
    if (InputManager::KeyDown(GLFW_KEY_D))
        Move(GetRight() * moveSpeed);
    if (InputManager::KeyDown(GLFW_KEY_Q))
        Move(Scene::Up() * moveSpeed);
    if (InputManager::KeyDown(GLFW_KEY_E))
        Move(-Scene::Up() * moveSpeed);

    if (m_position.y > 20)
        m_position.y = 20;
    if (m_position.y < 0)
        m_position.y = 0;

    //rotation
    Rotate(glm::vec3(-InputManager::MouseMoveY() * rotationSpeed,
        -InputManager::MouseMoveX() * rotationSpeed,
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
