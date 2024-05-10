#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

class Program
{
public:
	Program() = delete;

	static void Run();

	static GLuint GetProgramID();

	static GLFWwindow* GetWindow();

	static unsigned int GetScreenWidth();
	static unsigned int GetScreenHeight();

	static Shader m_shadowMappingShader;
	static Shader m_shadowMappingDepthShader;
	static Shader m_skyboxShader;

private:
	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	static void Initialize();
	static void CreateShaders();

	static GLuint m_programId;
	static GLFWwindow* m_window;

	static unsigned int m_screenWidth;
	static unsigned int m_screenHeight;
};

