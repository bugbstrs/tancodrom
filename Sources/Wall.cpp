#include "Wall.h"
#include "Scene.h"
#include "SoundManager.h"
#include "Light.h"

Model* Wall::wallModel = nullptr;

Wall::Wall(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation, int wallType):
	SceneObject(position, size, rotation, "wall")
{
	if (!wallModel)
	{
		wallModel = new Model("Models/BuildingSecondary/SimpleBlue/simpleblue.obj", false, 14);
	}

	m_model = new Model(wallModel);
	m_collider = new Collider(glm::vec3(0), 6, "Wall", m_position, m_rotation);
}

void Wall::Update()
{
}

void Wall::TakeDamage(float damage)
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
		m_position.y -= 1.5;
		SoundManager::PlayTankExplosion();
	}
}

void Wall::Render(Shader& shader)
{
	glEnable(GL_DEPTH_TEST);
	if (!m_model)
		return;
	glm::mat4 modelTransform(1.0f);
	modelTransform = glm::translate(modelTransform, m_position);
	modelTransform = glm::rotate(modelTransform, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	modelTransform = glm::rotate(modelTransform, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	modelTransform = glm::rotate(modelTransform, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	modelTransform = glm::scale(modelTransform, m_size);
	m_model->RenderModel(shader, modelTransform);
	//glDisable(GL_DEPTH_TEST);
}
