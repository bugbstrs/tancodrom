#include "Sun.h"
#include "Scene.h"
#include "InputManager.h"

std::vector<Texture> Sun::textures;
float Sun::rotationSpeed = 0.1f;

Sun::Sun(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation):
	LightSource(position, size, rotation)
{
	SetModel("Models/Sun/13913_Sun_v2_l3.obj", false, 4);

	textures.push_back(Texture("Models/Sun/13913_Sun_diff.jpg"));

    color = glm::vec3(0.6f);
    intensity = 10.0f;
}

void Sun::Update()
{
    if (InputManager::KeyHold(GLFW_KEY_P))
    {
        rotationSpeed += 0.1f * Scene::GetDeltaTime();
    }

    if (InputManager::KeyHold(GLFW_KEY_O))
    {
        rotationSpeed -= 0.1f * Scene::GetDeltaTime();
    }
    
    RotateAround(glm::vec3(0), 90, glm::vec3(0, 0, 1), rotationSpeed * Scene::GetDeltaTime());

    if (m_position.y >= 1)
        Scene::SetPrimaryLight(this);
}
