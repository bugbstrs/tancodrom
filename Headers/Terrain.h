#pragma once
#include "SceneObject.h"
class Terrain : public SceneObject
{
public:
	Terrain(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation);

	void Update() override;

private:
};

