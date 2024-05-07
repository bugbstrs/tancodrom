#include "Moon.h"
#include "Scene.h"

Moon::Moon(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation) :
    LightSource(position, size, rotation)
{
    SetModel("Models/Moon/Moon.obj", false);
}

void Moon::Update()
{
    RotateAround(35.f, 0.2f * glfwGetTime());
}
