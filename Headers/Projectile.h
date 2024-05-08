#pragma once
#include "SceneObject.h"

class Projectile : public SceneObject
{
public:
	Projectile(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation);

	void Update() override;

private:
	float m_lifeTime = 10.0f;

	const float m_moveSpeed = 0.5f;
};

