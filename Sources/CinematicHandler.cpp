#include "CinematicHandler.h"
#include "InputManager.h"
#include "Building.h"
#include "Wall.h"

CinematicHandler::CinematicHandler(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation) :
	SceneObject(position, size, rotation, "cinematic")
{}

const float cinematicTime1 = 8.0f;
const float cinematicTime2 = 13.0f;
const float cinematicTime3 = 20.5f;
const float cinematicTime4 = 32.5f;
const float cinematicTime5 = 50.0f;
const float cinematicTime6 = 16.0f;

void CinematicHandler::Update()
{
	for (auto object : m_tanks)
		if (object->GetName() == "")
			m_tanks.erase(std::find(m_tanks.begin(), m_tanks.end(), object));
	for (auto object : m_helicopters)
		if (object->GetName() == "")
			m_helicopters.erase(std::find(m_helicopters.begin(), m_helicopters.end(), object));

	static int z = 0;
	if (InputManager::KeyDown(GLFW_KEY_SPACE))
	{
		if (z == 1)
		{
			z = 2;
			m_camera->SetCameraPOV(FreeCamera);
			return;
		}
		else
			z = 1;

		ResetScene();
		m_elapsedTime = 0;
	}
	if (!m_camera || m_camera->GetCameraPOV() != CinematicCamera)
		return;

	if (z == 2)
		return;

	m_lastElapsedTime = m_elapsedTime;
	m_elapsedTime += Scene::GetDeltaTime();

	if (m_lastElapsedTime == 0.0f)
	{
		StartCinematic1();
	}else
	if (m_lastElapsedTime <= cinematicTime1 && m_elapsedTime <= cinematicTime1)
	{
		Cinematic1();
	}else
	if (m_lastElapsedTime <= cinematicTime1 && m_elapsedTime <= cinematicTime2)
	{
		StartCinematic2();
	}else
	if (m_lastElapsedTime <= cinematicTime2 && m_elapsedTime <= cinematicTime2)
	{
		Cinematic2();
	}else
	if (m_lastElapsedTime <= cinematicTime2 && m_elapsedTime <= cinematicTime3)
	{
		StartCinematic3();
	}else
	if (m_lastElapsedTime <= cinematicTime3 && m_elapsedTime <= cinematicTime3)
	{
		Cinematic3();
	}else
	if (m_lastElapsedTime <= cinematicTime3 && m_elapsedTime <= cinematicTime4)
	{
		StartCinematic4();
	}else
	if (m_lastElapsedTime <= cinematicTime4 && m_elapsedTime <= cinematicTime4)
	{
		Cinematic4();
	}else
	if (m_lastElapsedTime <= cinematicTime4 && m_elapsedTime <= cinematicTime5)
	{
		StartCinematic5();
	}else
	if (m_lastElapsedTime <= cinematicTime5 && m_elapsedTime <= cinematicTime5)
	{
		Cinematic5();
	}else
	if (m_lastElapsedTime <= cinematicTime5 && m_elapsedTime <= cinematicTime6)
	{
		StartCinematic6();
	}else
	if (m_lastElapsedTime <= cinematicTime6 && m_elapsedTime <= cinematicTime6)
	{
		Cinematic6();
	}
}

void CinematicHandler::ResetScene()
{
	auto tanks = Scene::GetAllObjects("tank");
	for (auto tank : tanks)
		Scene::Destroy(tank);
	m_tanks.clear();
	auto helicopters = Scene::GetAllObjects("helicopter");
	for (auto helicopter : helicopters)
		Scene::Destroy(helicopter);
	m_helicopters.clear();
	auto projectiles = Scene::GetAllObjects("projectile");
	for (auto projectile : projectiles)
		Scene::Destroy(projectile);
	auto lights = Scene::GetAllObjects("light");
	for (auto light : lights)
		Scene::DestroyLight(dynamic_cast<LightSource*>(light));
	auto buildings = Scene::GetAllObjects("building");
	for (auto building : buildings)
		Scene::Destroy(building);
	auto walls = Scene::GetAllObjects("wall");
	for (auto wall : walls)
		Scene::Destroy(wall);
	m_camera = Scene::GetCamera();
	m_camera->SetTank(nullptr);
	m_camera->SetHelicopter(nullptr);
	m_camera->SetCameraPOV(CinematicCamera);
	Scene::DestroyLight(dynamic_cast<Sun*>(Scene::GetObject("sun")));
	Scene::DestroyLight(dynamic_cast<Moon*>(Scene::GetObject("moon")));
}

