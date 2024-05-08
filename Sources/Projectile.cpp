#include "Projectile.h"
#include "Scene.h"

Projectile::Projectile(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation) :
	SceneObject(position, size, rotation)
{
	SetModel("Models/Projectile/projectile.obj", false, 2);
}

void Projectile::Update()
{
	m_lifeTime -= Scene::GetDeltaTime();
	if (m_lifeTime <= 0)
		Scene::Destroy(this);

	float moveSpeed = m_moveSpeed * Scene::GetDeltaTime();
	Move(GetForward() * moveSpeed);
}
