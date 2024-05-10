#pragma once
#include <glm/glm.hpp>

#include "Model.h"
#include "Shader.h"

class SceneObject;

class Collider
{
public:
	Collider() = delete;
	Collider(const glm::vec3& position, float radius, const std::string& type, glm::vec3& objPosition, glm::vec3& objRotation);

	std::vector<std::pair<std::string, SceneObject*>> GetCollisions();
	void ClearCollisions();

	static void CheckCollisions(SceneObject* object1, SceneObject* object2);

private:
	glm::vec3 CalculatePosition();

	glm::vec3& m_objectPosition;
	glm::vec3& m_objectRotation;
	glm::vec3 m_position;
	float m_radius;
	std::string m_type;
	std::vector<std::pair<std::string, SceneObject*>> m_collisions;

	friend class Scene;
};

class SceneObject
{
public:
	SceneObject(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation);

	void SetModel(std::string const& path, bool bSmoothNormals, int modelId);

	Collider* GetCollider();

	virtual void Update() = 0;

	glm::vec3 GetPosition() const;
	void SetPosition(glm::vec3 position);
	void Move(glm::vec3 direction);

	glm::vec3 GetRotation() const;
	void SetRotation(glm::vec3 rotation);
	void Rotate(glm::vec3 direction);
	void RotateAround(float distance, float rotationSpeed);

	glm::vec3 GetSize() const;
	void SetSize(glm::vec3 size);

	glm::vec3 GetForward() const;
	glm::vec3 GetRight() const;
	glm::vec3 GetUp() const;

	virtual void Render(Shader& shader);

protected:
	Model* m_model;
	Collider* m_collider;

	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_size;

	float RotationAngle = 0;
	const float DegreesToRadians = 0.01745f;

private:
	void NormalizeRotation();
};

