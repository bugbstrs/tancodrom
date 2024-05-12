#include <glm/gtc/quaternion.hpp>

#include "SceneObject.h"
#include <GLFW/glfw3.h>

Collider::Collider(const glm::vec3& position, float radius, const std::string& type, glm::vec3& objPosition, glm::vec3& objRotation) :
    m_radius(radius),
    m_type(type),
    m_position(position),
    m_objectPosition(objPosition),
    m_objectRotation(objRotation)
{}

std::vector<std::pair<std::string, SceneObject*>> Collider::GetCollisions()
{
    return m_collisions;
}

float Collider::GetRadius()
{
    return m_radius;
}

void Collider::ClearCollisions()
{
    m_collisions.clear();
}

void Collider::CheckCollisions(SceneObject* object1, SceneObject* object2)
{
    Collider* collider1 = object1->GetCollider();
    Collider* collider2 = object2->GetCollider();

    if (collider1 == nullptr || collider2 == nullptr)
    {
        return;
    }

    float distance = glm::distance(collider1->CalculatePosition(), collider2->CalculatePosition());

    if (distance < collider1->m_radius + collider2->m_radius)
    {
        collider1->m_collisions.push_back(std::make_pair(collider2->m_type, object2));
        collider2->m_collisions.push_back(std::make_pair(collider1->m_type, object1));
    }
}

void Collider::ResolveCollision(SceneObject* object1, SceneObject* object2)
{
    glm::vec3 direction(object1->GetPosition() - object2->GetPosition());
    direction = glm::normalize(direction);
    float collidersRadious = object1->GetCollider()->GetRadius() + object2->GetCollider()->GetRadius();
    float distance = glm::distance(object1->GetPosition(), object2->GetPosition());
    object1->Move(direction * ((collidersRadious - distance) / 2));
    object2->Move(-direction * ((collidersRadious - distance) / 2));
}

glm::vec3 Collider::CalculatePosition()
{
    glm::mat4 rotationMatrix = glm::mat4(1.0f);
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(m_objectRotation.x), glm::vec3(1, 0, 0));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(m_objectRotation.y), glm::vec3(0, 1, 0));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(m_objectRotation.z), glm::vec3(0, 0, 1));

    glm::vec4 rotatedPosition = rotationMatrix * glm::vec4(m_position, 1.0f);
    glm::vec3 rotatedPosition3 = glm::vec3(rotatedPosition);

    return m_objectPosition + rotatedPosition3;
}




SceneObject::SceneObject(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation) :
    m_position{ position },
    m_size{ size },
    m_rotation{ rotation },
    m_model{ nullptr },
    m_collider{ nullptr }
{}

void SceneObject::SetModel(std::string const& path, bool bSmoothNormals, int modelId)
{
    m_model = new Model(path, bSmoothNormals, modelId);
}

Collider* SceneObject::GetCollider()
{
    return m_collider;
}

glm::vec3 SceneObject::GetPosition() const
{
    return m_position;
}

void SceneObject::SetPosition(glm::vec3 position)
{
    m_position = position;
}

void SceneObject::Move(glm::vec3 direction)
{
    m_position += direction;
}

glm::vec3 SceneObject::GetRotation() const
{
    return m_rotation;
}

glm::vec3 SceneObject::GetForward() const
{
    glm::mat4 rotationMatrix = glm::mat4_cast(glm::quat(glm::radians(m_rotation)));

    glm::vec3 forward = glm::vec3(rotationMatrix * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));

    return glm::normalize(forward);
}

glm::vec3 SceneObject::GetRight() const
{
    glm::mat4 rotationMatrix = glm::mat4_cast(glm::quat(glm::radians(m_rotation)));

    glm::vec3 right = glm::vec3(rotationMatrix * glm::vec4(-1.0f, 0.0f, 0.0f, 0.0f));

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
    m_rotation += direction;

    NormalizeRotation();
}

void SceneObject::RotateAround(glm::vec3 point, float distance, glm::vec3 axis, float speed)
{
    float angle = speed;

    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, axis);
    glm::vec4 newPosition = rotationMatrix * glm::vec4(m_position - point, 1.0f);
    newPosition = glm::normalize(newPosition) * distance;

    m_position = glm::vec3(newPosition) + point;

    m_rotation += angle * glm::degrees(axis);
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
}

void SceneObject::Render(Shader& shader)
{
    if (!m_model)
        return;
    glm::mat4 modelTransform(1.0f);
    modelTransform = glm::translate(modelTransform, m_position);
    modelTransform = glm::rotate(modelTransform, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    modelTransform = glm::rotate(modelTransform, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelTransform = glm::rotate(modelTransform, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    modelTransform = glm::scale(modelTransform, m_size);
    m_model->RenderModel(shader, modelTransform);
}
