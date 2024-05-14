#include "Moon.h"
#include "Scene.h"
#include "InputManager.h"

std::vector<Texture> Moon::textures;
float Moon::rotationSpeed = 5.729f;

Moon::Moon(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation) :
    LightSource(position, size, rotation, "moon")
{
    SetModel("Models/Moon/moon.obj", false, 3);

    textures.emplace_back(Texture("Models/Moon/Moon_Normal.jpg"));
    textures.emplace_back(Texture("Models/Moon/Moon_Diffuse.jpg"));
    textures.emplace_back(Texture("Models/Moon/Moon_Displacement.jpg"));

    color = glm::vec3(0.2f, 0.2f, 0.6f);
    intensity = 12.2f;
    m_initialIntensity = intensity;
}

void Moon::Update()
{
    if (InputManager::KeyHold(GLFW_KEY_P))
    {
        rotationSpeed += 9.0f * Scene::GetDeltaTime();
    }

    if (InputManager::KeyHold(GLFW_KEY_O))
    {
        rotationSpeed -= 9.0f * Scene::GetDeltaTime();
    }

    RotateAround(glm::vec3(0), 110, glm::vec3(0, 0, 1), rotationSpeed * Scene::GetDeltaTime());

    if (m_position.y >= 1)
        Scene::SetPrimaryLight(this);

    if (m_position.y <= -2)
        intensity = 0;
    else
    if (m_position.y <= 2)
        intensity = ((m_position.y + 2) / 4) * m_initialIntensity;
    else
        intensity = m_initialIntensity;
}
