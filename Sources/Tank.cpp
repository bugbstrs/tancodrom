#include "Tank.h"
#include "Scene.h"
#include "InputManager.h"
#include "Projectile.h"

Tank::Tank(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation) :
    SceneObject(position, size, rotation),
    m_isMoving(true),
    m_camera{nullptr}
{
    SetModel("Models/Tanks/Tank/IS.obj", false, 2);
}

void Tank::Update()
{
    if (m_camera == nullptr || m_camera->GetCameraPOV() != TankCamera)
    {
        glm::vec3 forward = GetForward();
        float movementSpeed = 0.2f * Scene::GetDeltaTime();
    
        if (m_isMoving)
        {
            Move(forward * movementSpeed);
        }

        return;
    }

    float moveSpeed = m_moveSpeed * Scene::GetDeltaTime();
    float rotationSpeed = m_rotationSpeed * Scene::GetDeltaTime();

    if (InputManager::KeyHold(GLFW_KEY_W))
        Move(GetForward() * moveSpeed);
    if (InputManager::KeyHold(GLFW_KEY_A))
        Rotate(glm::vec3(0, rotationSpeed, 0));
    if (InputManager::KeyHold(GLFW_KEY_S))
        Move(-GetForward() * moveSpeed);
    if (InputManager::KeyHold(GLFW_KEY_D))
        Rotate(glm::vec3(0, -rotationSpeed, 0));

    if (InputManager::PrimaryClick())
    {
        Scene::Instantiate(new Projectile(m_position, glm::vec3(1), m_rotation));
    }
}

void Tank::SetCamera(Camera* camera)
{
    m_camera = camera;
}
