#include <glm/gtc/quaternion.hpp>

#include "SceneObject.h"
#include <GLFW/glfw3.h>
#include <Scene.h>

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




SceneObject::SceneObject(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation, std::string name) :
    m_position{ position },
    m_size{ size },
    m_rotation{ rotation },
    m_model{ nullptr },
    m_collider{ nullptr },
    m_name{ name }
{}

SceneObject::~SceneObject()
{

}

void SceneObject::SetModel(std::string const& path, bool bSmoothNormals, int modelId)
{
    m_model = new Model(path, bSmoothNormals, modelId);
}

void SceneObject::SetModel(Model* model)
{
    m_model = model;
}

Model* SceneObject::GetModel()
{
    return m_model;
}

Collider* SceneObject::GetCollider()
{
    return m_collider;
}

std::string SceneObject::GetName()
{
    return m_name;
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

void SceneObject::MoveTowards(glm::vec3 point, float speed)
{
    glm::vec3 direction = glm::normalize(point - m_position);
    glm::vec3 displacement = direction * speed;
    float distanceToTarget = glm::distance(point, m_position);

    if (glm::length(displacement) > distanceToTarget)
        m_position = point;
    else
        m_position += displacement;
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

float AngleBetweenVectors(glm::vec3 vec1, glm::vec3 vec2)
{
    vec1 = glm::normalize(vec1);
    vec2 = glm::normalize(vec2);

    float dotProduct = glm::dot(vec1, vec2);

    float angle = glm::acos(dotProduct);

    return glm::degrees(angle);
}

void SceneObject::RotateTowards(glm::vec3 targetPoint, float rotationSpeed)
{
    glm::vec3 targetDirection = glm::normalize(targetPoint - m_position);

    float angleToTarget = AngleBetweenVectors(GetForward(), targetDirection);

    float maxRotation = rotationSpeed;

    if (std::abs(angleToTarget) > maxRotation)
    {
        glm::vec3 rotationAxis = glm::cross(GetForward(), targetDirection);
        float sign = glm::sign(angleToTarget);
        glm::vec3 rotationDirection = rotationAxis * sign;

        Rotate(rotationDirection * maxRotation);
    }
    else
    {
        Rotate(targetDirection * angleToTarget);
    }
}

void SceneObject::RotateAround(glm::vec3 point, float distance, glm::vec3 axis, float speed)
{
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(speed), axis);
    glm::vec4 newPosition = rotationMatrix * glm::vec4(m_position - point, 1.0f);
    newPosition = glm::normalize(newPosition) * distance;

    m_position = glm::vec3(newPosition) + point;
}

void SceneObject::LookAt(glm::vec3 targetPoint, glm::vec3 up)
{
    glm::vec3 direction = glm::normalize(targetPoint - m_position);

    // Calculate rotation around Y axis (yaw)
    float yaw = glm::degrees(atan2(direction.z, direction.x)) - 90.0f;

    // Calculate rotation around X axis (pitch)
    float pitch = glm::degrees(asin(direction.y));

    // Set the new rotation
    glm::vec3 newRotation(-pitch, -yaw, 0);
    SetRotation(newRotation);
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
