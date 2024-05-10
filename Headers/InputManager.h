#pragma once
#include <unordered_set>

#include "Program.h"
#include "Scene.h"

class InputManager
{
public:
	static bool KeyDown(int key);//ex key: GLFW_KEY_W
	static bool KeyHold(int key);//ex key: GLFW_KEY_W

	static bool PrimaryClick();

	static float MouseMoveX();
	static float MouseMoveY();

	static float ScrollY();

private:
	static std::unordered_set<int> m_pressedKeys;

	static float m_mouseChangedX;
	static float m_mouseChangedY;
	static float m_oldMouseX;
	static float m_oldMouseY;
	static bool  m_mouseMoved;

	static float m_scrollY;

	static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
	static void ClearMouseMovement();
	static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

	friend class Program;
	friend class Scene;
};

