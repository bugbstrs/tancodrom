#include "Sun.h"
#include "Scene.h"
#include "InputManager.h"

std::vector<Texture> Sun::textures;
float Sun::rotationSpeed = 0.1f;
float Sun::lastFrame;

Sun::Sun(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation):
	LightSource(position, size, rotation)
{
	SetModel("Models/Sun/13913_Sun_v2_l3.obj", false, 4);

	textures.push_back(Texture("Models/Sun/13913_Sun_diff.jpg"));
}

void Sun::Update()
{
	RotateAround(-5.f, 0.1f * glfwGetTime());
}
