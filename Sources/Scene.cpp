#include "Program.h"
#include "Scene.h"
#include "InputManager.h"
#include "Tank.h"
#include "Moon.h"
#include "Sun.h"
#include "Helicopter.h"
#include "Projectile.h"
#include "Terrain.h"

std::vector<SceneObject*> Scene::m_objects;
std::vector<SceneObject*> Scene::m_objectsToInstantiate;
std::vector<SceneObject*> Scene::m_objectsToDestroy;
std::vector<LightSource*> Scene::m_lights;
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
	m_camera->SetTank(m_objects.back());

	m_objects.emplace_back(new Helicopter(glm::vec3(20, 15, 0), glm::vec3(0.5), glm::vec3(-90, 0, 180)));
	m_camera->SetHelicopter(m_objects.back());

	m_objects.emplace_back(new Tank(glm::vec3(-20, 0, 40), glm::vec3(1), glm::vec3(0, 180, 0)));
	m_objects.emplace_back(new Tank(glm::vec3(-10, 0, 35), glm::vec3(1), glm::vec3(0, 180, 0)));
	m_objects.emplace_back(new Tank(glm::vec3(0, 0, 40), glm::vec3(1), glm::vec3(0, 180, 0)));
	m_objects.emplace_back(new Tank(glm::vec3(10, 0, 35), glm::vec3(1), glm::vec3(0, 180, 0)));
	m_objects.emplace_back(new Tank(glm::vec3(20, 0, 40), glm::vec3(1), glm::vec3(0, 180, 0)));

	m_objects.push_back(new Helicopter(glm::vec3(0, 15, 0), glm::vec3(0.5), glm::vec3(-90, 0, 180)));

	m_lights.emplace_back(new LightSource(glm::vec3(5, 21, 5), glm::vec3(1), glm::vec3(0, 0, 0)));
	m_objects.push_back(m_lights[0]);

	m_objects.push_back(new Moon(glm::vec3(0, 5, 0), glm::vec3(0.5), glm::vec3(0, 0, 0)));
	m_objects.push_back(new Sun(glm::vec3(0, -5, 0), glm::vec3(0.006), glm::vec3(0, 0, 0)));
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
	Program::m_shadowMappingShader.Use();
	Program::m_shadowMappingShader.SetInt("diffuseTexture", 0);
	Program::m_shadowMappingShader.SetInt("shadowMap", 1);

	Start();


	while (true)//TODO:  while (!glfwWindowShouldClose(window)) de preferat in Program.cpp
	{
		glClearColor(0.3f, 0.3f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float currentFrame = glfwGetTime();
		m_deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

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
		Program::m_shadowMappingShader.SetFloat("hue", 1);

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

		InputManager::ClearMouseMovement();

		//Instantiate objects
		for (auto object : m_objectsToInstantiate)
		{
			m_objects.emplace_back(object);
		}
		m_objectsToInstantiate.clear();

		//Destroy objects
		for (auto object : m_objectsToDestroy)
		{
			m_objects.erase(std::find(m_objects.begin(), m_objects.end(), object));
		}
		m_objectsToDestroy.clear();

		glfwSwapBuffers(Program::GetWindow());
		glfwPollEvents();
	}
}

void Scene::Instantiate(SceneObject* object)
{
	m_objectsToInstantiate.emplace_back(object);
}

void Scene::Destroy(SceneObject* object)
{
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
