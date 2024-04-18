#pragma once
#include <glm/glm.hpp>

class SceneObject
{
public:
	virtual void Update() = 0;

	glm::vec3 GetPosition() const;
	void SetPosition(glm::vec3 position);
	void Move(glm::vec3 direction, bool globalCoordonates = false);

	glm::vec3 GetRotation() const;
	void SetRotation(glm::vec3 rotation);
	void Rotate(glm::vec3 direction);
	//TODO: rotatie in jurul unui punct cu o anumita viteza

	glm::vec3 GetSize() const;
	void SetSize(glm::vec3 size);

	glm::vec3 GetForward() const;
	glm::vec3 GetRight() const;
	glm::vec3 GetUp() const;

private:
	void NormalizeRotation();

	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_size;
};

