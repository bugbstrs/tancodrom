#include "InputManager.h"
#include "Program.h"
#include "Sun.h"
#include "Moon.h"

float InputManager::m_mouseChangedX = 0;
float InputManager::m_mouseChangedY = 0;
float InputManager::m_oldMouseX = 0;
float InputManager::m_oldMouseY = 0;
float InputManager::m_scrollY = 0;
bool InputManager::m_mouseMoved = false;
std::unordered_set<int> InputManager::m_pressedKeys;

bool InputManager::KeyDown(int key)
{
    bool isKeyPressed = glfwGetKey(Program::GetWindow(), key) == GLFW_PRESS;

    if (isKeyPressed && !m_pressedKeys.count(key))
    {
        m_pressedKeys.insert(key);
        return true;
    } else if (!isKeyPressed && m_pressedKeys.count(key))
    {
        m_pressedKeys.erase(key);
    }

    return false;
}

bool InputManager::KeyHold(int key)
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


void InputManager::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (InputManager::KeyDown(GLFW_KEY_P) && action == GLFW_PRESS)
    {
        Sun::rotationSpeed += 0.05f * glfwGetTime();
        Moon::rotationSpeed += 0.05f * glfwGetTime();
    }

    if (InputManager::KeyDown(GLFW_KEY_O) && action == GLFW_PRESS)
    {
        Sun::rotationSpeed -= 0.05f;
        Moon::rotationSpeed -= 0.05f;
    }
}

