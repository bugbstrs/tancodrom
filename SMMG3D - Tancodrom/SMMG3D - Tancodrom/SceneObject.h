#pragma once
#include <glm/glm.hpp>

#include "Model.h"
#include "Shader.h"

class SceneObject
{
public:
	SceneObject(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation);

	void SetModel(std::string const& path, bool bSmoothNormals, int modelId);

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

	void Render(Shader& shader);

protected:
	Model* m_model;

	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_size;

	float RotationAngle = 0;
	const float DegreesToRadians = 0.01745f;

private:
	void NormalizeRotation();
};

