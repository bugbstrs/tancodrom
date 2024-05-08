#pragma once
#include <GL/glew.h>
#include <vector>

#include "Shader.h"
#include "Texture.h"

class SkyBox
{
public:
	SkyBox(Texture texture);

	void Render(Shader& shader);

private:
	static std::vector<float> GetVertices();

	std::vector<float> m_vertices;

	Texture texture;

	unsigned int m_VAO, m_VBO;
};
