#include "Tank.h"

Tank::Tank(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation) :
    SceneObject(position, size, rotation)
{
    SetModel("Models/Tanks/Tank/IS.obj", false);
}

void Tank::Update()
{

}
