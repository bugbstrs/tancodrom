#pragma once
#include "LightSource.h"

class Moon : public LightSource
{
public:
	Moon(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation);

	void Update() override;

private:

};

