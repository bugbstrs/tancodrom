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
    m_pov{ FreeCamera },
    m_tank{ nullptr },
    m_helicopter{ nullptr }
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
    if (m_tank)
        dynamic_cast<Tank*>(m_tank)->SetCamera(nullptr);
    m_tank = tank;
    m_pov = TankCamera;
    dynamic_cast<Tank*>(m_tank)->SetCamera(this);
}

void Camera::SetHelicopter(SceneObject* helicopter)
{
    if(m_helicopter)
        dynamic_cast<Helicopter*>(m_helicopter)->SetCamera(nullptr);
    m_helicopter = helicopter;
    m_pov = HelicopterCamera;
    dynamic_cast<Helicopter*>(m_helicopter)->SetCamera(this);
}

void Camera::ProcessInput()
{
    if (InputManager::KeyDown(GLFW_KEY_X))
        m_pov = FreeCamera;

    if (m_pov == TankCamera)
    {
        glm::quat tankRotationQuat = glm::quat(glm::radians(m_tank->GetRotation()));
        glm::quat cameraOffsetQuat = glm::quat(glm::vec3(glm::radians(6.0f), glm::radians(-1.0f), glm::radians(-8.0f)));
        glm::quat finalOffsetQuat = tankRotationQuat * cameraOffsetQuat;
        glm::vec3 cameraOffset = glm::vec3(finalOffsetQuat * glm::vec4(-1.0f, 6.0f, -8.0f, 1.0f));

        m_position = m_tank->GetPosition() + cameraOffset;
        m_rotation = m_tank->GetRotation();

        m_rotation.x += 30;

        return;
    }

    if (m_pov == HelicopterCamera)
    {
        glm::quat helicopterRotationQuat = glm::quat(glm::radians(m_helicopter->GetRotation()));
        glm::quat cameraOffsetQuat = glm::quat(glm::vec3(glm::radians(6.0f), glm::radians(-1.0f), glm::radians(-8.0f)));
        glm::quat finalOffsetQuat = helicopterRotationQuat * cameraOffsetQuat;
        glm::vec3 cameraOffset = glm::vec3(finalOffsetQuat * glm::vec4(-1.0f, 6.0f, -8.0f, 1.0f));
        //glm::vec3 cameraOffset = glm::vec3(finalOffsetQuat * glm::vec4(-9.0f, 5.0f, -5.0f, 1.0f));

        m_position = m_helicopter->GetPosition() + cameraOffset;
        m_rotation = m_helicopter->GetRotation();

        m_rotation.x += 30;

        return;
    }

    if (InputManager::PrimaryClick())
    {
        glm::vec3 rayDirection = GetForward();

        std::pair<std::string, SceneObject*> collision = Scene::RayCast(m_position, rayDirection);

        if (collision.second != nullptr)
        {
            std::string objectType = collision.first;
            SceneObject* objectHit = collision.second;
            if (objectType == "Tank")
            {
                SetTank(objectHit);
            }
            if (objectType == "Helicopter")
            {
                SetHelicopter(objectHit);
            }
        }
    }

    float moveSpeed = (float)(m_cameraSpeedFactor * Scene::GetDeltaTime());
    float rotationSpeed = (float)(m_mouseSensitivity * Scene::GetDeltaTime());

    //move
    if (InputManager::KeyHold(GLFW_KEY_W))
        Move(GetForward() * moveSpeed);
    if (InputManager::KeyHold(GLFW_KEY_A))
        Move(-GetRight() * moveSpeed);
    if (InputManager::KeyHold(GLFW_KEY_S))
        Move(-GetForward() * moveSpeed);
    if (InputManager::KeyHold(GLFW_KEY_D))
        Move(GetRight() * moveSpeed);
    if (InputManager::KeyHold(GLFW_KEY_Q))
        Move(-Scene::Up() * moveSpeed);
    if (InputManager::KeyHold(GLFW_KEY_E))
        Move(Scene::Up() * moveSpeed);

    if (m_position.y > 30)
        m_position.y = 30;
    if (m_position.y < 0.5)
        m_position.y = 0.5;

    //rotation
    Rotate(glm::vec3(-InputManager::MouseMoveY() * rotationSpeed, -InputManager::MouseMoveX() * rotationSpeed, 0));

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
