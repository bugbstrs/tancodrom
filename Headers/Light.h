#pragma once
#include "LightSource.h"

class Light : public LightSource
{
public:
	Light(const glm::vec3& position, const glm::vec3& colorr, float intensityy, float life);

	void Update() override;

private:
	float m_initialIntensity;
	float m_initialLifeTime;
	float m_lifeTime;
};