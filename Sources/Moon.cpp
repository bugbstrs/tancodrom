#include "Moon.h"
#include "Scene.h"
#include "InputManager.h"

std::vector<Texture> Moon::textures;
float Moon::rotationSpeed = 0.1f;

Moon::Moon(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation) :
    LightSource(position, size, rotation)
{
    SetModel("Models/Moon/moon.obj", false, 3);

    textures.emplace_back(Texture("Models/Moon/Moon_Normal.jpg"));
    textures.emplace_back(Texture("Models/Moon/Moon_Diffuse.jpg"));
    textures.emplace_back(Texture("Models/Moon/Moon_Displacement.jpg"));

    color = glm::vec3(0.1f, 0.1f, 0.4f);
    intensity = 10.0f;
}

void Moon::Update()
{
    if (InputManager::KeyHold(GLFW_KEY_P))
    {
        rotationSpeed += 0.1f * Scene::GetDeltaTime();
    }

    if (InputManager::KeyHold(GLFW_KEY_O))
    {
        rotationSpeed -= 0.1f * Scene::GetDeltaTime();
    }

    RotateAround(glm::vec3(0), 90, glm::vec3(0, 0, 1), rotationSpeed * Scene::GetDeltaTime());

    if (m_position.y >= 1)
        Scene::SetPrimaryLight(this);
}
