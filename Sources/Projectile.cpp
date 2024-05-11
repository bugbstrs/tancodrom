#include "Projectile.h"
#include "Scene.h"
#include "Tank.h"

Model* Projectile::projectileModel = nullptr;

Projectile::Projectile(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation) :
	SceneObject(position, size, rotation)
{
	if (!projectileModel)
	{
		projectileModel = new Model("Models/Projectile/projectile.obj", false, 2);
	}
	m_model = projectileModel;
	m_collider = new Collider(glm::vec3(0,2,6), 0.5, "Projectile", m_position, m_rotation);
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
			Scene::Destroy(this);
		}
	}

	float moveSpeed = m_moveSpeed * Scene::GetDeltaTime();
	Move(GetForward() * moveSpeed);
}
