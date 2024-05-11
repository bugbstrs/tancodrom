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

std::vector<SceneObject*> Scene::m_objects;
std::vector<SceneObject*> Scene::m_objectsToInstantiate;
std::vector<SceneObject*> Scene::m_objectsToDestroy;
std::vector<LightSource*> Scene::m_lights;
std::unique_ptr<SkyBox> Scene::m_skybox;
Camera* Scene::m_camera;
float Scene::m_deltaTime;

void Scene::Start()
{
	m_camera = new Camera(glm::vec3(0, 2, 0), glm::vec3(1), glm::vec3(0, 0, 0));
	m_objects.push_back(m_camera);

	m_objects.emplace_back(new Tank(glm::vec3(-20, 0, 0), glm::vec3(1), glm::vec3(0, 0, 0)));
	m_objects.emplace_back(new Tank(glm::vec3(-10, 0, 5), glm::vec3(1), glm::vec3(0, 0, 0)));
	m_objects.emplace_back(new Tank(glm::vec3(0, 0, 0), glm::vec3(1), glm::vec3(0, 0, 0)));
	m_objects.emplace_back(new Tank(glm::vec3(10, 0, 5), glm::vec3(1), glm::vec3(0, 0, 0)));

	m_objects.emplace_back(new Terrain(glm::vec3(0, -5.05, 0), glm::vec3(10), glm::vec3(0, 0, 0)));

	m_objects.emplace_back(new Tank(glm::vec3(20, 0, 0), glm::vec3(1), glm::vec3(0, 0, 0)));

	m_objects.push_back(new Helicopter(glm::vec3(20, 15, 0), glm::vec3(0.5), glm::vec3(0, 0, 0)));
	m_objects.push_back(new Helicopter(glm::vec3(0, 15, 0), glm::vec3(0.5), glm::vec3(0, 0, 0)));

	m_objects.emplace_back(new Tank(glm::vec3(-20, 0, 40), glm::vec3(1), glm::vec3(0, 180, 0)));
	m_objects.emplace_back(new Tank(glm::vec3(-10, 0, 35), glm::vec3(1), glm::vec3(0, 180, 0)));
	m_objects.emplace_back(new Tank(glm::vec3(0, 0, 40), glm::vec3(1), glm::vec3(0, 180, 0)));
	m_objects.emplace_back(new Tank(glm::vec3(10, 0, 35), glm::vec3(1), glm::vec3(0, 180, 0)));
	m_objects.emplace_back(new Tank(glm::vec3(20, 0, 40), glm::vec3(1), glm::vec3(0, 180, 0)));

	m_objects.push_back(new Moon(glm::vec3(0, -5, 0), glm::vec3(0.5), glm::vec3(0, 0, 0)));
	//m_lights.push_back((LightSource*)m_objects[m_objects.size() - 1]);
	m_objects.push_back(new Sun(glm::vec3(0, 5, 0), glm::vec3(0.006), glm::vec3(0, 0, 0)));
	m_lights.push_back((LightSource*)m_objects[m_objects.size() - 1]);

	m_objects.push_back(new SkyBox(glm::vec3(0, 0, 0), glm::vec3(1), glm::vec3(0, 0, 0)));

	//Texture skyboxTexture({
	//	"Models/Skybox/right.jpg",
	//	"Models/Skybox/left.jpg",
	//	"Models/Skybox/top.jpg",
	//	"Models/Skybox/bottom.jpg",
	//	"Models/Skybox/front.jpg",
	//	"Models/Skybox/back.jpg"
	//	});

	//m_skybox = std::make_unique<SkyBox>(skyboxTexture);
}

