#pragma once
#include "SceneObject.h"
#include "Camera.h"

class Helicopter : public SceneObject
{
public:
	Helicopter(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation);

	void Update() override;

	static std::vector<Texture> textures;

	void SetCamera(Camera* camera);
private:
	const float m_rotationSpeed = 30.0f;
	const float m_moveSpeed = 2.0f;

	Camera* m_camera;
};

