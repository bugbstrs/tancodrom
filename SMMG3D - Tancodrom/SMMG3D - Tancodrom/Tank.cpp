#include "Tank.h"
#include "Scene.h"

Tank::Tank(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation) :
    SceneObject(position, size, rotation), isMoving(true)
{
    SetModel("Models/Tanks/Tank/IS.obj", false, 2);
}

void Tank::Update()
{
    glm::vec3 forward = GetForward();
    float movementSpeed = 0.2f * Scene::GetDeltaTime();
    
    if (isMoving)
    {
        Move(forward * movementSpeed);
    }
}
