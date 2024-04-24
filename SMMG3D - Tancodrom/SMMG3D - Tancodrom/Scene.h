#pragma once

#include <vector>
#include <GLFW/glfw3.h>

#include "SceneObject.h"
#include "Camera.h"
#include "Shader.h"
#include "Texture.h"
#include "Skybox.h"

#include <memory>

class Scene
{
public:
	static void Start();

	static void Run();

	static void Instantiate(SceneObject* object);

	static float GetDeltaTime();

	static glm::vec3 Forward();
	static glm::vec3 Right();
	static glm::vec3 Up();

	static void LoadObjects();

private:
	static std::vector<SceneObject*> m_objects;
	static Camera* m_camera;

	static float m_deltaTime;

	static std::unique_ptr<SkyBox> m_skybox;
};

