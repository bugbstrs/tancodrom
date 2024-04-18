#include "Program.h"
#include "Scene.h"

std::vector<SceneObject*> Scene::m_objects;
Camera* Scene::m_camera;
float Scene::m_deltaTime;

void Scene::Start()
{
	m_camera = new Camera(glm::vec3(0.5, 0.5, 10), glm::vec3(0, 0, 0));
	m_objects.push_back(m_camera);
}

void Scene::Run()
{
	float lastFrame = 0;
	m_deltaTime = 0;

	while (true)//TODO:  while (!glfwWindowShouldClose(window)) de preferat in Program.cpp
	{
		float currentFrame = glfwGetTime();
		m_deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		for (auto object : m_objects)
		{
			object->Update();
		}

		glfwSwapBuffers(Program::GetWindow());
		glfwPollEvents();
	}
}

void Scene::Instantiate(SceneObject* object)
{
	m_objects.push_back(object);
}

glm::vec3 Scene::Forward()
{
	return glm::vec3(0.0f, 0.0f, -1.0f);
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
