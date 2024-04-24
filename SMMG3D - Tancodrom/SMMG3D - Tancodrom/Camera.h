#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "SceneObject.h"

#pragma comment (lib, "glfw3dll.lib")
#pragma comment (lib, "OpenGL32.lib")

class Camera : public SceneObject
{
public:
    Camera(const glm::vec3& position, const glm::vec3 rotation);

    void Update() override;

    void ProcessInput();
    void MouseControl(float xPos, float yPos);
    void ProcessMouseScroll(float yOffset);
    void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);

    const glm::mat4 GetViewMatrix() const;
    const glm::mat4 GetProjectionMatrix() const;

private:
    void Reshape();

    const float m_zNEAR = 0.1f;
    const float m_zFAR = 500.f;
    const float cameraSpeedFactor = 2.5f;
    const float mouseSensitivity = 2.5f;

    // Perspective properties
    float m_FOV;
    int m_width;
    int m_height;

    bool m_bFirstMouseMove = true;
    float m_lastX = 0.f;
    float m_lastY = 0.f;

    GLuint ProjMatrixLocation;
    GLuint ViewMatrixLocation;
};
