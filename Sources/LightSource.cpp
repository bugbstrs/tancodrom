#include "LightSource.h"
#include "Scene.h"

LightSource::LightSource(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation) :
    SceneObject(position, size, rotation)
{}

glm::mat4 LightSource::GetLightSpaceMatrix()
{
    float near_plane = 1.0f, far_plane = 7.5f;
    glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);

    glm::mat4 lightView = glm::lookAt(m_position, GetForward(), Scene::Up());

    glm::mat4 lightSpaceMatrix = lightProjection * lightView;

    return lightSpaceMatrix;
}

void LightSource::Update()
{

}
