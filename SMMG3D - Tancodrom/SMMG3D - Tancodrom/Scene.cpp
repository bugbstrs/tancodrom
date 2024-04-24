#include "Program.h"
#include "Scene.h"


std::vector<SceneObject*> Scene::m_objects;
Camera* Scene::m_camera;
float Scene::m_deltaTime;

// Texture loading
Texture floorTexture("Skybox\\Floor.png");
Texture skyboxTexture({
	"Skybox\\left.jpg",
	"Skybox\\right.jpg",
	"Skybox\\top.jpg",
	"Skybox\\bottom.jpg",
	"Skybox\\front.jpg",
	"Skybox\\back.jpg"
	});

std::unique_ptr<SkyBox> Scene::m_skybox;;

void Scene::Start()
{
	m_camera = new Camera(glm::vec3(0.5, 0.5, 10), glm::vec3(0, 0, 0));
	m_objects.push_back(m_camera);
}

void Scene::Run()
{
	float lastFrame = 0;
	m_deltaTime = 0;

	Shader skyboxShader("skybox.vs", "skybox.fs");
	skyboxShader.Use();
	skyboxShader.SetInt("skybox", 0);

	float hue = 1.0;
	float floorHue = 0.9;
	float timeAcceleration = 0.1f;

	while (true)//TODO:  while (!glfwWindowShouldClose(window)) de preferat in Program.cpp
	{
		float currentFrame = glfwGetTime();
		m_deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		for (auto object : m_objects)
		{
			object->Update();
		}

		float sunPassingTime = currentFrame * timeAcceleration;
		hue = std::max<float>(sin(sunPassingTime), 0.1);

		glm::mat4 projection = m_camera->GetProjectionMatrix();

		skyboxShader.Use();
		skyboxShader.SetMat4("projection", projection);
		skyboxShader.SetMat4("view", glm::mat4(glm::mat3(m_camera->GetViewMatrix())));
		skyboxShader.SetFloat("hue", hue);
		skyboxShader.SetFloat("time", currentFrame);
		m_skybox->Render(skyboxShader);

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

void Scene::LoadObjects()
{
	// Positions loading
	const float floorSize = 50.0f;
	std::vector<float> floorVertices{
		// positions            // normals           // texcoords
		floorSize, 0.0f,  floorSize,  0.0f, 1.0f, 0.0f,    floorSize,  0.0f,
		-floorSize, 0.0f,  floorSize,  0.0f, 1.0f, 0.0f,    0.0f,  0.0f,
		-floorSize, 0.0f, -floorSize,  0.0f, 1.0f, 0.0f,    0.0f, floorSize,

		floorSize, 0.0f,  floorSize,  0.0f, 1.0f, 0.0f,    floorSize,  0.0f,
		-floorSize, 0.0f, -floorSize,  0.0f, 1.0f, 0.0f,    0.0f, floorSize,
		floorSize, 0.0f, -floorSize,  0.0f, 1.0f, 0.0f,    floorSize, floorSize
	};

	m_skybox = std::make_unique<SkyBox>(SkyBox(skyboxTexture));
}

float Scene::GetDeltaTime()
{
	return m_deltaTime;
}
