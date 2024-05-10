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
}

void Moon::Update()
{
    if (InputManager::KeyHold(GLFW_KEY_P))
    {
        Moon::rotationSpeed += 0.1f * Scene::GetDeltaTime();
    }

    if (InputManager::KeyHold(GLFW_KEY_O))
    {
        Moon::rotationSpeed -= 0.1f * Scene::GetDeltaTime();
    }

    RotateAround(-5.f, rotationSpeed * glfwGetTime());
}
