#pragma once
#include <GL/glew.h>
#include <vector>

#include "Shader.h"
#include "Texture.h"
#include "SceneObject.h"

class SkyBox : public SceneObject
{
public:
	//SkyBox(Texture texture);

	SkyBox(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation);

	//void Render(Shader& shader);

	void Update() override;

private:
	static std::vector<float> GetVertices();

	std::vector<float> m_vertices;

	//Texture texture;

	unsigned int m_VAO, m_VBO;
};
