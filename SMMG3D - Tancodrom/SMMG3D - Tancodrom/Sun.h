#pragma once
#include "LightSource.h"

class Sun : public LightSource
{
public:
	Sun(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation);

	void Update() override;

private:

};