void CinematicHandler::StartCinematic1()
{
	m_tanks.emplace_back(new Tank(glm::vec3(-30, 0, -25), glm::vec3(1), glm::vec3(0, 0, 0)));
	Scene::Instantiate(m_tanks.back());
	m_tanks.emplace_back(new Tank(glm::vec3(-30, 0, 25), glm::vec3(1), glm::vec3(0, 180, 0)));
	Scene::Instantiate(m_tanks.back());

	m_tanks.emplace_back(new Tank(glm::vec3(-15, 0, -25), glm::vec3(1), glm::vec3(0, 0, 0)));
	Scene::Instantiate(m_tanks.back());
	m_tanks.emplace_back(new Tank(glm::vec3(-15, 0, 25), glm::vec3(1), glm::vec3(0, 180, 0)));
	Scene::Instantiate(m_tanks.back());

	m_tanks.emplace_back(new Tank(glm::vec3(0, 0, -25), glm::vec3(1), glm::vec3(0, 0, 0)));
	Scene::Instantiate(m_tanks.back());
	m_tanks.emplace_back(new Tank(glm::vec3(0, 0, 25), glm::vec3(1), glm::vec3(0, 180, 0)));
	Scene::Instantiate(m_tanks.back());

	m_tanks.emplace_back(new Tank(glm::vec3(15, 0, -25), glm::vec3(1), glm::vec3(0, 0, 0)));
	Scene::Instantiate(m_tanks.back());
	m_tanks.emplace_back(new Tank(glm::vec3(15, 0, 25), glm::vec3(1), glm::vec3(0, 180, 0)));
	Scene::Instantiate(m_tanks.back());

	m_tanks.emplace_back(new Tank(glm::vec3(30, 0, -25), glm::vec3(1), glm::vec3(0, 0, 0)));
	Scene::Instantiate(m_tanks.back());
	m_tanks.emplace_back(new Tank(glm::vec3(30, 0, 25), glm::vec3(1), glm::vec3(0, 180, 0)));
	Scene::Instantiate(m_tanks.back());

	Scene::Instantiate(new Building(glm::vec3(91, 0, -90), glm::vec3(1), glm::vec3(0, 45, 0)));
	Scene::Instantiate(new Building(glm::vec3(72.8, 0, -82), glm::vec3(1), glm::vec3(0, 90, 0)));
	Scene::Instantiate(new Building(glm::vec3(54.6, 0, -87), glm::vec3(1), glm::vec3(0, 30, 0)));
	Scene::Instantiate(new Building(glm::vec3(36.4, 0, -78), glm::vec3(1), glm::vec3(0, 60, 0)));
	Scene::Instantiate(new Building(glm::vec3(18.2, 0, -78), glm::vec3(1), glm::vec3(0, 120, 0)));
	Scene::Instantiate(new Building(glm::vec3(0, 0, -73), glm::vec3(1), glm::vec3(0, 180, 0)));
	Scene::Instantiate(new Building(glm::vec3(-91, 0, -90), glm::vec3(1), glm::vec3(0, 270, 0)));
	Scene::Instantiate(new Building(glm::vec3(-72.8, 0, -82), glm::vec3(1), glm::vec3(0, 330, 0)));
	Scene::Instantiate(new Building(glm::vec3(-54.6, 0, -87), glm::vec3(1), glm::vec3(0, 210, 0)));
	Scene::Instantiate(new Building(glm::vec3(-36.4, 0, -78), glm::vec3(1), glm::vec3(0, 240, 0)));
	Scene::Instantiate(new Building(glm::vec3(-18.2, 0, -78), glm::vec3(1), glm::vec3(0, 300, 0)));
	Scene::Instantiate(new Building(glm::vec3(91, 0, -90), glm::vec3(1), glm::vec3(0, 15, 0)));
	Scene::Instantiate(new Building(glm::vec3(72.8, 0, -82), glm::vec3(1), glm::vec3(0, 75, 0)));
	Scene::Instantiate(new Building(glm::vec3(54.6, 0, -87), glm::vec3(1), glm::vec3(0, 135, 0)));

	Scene::Instantiate(new Wall(glm::vec3(91, -0.3, -60), glm::vec3(0.5), glm::vec3(0, 0, 0), 0));
	Scene::Instantiate(new Wall(glm::vec3(72.8, -0.3, -60), glm::vec3(0.5), glm::vec3(0, 0, 0), 0));
	Scene::Instantiate(new Wall(glm::vec3(54.6, -0.3, -60), glm::vec3(0.5), glm::vec3(0, 0, 0), 0));
	Scene::Instantiate(new Wall(glm::vec3(36.4, -0.3, -60), glm::vec3(0.5), glm::vec3(0, 0, 0), 0));
	Scene::Instantiate(new Wall(glm::vec3(18.2, -0.3, -60), glm::vec3(0.5), glm::vec3(0, 0, 0), 0));
	Scene::Instantiate(new Wall(glm::vec3(0, -0.3, -60), glm::vec3(0.5), glm::vec3(0, 0, 0), 0));
	Scene::Instantiate(new Wall(glm::vec3(-18.2, -0.3, -60), glm::vec3(0.5), glm::vec3(0, 0, 0), 0));
	Scene::Instantiate(new Wall(glm::vec3(-36.4, -0.3, -60), glm::vec3(0.5), glm::vec3(0, 0, 0), 0));
	Scene::Instantiate(new Wall(glm::vec3(-54.6, -0.3, -60), glm::vec3(0.5), glm::vec3(0, 0, 0), 0));
	Scene::Instantiate(new Wall(glm::vec3(-72.8, -0.3, -60), glm::vec3(0.5), glm::vec3(0, 0, 0), 0));
	Scene::Instantiate(new Wall(glm::vec3(-91, -0.3, -60), glm::vec3(0.5), glm::vec3(0, 0, 0), 0));

	// Second city
	Scene::Instantiate(new Building(glm::vec3(91, 0, 90), glm::vec3(1), glm::vec3(0, 45, 0)));
	Scene::Instantiate(new Building(glm::vec3(72.8, 0, 82), glm::vec3(1), glm::vec3(0, 90, 0)));
	Scene::Instantiate(new Building(glm::vec3(54.6, 0, 87), glm::vec3(1), glm::vec3(0, 30, 0)));
	Scene::Instantiate(new Building(glm::vec3(36.4, 0, 78), glm::vec3(1), glm::vec3(0, 60, 0)));
	Scene::Instantiate(new Building(glm::vec3(18.2, 0, 78), glm::vec3(1), glm::vec3(0, 120, 0)));
	Scene::Instantiate(new Building(glm::vec3(0, 0, 73), glm::vec3(1), glm::vec3(0, 180, 0)));
	Scene::Instantiate(new Building(glm::vec3(-91, 0, 90), glm::vec3(1), glm::vec3(0, 270, 0)));
	Scene::Instantiate(new Building(glm::vec3(-72.8, 0, 82), glm::vec3(1), glm::vec3(0, 330, 0)));
	Scene::Instantiate(new Building(glm::vec3(-54.6, 0, 87), glm::vec3(1), glm::vec3(0, 210, 0)));
	Scene::Instantiate(new Building(glm::vec3(-36.4, 0, 78), glm::vec3(1), glm::vec3(0, 240, 0)));
	Scene::Instantiate(new Building(glm::vec3(-18.2, 0, 78), glm::vec3(1), glm::vec3(0, 300, 0)));
	Scene::Instantiate(new Building(glm::vec3(91, 0, 90), glm::vec3(1), glm::vec3(0, 15, 0)));
	Scene::Instantiate(new Building(glm::vec3(72.8, 0, 82), glm::vec3(1), glm::vec3(0, 75, 0)));
	Scene::Instantiate(new Building(glm::vec3(54.6, 0, 87), glm::vec3(1), glm::vec3(0, 135, 0)));

	Scene::Instantiate(new Wall(glm::vec3(91, -0.3, 60), glm::vec3(0.5), glm::vec3(0, 180, 0), 0));
	Scene::Instantiate(new Wall(glm::vec3(72.8, -0.3, 60), glm::vec3(0.5), glm::vec3(0, 180, 0), 0));
	Scene::Instantiate(new Wall(glm::vec3(54.6, -0.3, 60), glm::vec3(0.5), glm::vec3(0, 180, 0), 0));
	Scene::Instantiate(new Wall(glm::vec3(36.4, -0.3, 60), glm::vec3(0.5), glm::vec3(0, 180, 0), 0));
	Scene::Instantiate(new Wall(glm::vec3(18.2, -0.3, 60), glm::vec3(0.5), glm::vec3(0, 180, 0), 0));
	Scene::Instantiate(new Wall(glm::vec3(0, -0.3, 60), glm::vec3(0.5), glm::vec3(0, 180, 0), 0));
	Scene::Instantiate(new Wall(glm::vec3(-18.2, -0.3, 60), glm::vec3(0.5), glm::vec3(0, 180, 0), 0));
	Scene::Instantiate(new Wall(glm::vec3(-36.4, -0.3, 60), glm::vec3(0.5), glm::vec3(0, 180, 0), 0));
	Scene::Instantiate(new Wall(glm::vec3(-54.6, -0.3, 60), glm::vec3(0.5), glm::vec3(0, 180, 0), 0));
	Scene::Instantiate(new Wall(glm::vec3(-72.8, -0.3, 60), glm::vec3(0.5), glm::vec3(0, 180, 0), 0));
	Scene::Instantiate(new Wall(glm::vec3(-91, -0.3, 60), glm::vec3(0.5), glm::vec3(0, 180, 0), 0));

	m_sun = new Sun(glm::vec3(10, 0, 0), glm::vec3(0.006), glm::vec3(0, 0, 0));
	Scene::AddLight(m_sun);

	m_moon = new Moon(glm::vec3(-10, 0, 0), glm::vec3(0.5), glm::vec3(0, 0, 0));
	Scene::AddLight(m_moon);

	m_tanks[0]->SetTarget(m_tanks[3]);
	m_tanks[1]->SetTarget(m_tanks[2]);
	m_tanks[2]->SetTarget(m_tanks[1]);
	m_tanks[3]->SetTarget(m_tanks[0]);
	m_tanks[4]->SetTarget(m_tanks[5]);
	m_tanks[5]->SetTarget(m_tanks[4]);
	m_tanks[6]->SetTarget(m_tanks[9]);
	m_tanks[7]->SetTarget(m_tanks[8]);
	m_tanks[8]->SetTarget(m_tanks[7]);
	m_tanks[9]->SetTarget(m_tanks[6]);

	m_camera->SetPosition(glm::vec3(-50, 0.5, 0));
	m_camera->SetRotation(glm::vec3(0, 90, 15));
}

