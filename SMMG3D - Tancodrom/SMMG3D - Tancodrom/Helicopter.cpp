#include "Helicopter.h"

Helicopter::Helicopter(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation) :
    SceneObject(position, size, rotation)
{
    SetModel("Models/Helicopters/uh60.dae", false);
}

void Helicopter::Update()
{

}
