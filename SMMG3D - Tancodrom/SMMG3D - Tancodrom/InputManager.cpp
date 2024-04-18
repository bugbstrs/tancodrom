#include "InputManager.h"
#include "Program.h"

bool InputManager::KeyDown(int key)
{
    return glfwGetKey(Program::GetWindow(), key) == GLFW_PRESS;
}
