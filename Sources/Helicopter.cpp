#include "Helicopter.h"
#include "InputManager.h"

std::vector<Texture> Helicopter::textures;
float const Helicopter::maxTilt = 30;
float const Helicopter::constTiltSpeed = 15;

Helicopter::Helicopter(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation) :
    SceneObject(position, size, rotation),
    m_camera{ nullptr }
{
    SetModel("Models/Helicopters/uh60.dae", false, 2);
    m_collider = new Collider(glm::vec3(0), 7, "Helicopter", m_position, m_rotation);

    textures.emplace_back(Texture("Models/Helicopter/fuselage"));
    textures.emplace_back(Texture("Models/Helicopter/land"));
    textures.emplace_back(Texture("Models/Helicopter/pal"));
    textures.emplace_back(Texture("Models/Helicopter/panel"));
    textures.emplace_back(Texture("Models/Helicopter/plt"));
}

void Helicopter::Update()
{
    m_model->SetMeshTransform(10, glm::rotate(m_model->GetMeshTransform(10), 15 * Scene::GetDeltaTime(), glm::vec3(0, 0, 1)));

    float tiltSpeed = constTiltSpeed * Scene::GetDeltaTime();

    if (pitch != 0)
    {
        if (pitch > 0)
            pitch = (pitch - tiltSpeed < 0) ? 0 : pitch - tiltSpeed;
        else
            pitch = (pitch + tiltSpeed > 0) ? 0 : pitch + tiltSpeed;
    }
    if (yaw != 0)
    {
        if (yaw > 0)
            yaw = (yaw - tiltSpeed < 0) ? 0 : yaw - tiltSpeed;
        else
            yaw = (yaw + tiltSpeed > 0) ? 0 : yaw + tiltSpeed;
    }

    if (m_camera == nullptr || m_camera->GetCameraPOV() != HelicopterCamera)
        return;

    float moveSpeed = m_moveSpeed * Scene::GetDeltaTime();
    float rotationSpeed = m_rotationSpeed * Scene::GetDeltaTime();

    if (InputManager::KeyHold(GLFW_KEY_W))
    {
        pitch = (pitch - tiltSpeed * 2 < -maxTilt) ? -maxTilt : pitch - tiltSpeed * 2;
        Move(-GetUp() * moveSpeed);
    }
    if (InputManager::KeyHold(GLFW_KEY_A))
    {
        yaw = (yaw - tiltSpeed * 2 < -maxTilt) ? -maxTilt : yaw - tiltSpeed * 2;
        Move(GetRight() * moveSpeed);
    }
    if (InputManager::KeyHold(GLFW_KEY_S))
    {
        pitch = (pitch + tiltSpeed * 2 > maxTilt) ? maxTilt : pitch + tiltSpeed * 2;
        Move(GetUp() * moveSpeed);
    }
    if (InputManager::KeyHold(GLFW_KEY_D))
    {
        yaw = (yaw + tiltSpeed * 2 > maxTilt) ? maxTilt : yaw + tiltSpeed * 2;
        Move(-GetRight() * moveSpeed);
    }
    if (InputManager::KeyHold(GLFW_KEY_Q))
    {
        Move(-Scene::Up() * moveSpeed);
    }
    if (InputManager::KeyHold(GLFW_KEY_E))
    {
        Move(Scene::Up() * moveSpeed);
    }

    if (m_position.y > 35)
        m_position.y = 35;
    if (m_position.y < 0.5)
        m_position.y = 0.5;

    Rotate(glm::vec3(0, 0, -InputManager::MouseMoveX() * rotationSpeed));
}

void Helicopter::SetCamera(Camera* camera)
{
    m_camera = camera;
}

void Helicopter::Render(Shader& shader)
{
    glm::mat4 modelTransform(1.0f);
    modelTransform = glm::translate(modelTransform, m_position);
    modelTransform = glm::rotate(modelTransform, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    modelTransform = glm::rotate(modelTransform, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelTransform = glm::rotate(modelTransform, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    modelTransform = glm::rotate(modelTransform, glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));
    modelTransform = glm::rotate(modelTransform, glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
    modelTransform = glm::scale(modelTransform, m_size);
    m_model->RenderModel(shader, modelTransform);
}
