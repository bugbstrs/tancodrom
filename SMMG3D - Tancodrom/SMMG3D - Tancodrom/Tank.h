#pragma once
#include "SceneObject.h"

class Tank : public SceneObject
{
public:
	Tank(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation);
	
	void Update() override;

private:
	bool isMoving;
};

