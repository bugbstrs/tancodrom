#pragma once
#include "SceneObject.h"

class Helicopter : public SceneObject
{
public:
	Helicopter(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation);

	void Update() override;

	static std::vector<Texture> textures;
private:
};

