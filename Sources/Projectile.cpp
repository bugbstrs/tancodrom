#include "Projectile.h"
#include "Scene.h"
#include "Tank.h"
#include "Light.h"
#include <Building.h>
#include <Wall.h>

Model* Projectile::projectileModel = nullptr;

Projectile::Projectile(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation) :
	SceneObject(position, size, rotation, "projectile")
{
	m_model = projectileModel;
	m_collider = new Collider(glm::vec3(0, 2, 6), 0.5, "Projectile", m_position, m_rotation);
}

void Projectile::InitializeModel()
{
	projectileModel = new Model("Models/Projectile/projectile.obj", false, 2);
}

void Projectile::Update()
{
	m_lifeTime -= Scene::GetDeltaTime();
	if (m_lifeTime <= 0)
		Scene::Destroy(this);

	for (auto collision : m_collider->GetCollisions())
	{
		if (collision.first == "Tank")
		{
			dynamic_cast<Tank*>(collision.second)->TakeDamage(m_damage);
			Scene::AddLight(new Light(m_position + GetForward() * 6.0f + GetUp() * 2.0f, glm::vec3(0.8, 0.3, 0), 7, 1));
			Scene::Destroy(this);
		}

		if (collision.first == "Building")
		{
			dynamic_cast<Building*>(collision.second)->TakeDamage(m_damage);
			Scene::AddLight(new Light(m_position + GetForward() * 6.0f + GetUp() * 2.0f, glm::vec3(0.8, 0.3, 0), 7, 1));
			Scene::Destroy(this);
		}

		if (collision.first == "Wall")
		{
			dynamic_cast<Wall*>(collision.second)->TakeDamage(m_damage);
			Scene::AddLight(new Light(m_position + GetForward() * 6.0f + GetUp() * 2.0f, glm::vec3(0.8, 0.3, 0), 7, 1));
			Scene::Destroy(this);
		}
	}

	float moveSpeed = m_moveSpeed * Scene::GetDeltaTime();
	Move(GetForward() * moveSpeed);
}
