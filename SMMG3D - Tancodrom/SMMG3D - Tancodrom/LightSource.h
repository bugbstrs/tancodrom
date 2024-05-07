#pragma once
#include "SceneObject.h"

class LightSource : public SceneObject
{
public:
    LightSource(const glm::vec3& position, const glm::vec3& size, const glm::vec3& rotation);

    glm::mat4 GetLightSpaceMatrix();

    void Update() override;
};


