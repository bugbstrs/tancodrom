#include "Sun.h"
#include "Scene.h"
#include "InputManager.h"

std::vector<Texture> Sun::textures;
float Sun::rotationSpeed = 5.729f;

Sun::Sun(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation):
	LightSource(position, size, rotation, "sun")
{
	SetModel("Models/Sun/13913_Sun_v2_l3.obj", false, 4);

	textures.push_back(Texture("Models/Sun/13913_Sun_diff.jpg"));

    color = glm::vec3(0.6f);
    intensity = 12.2f;
    m_initialIntensity = intensity;
}

void Sun::Update()
{
    if (InputManager::KeyHold(GLFW_KEY_P))
    {
        rotationSpeed += 9.0f * Scene::GetDeltaTime();
    }

    if (InputManager::KeyHold(GLFW_KEY_O))
    {
        rotationSpeed -= 9.0f * Scene::GetDeltaTime();
    }
    
    RotateAround(glm::vec3(0), 110, glm::vec3(0, 0, 1), rotationSpeed * Scene::GetDeltaTime());

    if (m_position.y >= 1)
        Scene::SetPrimaryLight(this);

    if (m_position.y <= -2)
        intensity = 0;
    else
    if (m_position.y <= 2)
        intensity = ((m_position.y + 2) / 4) * m_initialIntensity;
    else
        intensity = m_initialIntensity;
}