void CinematicHandler::Cinematic1()
{
	m_camera->MoveTowards(m_sun->GetPosition(), 5.0f * Scene::GetDeltaTime());
	m_camera->Rotate(glm::vec3(0, 0, -5.0f * Scene::GetDeltaTime()));
}

void CinematicHandler::StartCinematic2()
{

}

void CinematicHandler::Cinematic2()
{
	if (m_camera->GetPosition().y < 12.0f)
		m_camera->Move(Scene::Up() * 1.0f * Scene::GetDeltaTime());
	m_camera->Move(Scene::Right() * 5.0f * Scene::GetDeltaTime());
	if(m_camera->GetRotation().y > -90.0f)
		m_camera->Rotate(glm::vec3(0, -90.0f * Scene::GetDeltaTime(), 0));
	if (m_camera->GetRotation().z < 25.0f)
		m_camera->Rotate(glm::vec3(0, 0, 10.0f * Scene::GetDeltaTime()));
}

void CinematicHandler::StartCinematic3()
{
	auto position = m_camera->GetPosition();
	position.y = 12;
	m_camera->SetPosition(position);
}

void CinematicHandler::Cinematic3()
{
	m_camera->Move(Scene::Right() * 5.0f * Scene::GetDeltaTime());
}

void CinematicHandler::StartCinematic4()
{
	auto position = m_camera->GetPosition();
	position.x = 50;
	m_camera->SetPosition(position);
}

