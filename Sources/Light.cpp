#include "Light.h"
#include "Scene.h"

Light::Light(const glm::vec3& position, const glm::vec3& colorr, float intensityy, float life) :
	LightSource(position, glm::vec3(1), glm::vec3(1), "light"),
	m_lifeTime{life},
	m_initialIntensity{intensityy},
	m_initialLifeTime{life}
{
	color = colorr;
	intensity = intensityy;
}

void Light::Update()
{
	m_lifeTime -= Scene::GetDeltaTime();
	if (m_lifeTime <= 0)
	{
		Scene::DestroyLight(this);
		return;
	}

	intensity = m_initialIntensity / (m_initialLifeTime / m_lifeTime);
}
