#include "InputManager.h"
#include "Program.h"

float InputManager::m_mouseChangedX = 0;
float InputManager::m_mouseChangedY = 0;
float InputManager::m_oldMouseX = 0;
float InputManager::m_oldMouseY = 0;
float InputManager::m_scrollY = 0;
bool InputManager::m_mouseMoved = false;

bool InputManager::KeyDown(int key)
{
    return glfwGetKey(Program::GetWindow(), key) == GLFW_PRESS;
}

bool InputManager::PrimaryClick()
{
    return glfwGetMouseButton(Program::GetWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
}

float InputManager::MouseMoveX()
{
    if (!m_mouseMoved) return 0;
    return m_mouseChangedX;
}

float InputManager::MouseMoveY()
{
    if (!m_mouseMoved) return 0;
    return m_mouseChangedY;
}

float InputManager::ScrollY()
{
    return m_scrollY;
}

void InputManager::MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    m_mouseMoved = true;
    m_mouseChangedX = xpos - m_oldMouseX;
    m_mouseChangedY = m_oldMouseY - ypos;
    m_oldMouseX = xpos;
    m_oldMouseY = ypos;
}

void InputManager::ClearMouseMovement()
{
    m_mouseMoved = false;
}

void InputManager::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    m_scrollY = yoffset;
}
