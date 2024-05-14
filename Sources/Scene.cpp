#include "Program.h"
#include "Scene.h"
#include "InputManager.h"
#include "Tank.h"
#include "Moon.h"
#include "Sun.h"
#include "Helicopter.h"
#include "Projectile.h"
#include "Terrain.h"
#include <stb_image.h>
#include "SoundManager.h"
#include "CinematicHandler.h"

std::vector<SceneObject*> Scene::m_objects;
std::vector<SceneObject*> Scene::m_objectsToInstantiate;
std::vector<LightSource*> Scene::m_lightsToInstantiate;
std::vector<SceneObject*> Scene::m_objectsToDestroy;
std::vector<LightSource*> Scene::m_lightsToDestroy;
std::vector<LightSource*> Scene::m_lights;
std::unique_ptr<SkyBox> Scene::m_skybox;
Camera* Scene::m_camera;
float Scene::m_deltaTime;

void Scene::Start()
{
	m_camera = new Camera(glm::vec3(0, 2, 0), glm::vec3(1), glm::vec3(0, 0, 0));
	m_objects.push_back(m_camera);

	m_objects.emplace_back(new Terrain(glm::vec3(0, -5.05, 0), glm::vec3(10), glm::vec3(0, 0, 0)));


	m_objects.emplace_back(new Tank(glm::vec3(-30, 0, -20), glm::vec3(1), glm::vec3(0, 0, 0)));
	m_objects.emplace_back(new Tank(glm::vec3(-30, 0, 20), glm::vec3(1), glm::vec3(0, 180, 0)));

	m_objects.emplace_back(new Tank(glm::vec3(-15, 0, -20), glm::vec3(1), glm::vec3(0, 0, 0)));
	m_objects.emplace_back(new Tank(glm::vec3(-15, 0, 20), glm::vec3(1), glm::vec3(0, 180, 0)));

	m_objects.emplace_back(new Tank(glm::vec3(0, 0, -20), glm::vec3(1), glm::vec3(0, 0, 0)));
	m_objects.emplace_back(new Tank(glm::vec3(0, 0, 20), glm::vec3(1), glm::vec3(0, 180, 0)));

	m_objects.emplace_back(new Tank(glm::vec3(15, 0, -20), glm::vec3(1), glm::vec3(0, 0, 0)));
	m_objects.emplace_back(new Tank(glm::vec3(15, 0, 20), glm::vec3(1), glm::vec3(0, 180, 0)));

	m_objects.emplace_back(new Tank(glm::vec3(30, 0, -20), glm::vec3(1), glm::vec3(0, 0, 0)));
	m_objects.emplace_back(new Tank(glm::vec3(30, 0, 20), glm::vec3(1), glm::vec3(0, 180, 0)));

	m_objects.push_back(new Helicopter(glm::vec3(-30, 15, -20), glm::vec3(0.5), glm::vec3(0, 0, 0)));
	m_objects.push_back(new Helicopter(glm::vec3(-30, 15, 20), glm::vec3(0.5), glm::vec3(0, 180, 0)));

	m_objects.push_back(new Helicopter(glm::vec3(-15, 15, -20), glm::vec3(0.5), glm::vec3(0, 0, 0)));
	m_objects.push_back(new Helicopter(glm::vec3(-15, 15, 20), glm::vec3(0.5), glm::vec3(0, 180, 0)));

	m_objects.push_back(new Helicopter(glm::vec3(0, 15, -20), glm::vec3(0.5), glm::vec3(0, 0, 0)));
	m_objects.push_back(new Helicopter(glm::vec3(0, 15, 20), glm::vec3(0.5), glm::vec3(0, 180, 0)));

	m_objects.push_back(new Helicopter(glm::vec3(15, 15, -20), glm::vec3(0.5), glm::vec3(0, 0, 0)));
	m_objects.push_back(new Helicopter(glm::vec3(15, 15, 20), glm::vec3(0.5), glm::vec3(0, 180, 0)));

	m_objects.push_back(new Helicopter(glm::vec3(30, 15, -20), glm::vec3(0.5), glm::vec3(0, 0, 0)));
	m_objects.push_back(new Helicopter(glm::vec3(30, 15, 20), glm::vec3(0.5), glm::vec3(0, 180, 0)));

	m_objects.push_back(new Sun(glm::vec3(10, 0, 0), glm::vec3(0.006), glm::vec3(0, 0, 0)));
	m_lights.push_back((LightSource*)m_objects[m_objects.size() - 1]);

	m_objects.push_back(new Moon(glm::vec3(-10, 0, 0), glm::vec3(0.5), glm::vec3(0, 0, 0)));
	m_lights.push_back((LightSource*)m_objects[m_objects.size() - 1]);

	m_objects.push_back(new SkyBox(glm::vec3(0, 0, 0), glm::vec3(30), glm::vec3(0, 0, 0)));

	m_objects.push_back(new CinematicHandler(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)));

	Projectile::InitializeModel();

	SoundManager::Initialize();
	//SoundManager::DecreaseVolume();
}

