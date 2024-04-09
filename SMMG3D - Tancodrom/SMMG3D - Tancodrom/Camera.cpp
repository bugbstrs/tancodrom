#include "Camera.h"

#include <GL/glew.h>
#pragma comment (lib, "glew32.lib")

Camera::Camera(const int width, const int height, const glm::vec3& position)
{
    startPosition = position;
    Set(width, height, position);
}

void Camera::Set(const int width, const int height, const glm::vec3& position)
{
    this->isPerspective = true;
    this->yaw = YAW;
    this->pitch = PITCH;

    this->FoVy = FOV;
    this->width = width;
    this->height = height;
    this->zNear = zNEAR;
    this->zFar = zFAR;

    this->worldUp = glm::vec3(0, 1, 0);
    this->position = position;

    lastX = width / 2.0f;
    lastY = height / 2.0f;
    bFirstMouseMove = true;

    UpdateCameraVectors();
}

void Camera::Reset(const int width, const int height)
{
    Set(width, height, startPosition);
}

void Camera::Reshape(int windowWidth, int windowHeight)
{
    width = windowWidth;
    height = windowHeight;

    // define the viewport transformation
    glViewport(0, 0, windowWidth, windowHeight);
}

const glm::mat4 Camera::GetViewMatrix() const
{
    // Returns the View Matrix
    return glm::lookAt(position, position + forward, up);
}

const glm::vec3 Camera::GetPosition() const
{
    return position;
}

const glm::mat4 Camera::GetProjectionMatrix() const
{
    glm::mat4 Proj = glm::mat4(1);
    if (isPerspective)
    {
        float aspectRatio = ((float)(width)) / height;
        Proj = glm::perspective(glm::radians(FoVy), aspectRatio, zNear, zFar);
    }
    else
    {
        float scaleFactor = 2000.f;
        Proj = glm::ortho<float>(
            -width / scaleFactor, width / scaleFactor,
            -height / scaleFactor, height / scaleFactor, -zFar, zFar);
    }
    return Proj;
}

void Camera::ProcessInput(ECameraMovementType direction, float deltaTime)
{
    float velocity = (float)(cameraSpeedFactor * deltaTime);
    switch (direction)
    {
    case ECameraMovementType::FORWARD:
        position += forward * velocity;
        break;
    case ECameraMovementType::BACKWARD:
        position -= forward * velocity;
        break;
    case ECameraMovementType::LEFT:
        position -= right * velocity;
        break;
    case ECameraMovementType::RIGHT:
        position += right * velocity;
        break;
    case ECameraMovementType::UP:
        position += up * velocity;
        break;
    case ECameraMovementType::DOWN:
        position -= up * velocity;
        break;
    }
}

void Camera::MouseControl(float xPos, float yPos)
{
    if (bFirstMouseMove)
    {
        lastX = xPos;
        lastY = yPos;
        bFirstMouseMove = false;
    }

    float xChange = xPos - lastX;
    float yChange = lastY - yPos;
    lastX = xPos;
    lastY = yPos;

    if (fabs(xChange) <= 1e-6 && fabs(yChange) <= 1e-6)
    {
        return;
    }
    xChange *= mouseSensitivity;
    yChange *= mouseSensitivity;

    ProcessMouseMovement(xChange, yChange);
}

void Camera::ProcessMouseScroll(float yOffset)
{
    if (FoVy >= 1.0f && FoVy <= 90.0f)
    {
        FoVy -= yOffset;
    }
    if (FoVy <= 1.0f)
        FoVy = 1.0f;
    if (FoVy >= 90.0f)
        FoVy = 90.0f;
}

void Camera::ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch)
{
    yaw += xOffset;
    pitch += yOffset;

    // Avem grijã sã nu ne dãm peste cap
    if (constrainPitch)
    {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    // Se modificã vectorii camerei pe baza unghiurilor Euler
    UpdateCameraVectors();
}

void Camera::UpdateCameraVectors()
{
    // Calculate the new forward vector
    this->forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->forward.y = sin(glm::radians(pitch));
    this->forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->forward = glm::normalize(this->forward);
    // Also re-calculate the Right and Up vector
    right = glm::normalize(glm::cross(forward, worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    up = glm::normalize(glm::cross(right, forward));
}