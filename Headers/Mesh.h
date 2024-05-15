#pragma once
#include <string>
#include <vector>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Vertex.h"
#include "Texture.h"

using namespace std;

class Mesh
{
public:
    // mesh Data
    unsigned int numVertices;
    std::shared_ptr <Vertex> vertices;

    unsigned int numIndexes;
    std::shared_ptr <unsigned int> indices;
    vector<Texture> textures;
    unsigned int VAO;

    Mesh(const vector<Vertex> &vertices, const vector<unsigned int> &indices, const vector<Texture> &textures);
    Mesh(unsigned int numVertices, std::shared_ptr <Vertex> vertices, unsigned int numIndexes, std::shared_ptr <unsigned int> indices, const vector<Texture> &textures);
    void RenderMesh(Shader &shader, const glm::mat4 &model = glm::mat4(1));

protected:
    void setupMesh();
private:
    // render data 
    unsigned int VBO, EBO;
};