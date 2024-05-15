#pragma once
#include "LightSource.h"

class Sun : public LightSource
{
public:
	Sun(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation);

	void Update() override;

	static std::vector<Texture> textures;

	float rotationSpeed;

	const float initialSpeed = 0.1f;
private:
	float m_initialIntensity;
};

