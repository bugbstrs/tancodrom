#pragma once
#include "Camera.h"
#include "Tank.h"
#include "Helicopter.h"
#include <Sun.h>
#include <Moon.h>

class CinematicHandler : public SceneObject
{
public:
	CinematicHandler(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation);

	void Update() override;

private:
	void ResetScene();

	void StartCinematic1();
	void Cinematic1();
	void StartCinematic2();
	void Cinematic2();
	void StartCinematic3();
	void Cinematic3();
	void StartCinematic4();
	void Cinematic4();
	void StartCinematic5();
	void Cinematic5();
	void StartCinematic6();
	void Cinematic6();

	float m_elapsedTime = 0;
	float m_lastElapsedTime = 0;

	Camera* m_camera = nullptr;
	Sun* m_sun = nullptr;
	Moon* m_moon = nullptr;
	std::vector<Tank*> m_tanks;
	std::vector<Helicopter*> m_helicopters;
};