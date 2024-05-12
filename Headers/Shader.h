#pragma once
#include <string>

#include <GL/glew.h>
#include <glm/fwd.hpp>
#include <vector>
#include <string>

class Shader
{
public:

	Shader() = default;
	~Shader();

	void Initialize(const std::string& path);

	void Use() const;

	GLuint GetID() const;

	GLuint modelMatrixLocation;
	GLuint viewMatrixLocation;
	GLuint projMatrixLocation;

	void SetVec3(const std::string& name, const glm::vec3& value) const;
	void SetVec3(const std::string& name, float x, float y, float z) const;
	void SetVec4(const std::string& name, const glm::vec4& value) const;
	void SetMat4(const std::string& name, const glm::mat4& mat) const;
	void SetLightsVec3(const std::string& name, const std::vector<glm::vec3>& vec) const;
	void SetLightsFloat(const std::string& name, const std::vector<float>& vec) const;
	void SetFloat(const std::string& name, float value) const;
	void SetInt(const std::string& name, int value) const;

private:

	void CheckCompileErrors(GLuint shader, const std::string& type);

	GLuint m_ID;

};