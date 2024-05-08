#include "Moon.h"
#include "Scene.h"

std::vector<Texture> Moon::textures;

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
    RotateAround(35.f, 0.2f * glfwGetTime());
}
