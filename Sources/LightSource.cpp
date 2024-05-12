#include "LightSource.h"
#include "Scene.h"

LightSource::LightSource(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation) :
    SceneObject(position, size, rotation)
{
    Rotate(glm::vec3(180, 180, 180));
}

glm::mat4 LightSource::GetLightProjection()
{
    float near_plane = 1.0f, far_plane = 250.f;
    return glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, near_plane, far_plane);
}

glm::mat4 LightSource::GetLightView()
{
    return glm::lookAt(m_position, GetForward(), Scene::Up());
}

glm::mat4 LightSource::GetLightSpaceMatrix()
{
    float near_plane = 1.0f, far_plane = 250.f;
    glm::mat4 lightProjection = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, near_plane, far_plane);

    glm::mat4 lightView = glm::lookAt(m_position, GetForward(), Scene::Up());

    glm::mat4 lightSpaceMatrix = lightProjection * lightView;

    return lightSpaceMatrix;
}

void LightSource::Update()
{

}
