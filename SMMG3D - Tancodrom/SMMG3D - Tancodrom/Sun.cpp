#include "Sun.h"
#include "Scene.h"

std::vector<Texture> Sun::textures;

Sun::Sun(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation):
	LightSource(position, size, rotation)
{
	SetModel("Models/Sun/13913_Sun_v2_l3.obj", false, 4);

	textures.push_back(Texture("Models/Sun/13913_Sun_diff.jpg"));
}

void Sun::Update()
{
	RotateAround(-35.f, 0.2f * glfwGetTime());
}
