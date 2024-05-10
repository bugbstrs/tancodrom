#pragma once
#include "SceneObject.h"
#include "Camera.h"

class Tank : public SceneObject
{
public:
	Tank(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation);
	
	void Update() override;

	void TakeDamage(float damage);

	void SetCamera(Camera* camera);

private:
	float m_health = 100.0f;

	const float m_rotationSpeed = 30.0f;
	const float m_moveSpeed = 4.0f;
	
	Camera *m_camera;
	bool m_isMoving;
};

