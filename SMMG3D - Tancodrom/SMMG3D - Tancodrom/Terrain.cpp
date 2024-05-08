#include "Terrain.h"

Terrain::Terrain(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation):
	SceneObject(position, size, rotation)
{
	SetModel("Models/Terrain/Grass/Grass.obj", false, 5);
}

void Terrain::Update()
{
}