void Scene::Run()
{
	float lastFrame = 0;
	m_deltaTime = 0;

	unsigned int depthMapFBO;
	glGenFramebuffers(1, &depthMapFBO);
	const unsigned int SHADOW_WIDTH = 8192, SHADOW_HEIGHT = 8192;
	unsigned int depthMap;
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	Program::m_shadowMappingShader.Use();
	Program::m_shadowMappingShader.SetInt("diffuseTexture", 0);
	Program::m_shadowMappingShader.SetInt("shadowMap", 1);

	Start();

	while (!glfwWindowShouldClose(Program::GetWindow()))
	{
		glClearColor(0.3f, 0.3f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float currentFrame = glfwGetTime();
		m_deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//Check collisions
		for (int i = 0; i < m_objects.size(); ++i)
		{
			for (int j = i + 1; j < m_objects.size(); ++j)
			{
				Collider::CheckCollisions(m_objects[i], m_objects[j]);
			}
		}

		//logica
		for (auto object : m_objects)
		{
			object->Update();
		}

		//randare umbre
		Program::m_shadowMappingDepthShader.Use();
		Program::m_shadowMappingDepthShader.SetMat4("lightSpaceMatrix", m_lights[0]->GetLightSpaceMatrix());

		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);

		for (auto object : m_objects)
		{
			object->Render(Program::m_shadowMappingDepthShader);
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glActiveTexture(GL_TEXTURE0);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		glCullFace(GL_BACK);

		glViewport(0, 0, Program::GetScreenWidth(), Program::GetScreenHeight());
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//randare scena
		Program::m_shadowMappingShader.Use();
		Program::m_shadowMappingShader.SetMat4("projection", m_camera->GetProjectionMatrix());
		Program::m_shadowMappingShader.SetMat4("view", m_camera->GetViewMatrix());

		Program::m_shadowMappingShader.SetVec3("viewPos", m_camera->GetPosition());
		Program::m_shadowMappingShader.SetVec3("lightPos", m_lights[0]->GetPosition());
		Program::m_shadowMappingShader.SetMat4("lightSpaceMatrix", m_lights[0]->GetLightSpaceMatrix());

		std::vector<glm::vec3> lightsPosition;
		std::vector<glm::vec3> lightsColor;
		std::vector<float> lightsIntensity;
		for (auto light : m_lights)
		{
			lightsPosition.push_back(light->GetPosition());
			lightsColor.push_back(light->color);
			lightsIntensity.push_back(light->intensity);
		}
		Program::m_shadowMappingShader.SetInt("numLights", m_lights.size());
		Program::m_shadowMappingShader.SetLightsVec3("position", lightsPosition);
		Program::m_shadowMappingShader.SetLightsVec3("color", lightsColor);
		Program::m_shadowMappingShader.SetLightsFloat("intensity", lightsIntensity);
		float sunPos = GetObject("sun")->GetPosition().y;
		float skyboxHue = 0.3 + ((sunPos + 90) / 180 * 0.7);
		Program::m_shadowMappingShader.SetFloat("skyboxHue", skyboxHue);

		glActiveTexture(GL_TEXTURE0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, depthMap);

		for (auto object : m_objects)
		{
			object->Render(Program::m_shadowMappingShader);
		}
		
		InputManager::ClearMouseMovement();

		//Clear collisions
		for (auto object : m_objects)
		{
			if (object->GetCollider())
				object->GetCollider()->ClearCollisions();
		}

		//Instantiate objects
		for (auto object : m_objectsToInstantiate)
		{
			m_objects.emplace_back(object);
		}
		m_objectsToInstantiate.clear();
		for (auto light : m_lightsToInstantiate)
		{
			m_lights.emplace_back(light);
		}
		m_lightsToInstantiate.clear();

		//Destroy objects
		for (auto light : m_lightsToDestroy)
		{
			if (std::find(m_lights.begin(), m_lights.end(), light) != m_lights.end())
				m_lights.erase(std::find(m_lights.begin(), m_lights.end(), light));
		}
		m_lightsToDestroy.clear();
		for (auto object : m_objectsToDestroy)
		{
			if (std::find(m_objects.begin(), m_objects.end(), object) != m_objects.end())
			{
				m_objects.erase(std::find(m_objects.begin(), m_objects.end(), object));
				delete object;
			}
		}
		m_objectsToDestroy.clear();

		glfwSwapBuffers(Program::GetWindow());
		glfwPollEvents();

		if (InputManager::KeyDown(GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(Program::GetWindow(), true);
	}
}

std::pair<std::string, SceneObject*> Scene::RayCast(const glm::vec3& origin, const glm::vec3& direction)
{
	float closestCollision = std::numeric_limits<float>::infinity();
	std::pair<std::string, SceneObject*> closestObject("", nullptr);

	for (auto object : m_objects)
	{
		if (Collider* collider = object->GetCollider())
		{
			glm::vec3 oc = origin - collider->CalculatePosition();
			float a = glm::dot(direction, direction);
			float b = 2.0f * glm::dot(oc, direction);
			float c = glm::dot(oc, oc) - collider->GetRadius() * collider->GetRadius();
			float discriminant = b * b - 4 * a * c;

			if (discriminant >= 0)
			{
				float t = (-b - sqrt(discriminant)) / (2.0f * a);
				if (t >= 0)
				{
					if (t < closestCollision)
					{
						closestCollision = t;
						closestObject = std::make_pair(collider->m_type, object);
					}
				}
			}
		}
	}

	return closestObject;
}

SceneObject* Scene::GetObject(std::string name)
{
	for (auto& object : m_objects)
		if (object->GetName() == name)
			return object;

	return nullptr;
}

std::vector<SceneObject*> Scene::GetAllObjects(std::string name)
{
	std::vector<SceneObject*> objects;
	for (auto& object : m_objects)
		if (object->GetName() == name)
			objects.push_back(object);

	return objects;
}

void Scene::Instantiate(SceneObject* object)
{
	m_objectsToInstantiate.emplace_back(object);
}

void Scene::Destroy(SceneObject* object)
{
	if (std::find(m_objectsToDestroy.begin(), m_objectsToDestroy.end(), object) == m_objectsToDestroy.end())
		m_objectsToDestroy.emplace_back(object);
}

void Scene::AddLight(LightSource* light)
{
	m_objectsToInstantiate.emplace_back(light);
	m_lightsToInstantiate.emplace_back(light);
}

void Scene::DestroyLight(LightSource* light)
{
	if (std::find(m_objectsToDestroy.begin(), m_objectsToDestroy.end(), light) == m_objectsToDestroy.end())
		m_objectsToDestroy.emplace_back(light);
	if (std::find(m_lightsToDestroy.begin(), m_lightsToDestroy.end(), light) == m_lightsToDestroy.end())
		m_lightsToDestroy.emplace_back(light);
}

void Scene::SetPrimaryLight(LightSource* light)
{
	if (light == m_lights[0])
		return;

	auto it = std::find(m_lights.begin(), m_lights.end(), light);

	if (it != m_lights.end())
	{
		std::iter_swap(m_lights.begin(), it);
	}
}

glm::vec3 Scene::Forward()
{
	return glm::vec3(0.0f, 0.0f, 1.0f);
}

glm::vec3 Scene::Right()
{
	return glm::vec3(1.0f, 0.0f, 0.0f);
}

glm::vec3 Scene::Up()
{
	return glm::vec3(0.0f, 1.0f, 0.0f);
}

float Scene::GetDeltaTime()
{
	return m_deltaTime;
}

Camera* Scene::GetCamera()
{
	return m_camera;
}
