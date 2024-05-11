#include "Tank.h"
#include "Scene.h"
#include "InputManager.h"
#include "Projectile.h"
#include <SoundManager.h>

Model* Tank::tankModel = nullptr;
float Tank::turretRotationSpeed = 10.f;

Tank::Tank(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation) :
	SceneObject(position, size, rotation),
	m_camera{ nullptr },
	m_isMoving{ true }
{
	if (!tankModel)
	{
		tankModel = new Model("Models/Tanks/Tank/IS.obj", false, 2);
	}
	m_model = new Model(tankModel);
	m_collider = new Collider(glm::vec3(0), 6.9, "Tank", m_position, m_rotation);
}

void Tank::Update()
{
	m_isMoving = true;

	for (auto collision : m_collider->GetCollisions())
	{
		if (collision.first == "Tank")
			m_isMoving = false;
	}

	if (m_camera == nullptr || m_camera->GetCameraPOV() != TankCamera)
	{
		glm::vec3 forward = GetForward();
		float movementSpeed = 2.f * Scene::GetDeltaTime();

		if (m_isMoving)
		{
			Move(forward * movementSpeed);
		}

		return;
	}

	if (InputManager::MouseMoveX() != 0 && !SoundManager::IsPlayingTurretRotation())
	{
		SoundManager::StartTurretRotation();
	}

	m_model->SetMeshTransform(1, glm::rotate(m_model->GetMeshTransform(1), -glm::radians(m_turretRotation), glm::vec3(0, 1, 0)));
	m_model->SetMeshTransform(0, glm::rotate(m_model->GetMeshTransform(0), -glm::radians(m_turretRotation), glm::vec3(0, 1, 0)));
	m_turretRotation += -InputManager::MouseMoveX() * turretRotationSpeed * Scene::GetDeltaTime();
	m_model->SetMeshTransform(1, glm::rotate(m_model->GetMeshTransform(1), glm::radians(m_turretRotation), glm::vec3(0, 1, 0)));
	m_model->SetMeshTransform(0, glm::rotate(m_model->GetMeshTransform(0), glm::radians(m_turretRotation), glm::vec3(0, 1, 0)));

	float moveSpeed = m_moveSpeed * Scene::GetDeltaTime();
	float rotationSpeed = m_rotationSpeed * Scene::GetDeltaTime();

	if (InputManager::KeyHold(GLFW_KEY_W))
	{
		Move(GetForward() * moveSpeed);

		if (!SoundManager::IsPlayingMovingTank())
			SoundManager::StartMovingTank();
	}
	if (InputManager::KeyHold(GLFW_KEY_A))
	{
		Rotate(glm::vec3(0, rotationSpeed, 0));

		if (!SoundManager::IsPlayingMovingTank())
			SoundManager::StartMovingTank();
	}
	if (InputManager::KeyHold(GLFW_KEY_S))
	{
		Move(-GetForward() * moveSpeed);

		if (!SoundManager::IsPlayingMovingTank())
			SoundManager::StartMovingTank();
	}
	if (InputManager::KeyHold(GLFW_KEY_D))
	{
		Rotate(glm::vec3(0, -rotationSpeed, 0));

		if (!SoundManager::IsPlayingMovingTank())
			SoundManager::StartMovingTank();
	}

	if (!InputManager::KeyHold(GLFW_KEY_W) && !InputManager::KeyHold(GLFW_KEY_A) && !InputManager::KeyHold(GLFW_KEY_S) && !InputManager::KeyHold(GLFW_KEY_D))
	{
		SoundManager::StopMovingTank();
	}

	if (InputManager::PrimaryClick())
	{
		Scene::Instantiate(new Projectile(m_position, glm::vec3(1), m_rotation + GetTurretRotation()));
		SoundManager::PlayTankShot();
	}
}

void Tank::TakeDamage(float damage)
{
	m_health -= damage;
	if (m_health <= 0)
	{
		Scene::Destroy(this);
		SoundManager::PlayTankHit();
	}
	else
	{
		SoundManager::PlayTankExplosion();
	}
}

void Tank::SetCamera(Camera* camera)
{
	m_camera = camera;
}

glm::vec3 Tank::GetTurretRotation() const
{
	return glm::vec3(0, m_turretRotation, 0);
}
