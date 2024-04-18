#include <glm/gtc/quaternion.hpp>

#include "SceneObject.h"

glm::vec3 SceneObject::GetPosition() const
{
    return m_position;
}

void SceneObject::SetPosition(glm::vec3 position)
{
    m_position = position;
}

void SceneObject::Move(glm::vec3 direction, bool globalCoordonates)
{
    if (globalCoordonates)
    {
        m_position += direction;
        return;
    }

    glm::vec3 localDirection = glm::vec3(glm::dot(direction, GetRight()),
        glm::dot(direction, GetUp()),
        glm::dot(direction, GetForward()));

    m_position += localDirection;
}

glm::vec3 SceneObject::GetRotation() const
{
    return m_rotation;
}

glm::vec3 SceneObject::GetForward() const
{
    glm::mat4 rotationMatrix = glm::mat4_cast(glm::quat(glm::radians(m_rotation)));

    glm::vec3 forward = glm::vec3(rotationMatrix * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f));

    return glm::normalize(forward);
}

glm::vec3 SceneObject::GetRight() const
{
    glm::mat4 rotationMatrix = glm::mat4_cast(glm::quat(glm::radians(m_rotation)));

    glm::vec3 right = glm::vec3(rotationMatrix * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));

    return glm::normalize(right);
}

glm::vec3 SceneObject::GetUp() const
{
    glm::mat4 rotationMatrix = glm::mat4_cast(glm::quat(glm::radians(m_rotation)));

    glm::vec3 up = glm::vec3(rotationMatrix * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));

    return glm::normalize(up);
}

void SceneObject::SetRotation(glm::vec3 rotation)
{
    m_rotation = rotation;

    NormalizeRotation();
}

void SceneObject::Rotate(glm::vec3 direction)
{
    direction = glm::radians(direction);

    glm::quat rotation = glm::quat(direction);

    m_rotation = glm::eulerAngles(rotation);

    NormalizeRotation();
}

glm::vec3 SceneObject::GetSize() const
{
    return m_size;
}

void SceneObject::SetSize(glm::vec3 size)
{
    m_size = size;
}

void SceneObject::NormalizeRotation()
{
    m_rotation.x = fmod(m_rotation.x, 360.0f);
    m_rotation.y = fmod(m_rotation.y, 360.0f);
    m_rotation.z = fmod(m_rotation.z, 360.0f);

    if (m_rotation.x < 0) m_rotation.x += 360.0f;
    if (m_rotation.y < 0) m_rotation.y += 360.0f;
    if (m_rotation.z < 0) m_rotation.z += 360.0f;
}
