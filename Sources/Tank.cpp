#include "Tank.h"
#include "Scene.h"
#include "InputManager.h"
#include "Projectile.h"
#include "Light.h"
#include "SoundManager.h"
#include <random>

Model* Tank::tankModel = nullptr;
float Tank::turretRotationSpeed = 10.f;

Tank::Tank(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation) :
	SceneObject(position, size, rotation, "tank"),
	m_camera{ nullptr },
	m_isMoving{ true }
{
	if (!tankModel)
	{
		tankModel = new Model("Models/Tanks/Tank/IS.obj", false, 2);
	}
	m_model = new Model(tankModel);
	m_collider = new Collider(glm::vec3(0), 3.3, "Tank", m_position, m_rotation);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> distr(-2.0, 6.0);
	float randomNumber = distr(gen);
	m_currentReloadTime = m_reloadTime + distr(gen);
}

Tank::~Tank()
{
	m_collider = new Collider(glm::vec3(0), 3, "Tank", m_position, m_rotation);
}

void Tank::Update()
{
	if (m_target && m_target->GetName() == "")
		m_target = nullptr;

	m_currentReloadTime -= Scene::GetDeltaTime();

	m_isMoving = true;
	auto collisions = m_collider->GetCollisions();
	for (auto collision : collisions)
	{
		if (collision.first == "Tank")
		{
			m_isMoving = false;
			Collider::ResolveCollision(this, collision.second);
		}

		if (collision.first == "Wall")
		{
			m_isMoving = false;
			Collider::ResolveCollision2(this, collision.second);
		}
	}

	auto collision = Scene::RayCast(m_position, GetForward());
	if (collision.first == "Tank" && glm::distance(m_position, collision.second->GetPosition()) <= 13.0f)
		m_isMoving = false;

	if (m_camera == nullptr || m_camera->GetCameraPOV() != TankCamera)
	{
		glm::vec3 forward = GetForward();
		float movementSpeed = 0.5f * Scene::GetDeltaTime();

		if (m_isMoving)
		{
			Move(forward * movementSpeed);
		}

		if (m_target)
		{
			glm::vec3 directionToTarget = glm::normalize(m_target->GetPosition() - m_position);
			glm::vec3 crossProduct = glm::cross(GetForward(), directionToTarget);

			float angleToTarget = std::atan2(glm::length(crossProduct), glm::dot(GetForward(), directionToTarget));

			if (glm::dot(glm::cross(GetForward(), directionToTarget), glm::vec3(0, 1, 0)) < 0) {
				angleToTarget = -angleToTarget;
			}

			m_model->SetMeshTransform(1, glm::rotate(glm::mat4(1.0f), angleToTarget, glm::vec3(0, 1, 0)));
			m_model->SetMeshTransform(0, glm::rotate(glm::mat4(1.0f), angleToTarget, glm::vec3(0, 1, 0)));

			m_turretRotation = glm::degrees(angleToTarget);

			if (m_currentReloadTime <= 0)
			{
				std::random_device rd;
				std::mt19937 gen(rd());
				std::uniform_real_distribution<float> distr(-2.0, 6.0);
				float randomNumber = distr(gen);
				m_currentReloadTime = m_reloadTime + distr(gen);
				Scene::Instantiate(new Projectile(m_position, glm::vec3(1), m_rotation + GetTurretRotation()));
				SoundManager::PlayTankShot();
			}
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
		if (m_currentReloadTime <= 0)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<float> distr(-2.0, 6.0);
			float randomNumber = distr(gen);
			m_currentReloadTime = m_reloadTime + distr(gen);
			Scene::Instantiate(new Projectile(m_position, glm::vec3(1), m_rotation + GetTurretRotation()));
			SoundManager::PlayTankShot();
		}
	}
}

void Tank::TakeDamage(float damage)
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
		SoundManager::PlayTankExplosion();
	}
}

void Tank::SetCamera(Camera* camera)
{
	m_camera = camera;
}

void Tank::SetTarget(SceneObject* tank)
{
	m_target = tank;
}

glm::vec3 Tank::GetTurretRotation() const
{
	return glm::vec3(0, m_turretRotation, 0);
}