void Scene::Run()
{
	float lastFrame = 0;
	m_deltaTime = 0;

	unsigned int depthMapFBO;
	glGenFramebuffers(1, &depthMapFBO);
	const unsigned int SHADOW_WIDTH = 4096, SHADOW_HEIGHT = 4096;
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

	//Program::m_skyboxShader.Use();
	//Program::m_skyboxShader.SetInt("skybox", 0);

	Program::m_shadowMappingShader.Use();
	Program::m_shadowMappingShader.SetInt("diffuseTexture", 0);
	Program::m_shadowMappingShader.SetInt("shadowMap", 1);

	float hue = 1.0;
	float floorHue = 0.9;

	Start();


	while (true)//TODO:  while (!glfwWindowShouldClose(window)) de preferat in Program.cpp
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
		for (auto light : m_lights) {
			Program::m_shadowMappingDepthShader.Use();
			Program::m_shadowMappingDepthShader.SetMat4("lightSpaceMatrix", light->GetLightSpaceMatrix());

			glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
			glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
			glClear(GL_DEPTH_BUFFER_BIT);

			for (auto object : m_objects)
			{
				object->Render(Program::m_shadowMappingDepthShader);
			}

			glActiveTexture(GL_TEXTURE0);
			glEnable(GL_CULL_FACE);
			glCullFace(GL_FRONT);
			glCullFace(GL_BACK);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		glViewport(0, 0, Program::GetScreenWidth(), Program::GetScreenHeight());
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//randare scena
		Program::m_shadowMappingShader.Use();
		Program::m_shadowMappingShader.SetMat4("projection", m_camera->GetProjectionMatrix());
		Program::m_shadowMappingShader.SetMat4("view", m_camera->GetViewMatrix());
		Program::m_shadowMappingShader.SetFloat("hue", floorHue);

		Program::m_shadowMappingShader.SetVec3("viewPos", m_camera->GetPosition());
		Program::m_shadowMappingShader.SetVec3("lightPos", m_lights[0]->GetPosition());
		Program::m_shadowMappingShader.SetMat4("lightSpaceMatrix", m_lights[0]->GetLightSpaceMatrix());
		glActiveTexture(GL_TEXTURE0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, depthMap);

		for (auto object : m_objects)
		{
			object->Render(Program::m_shadowMappingShader);
		}

		float sunPassingTime = currentFrame * Sun::rotationSpeed;
		m_lights[0]->SetPosition(glm::vec3(0.0f, 20 * sin(sunPassingTime), 50 * cos(sunPassingTime)));
		hue = std::max<float>(sin(sunPassingTime), 0.1);
		floorHue = std::max<float>(sin(sunPassingTime), 0.6);
		
		//Program::m_skyboxShader.Use();
		//Program::m_skyboxShader.SetMat4("projection", m_camera->GetProjectionMatrix());
		//Program::m_skyboxShader.SetMat4("view", glm::mat4(glm::mat3(m_camera->GetViewMatrix())));
		//Program::m_skyboxShader.SetFloat("hue", 1);
		//Program::m_skyboxShader.SetFloat("time", currentFrame);

		//m_skybox->Render(Program::m_skyboxShader);

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

		//Destroy objects
		for (auto object : m_objectsToDestroy)
		{
			if(std::find(m_objects.begin(), m_objects.end(), object) != m_objects.end())
				m_objects.erase(std::find(m_objects.begin(), m_objects.end(), object));
		}
		m_objectsToDestroy.clear();

		glfwSwapBuffers(Program::GetWindow());
		glfwPollEvents();
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
			glm::vec3 colliderPosition = collider->CalculatePosition();

			glm::vec3 toCollider = colliderPosition - origin;
			glm::vec3 colliderDirection = glm::normalize(toCollider);

			float colliderDistance = glm::length(toCollider);
			float dotProduct = glm::dot(colliderDirection, direction);

			if (dotProduct > 0 && colliderDistance > 0)
			{
				float t = glm::dot(colliderDirection, colliderPosition - origin);

				if (t > 0 && t < colliderDistance)
				{
					glm::vec3 collisionPoint = origin + direction * t;

					if (glm::distance(collisionPoint, colliderPosition) <= collider->m_radius)
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
	}

	return closestObject;
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
