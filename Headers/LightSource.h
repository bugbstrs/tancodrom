#pragma once
#include "SceneObject.h"

class LightSource : public SceneObject
{
public:
    LightSource(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation, std::string name);

    glm::mat4 GetLightSpaceMatrix();
    glm::mat4 GetLightProjection();
    glm::mat4 GetLightView();

    glm::vec3 color;
    float intensity;

    void Update() override;
};