void CinematicHandler::Cinematic4()
{
	m_camera->RotateAround(glm::vec3(0 + cinematicTime3 - m_elapsedTime, 12, 0), 50 + cinematicTime3 - m_elapsedTime, glm::vec3(0, 1, 0), 30.0f * Scene::GetDeltaTime());
	auto rotation = m_camera->GetRotation();
	rotation.y += 30.0f * Scene::GetDeltaTime();
	rotation.z -= 4.15f * Scene::GetDeltaTime();
	m_camera->SetRotation(rotation);
}

void CinematicHandler::StartCinematic5()
{
	auto sunPos = m_sun->GetPosition();
	auto moonPos = m_moon->GetPosition();

	ResetScene();

	m_helicopters.emplace_back(new Helicopter(glm::vec3(0, 30, -30), glm::vec3(0.5), glm::vec3(0, 0, 0)));
	Scene::Instantiate(m_helicopters.back());

	m_sun = new Sun(sunPos, glm::vec3(0.006), glm::vec3(0, 0, 0));
	Scene::AddLight(m_sun);

	m_moon = new Moon(moonPos, glm::vec3(0.5), glm::vec3(0, 0, 0));
	Scene::AddLight(m_moon);
}

void CinematicHandler::Cinematic5()
{
	if (m_helicopters.empty())
		return;

	m_helicopters[0]->Rotate(glm::vec3(9 * Scene::GetDeltaTime(), 276 * Scene::GetDeltaTime(), 2 * Scene::GetDeltaTime()));
	m_helicopters[0]->MoveTowards(glm::vec3(0, 0, 30), (10.0f - cinematicTime4 + m_elapsedTime) * Scene::GetDeltaTime());
	m_camera->LookAt(m_helicopters[0]->GetPosition(), Scene::Up());
}

void CinematicHandler::StartCinematic6()
{
}

void CinematicHandler::Cinematic6()
{
}
