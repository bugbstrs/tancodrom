#pragma once
#include "SceneObject.h"
#include "Camera.h"

class Tank : public SceneObject
{
public:
	Tank(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation);
	
	void Update() override;

	void SetCamera(Camera* camera);

private:
	const float m_rotationSpeed = 30.0f;
	const float m_moveSpeed = 2.0f;
	
	Camera *m_camera;
	bool m_isMoving;
};

