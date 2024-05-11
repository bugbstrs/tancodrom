#include "Tank.h"
#include "Scene.h"
#include "InputManager.h"
#include "Projectile.h"

Model* Tank::tankModel = nullptr;

Tank::Tank(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation) :
    SceneObject(position, size, rotation),
    m_camera{nullptr},
    m_isMoving{true}
{
    if (!tankModel)
    {
        tankModel = new Model("Models/Tanks/Tank/IS.obj", false, 2);
    }
    m_model = tankModel;
    m_collider = new Collider(glm::vec3(0), 3, "Tank", m_position, m_rotation);
}

void Tank::Update()
{
    m_isMoving = true;

    for (auto collision : m_collider->GetCollisions())
    {
        if (collision.first == "Tank")
            m_isMoving = false;
    }

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

void Tank::TakeDamage(float damage)
{
    m_health -= damage;
    if (m_health <= 0)
        Scene::Destroy(this);
}

void Tank::SetCamera(Camera* camera)
{
    m_camera = camera;
}
