#pragma once
#include <string>
#include <Vector>

struct Texture
{
    unsigned int id;
    std::string type;
    std::string path;

    Texture() = default;
    Texture(const std::string &strTexturePath);
    Texture(const std::vector<std::string>& faces);
};