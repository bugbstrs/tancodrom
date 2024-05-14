#include "Building.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "Light.h"

Model* Building::buildingModel = nullptr;
Model* Building::damagedModel = nullptr;

Building::Building(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation):
	SceneObject(position, size, rotation, "building")
{
	if (!buildingModel)
	{
		buildingModel = new Model("Models/BuildingNormal/buildingnormal.obj", false, 13);
	}

	if (!damagedModel)
	{
		damagedModel = new Model("Models/BuildingDamaged/buildingdamaged.obj", false, 13);
	}

	m_model = new Model(buildingModel);
	m_collider = new Collider(glm::vec3(0), 3, "Building", m_position, m_rotation);
}

void Building::Update()
{
}

void Building::TakeDamage(float damage)
{
	m_health -= damage;
	if (m_health <= 0)
	{
		Scene::AddLight(new Light(m_position + GetUp() * 1.5f, glm::vec3(1, 0.4, 0), 10, 1.7));
		Scene::Destroy(this);
		SoundManager::PlayTankHit();
	}
	else
	{
		m_position.y = -0.85;
		m_collider = 0;
		m_model = damagedModel;
		SoundManager::PlayTankExplosion();
	}
}
