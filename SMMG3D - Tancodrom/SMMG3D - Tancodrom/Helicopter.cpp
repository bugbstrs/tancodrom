#include "Helicopter.h"

std::vector<Texture> Helicopter::textures;

Helicopter::Helicopter(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation) :
    SceneObject(position, size, rotation)
{
    SetModel("Models/Helicopters/uh60.dae", false, 2);

    textures.emplace_back(Texture("Models/Helicopter/fuselage"));
    textures.emplace_back(Texture("Models/Helicopter/land"));
    textures.emplace_back(Texture("Models/Helicopter/pal"));
    textures.emplace_back(Texture("Models/Helicopter/panel"));
    textures.emplace_back(Texture("Models/Helicopter/plt"));
}

void Helicopter::Update()
{

}
