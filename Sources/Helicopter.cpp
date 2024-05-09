#include "Helicopter.h"
#include "InputManager.h"

std::vector<Texture> Helicopter::textures;

Helicopter::Helicopter(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation) :
    SceneObject(position, size, rotation),
    m_camera{ nullptr }
{
    SetModel("Models/Helicopters/uh60.dae", false, 2);

    textures.emplace_back(Texture("Models/Helicopter/fuselage"));
    textures.emplace_back(Texture("Models/Helicopter/land"));
    textures.emplace_back(Texture("Models/Helicopter/pal"));
    textures.emplace_back(Texture("Models/Helicopter/panel"));
    textures.emplace_back(Texture("Models/Helicopter/plt"));
}

void Helicopter::Update()
{
    if (m_camera == nullptr || m_camera->GetCameraPOV() != HelicopterCamera)
        return;

    float moveSpeed = (float)(m_moveSpeed * Scene::GetDeltaTime());
    float rotationSpeed = (float)(m_rotationSpeed * Scene::GetDeltaTime());

    if (InputManager::KeyHold(GLFW_KEY_W))
        Move(-GetUp() * moveSpeed);
    if (InputManager::KeyHold(GLFW_KEY_A))
        Move(GetRight() * moveSpeed);
    if (InputManager::KeyHold(GLFW_KEY_S))
        Move(GetUp() * moveSpeed);
    if (InputManager::KeyHold(GLFW_KEY_D))
        Move(-GetRight() * moveSpeed);
    if (InputManager::KeyHold(GLFW_KEY_Q))
        Move(-Scene::Up() * moveSpeed);
    if (InputManager::KeyHold(GLFW_KEY_E))
        Move(Scene::Up() * moveSpeed);
}

void Helicopter::SetCamera(Camera* camera)
{
    m_camera = camera;
}
