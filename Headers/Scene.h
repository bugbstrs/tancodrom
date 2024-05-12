#pragma once

#include <vector>
#include <GLFW/glfw3.h>

#include "LightSource.h"
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

	static std::pair<std::string, SceneObject*> RayCast(const glm::vec3& origin, const glm::vec3& direction);

	static void Instantiate(SceneObject* object);
	static void Destroy(SceneObject* object);

	static void AddLight(LightSource* light);
	static void DestroyLight(LightSource* light);
	static void SetPrimaryLight(LightSource* light);

	static float GetDeltaTime();
	static Camera* GetCamera();

	static glm::vec3 Forward();
	static glm::vec3 Right();
	static glm::vec3 Up();

private:
	static std::vector<SceneObject*> m_objects;
	static std::vector<LightSource*> m_lights;
	static Camera* m_camera;

	static float m_deltaTime;

	static std::unique_ptr<SkyBox> m_skybox;

	static std::vector<SceneObject*> m_objectsToInstantiate;
	static std::vector<LightSource*> m_lightsToInstantiate;
	static std::vector<SceneObject*> m_objectsToDestroy;
	static std::vector<LightSource*> m_lightsToDestroy;
};

