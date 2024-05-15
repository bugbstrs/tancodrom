#pragma once
#include <string>
#include <vector>

struct Texture
{
    unsigned int id;
    std::string type;
    std::string path;

    Texture() = default;
    Texture(const std::string &strTexturePath);
    Texture(std::vector<std::string> faces);
};