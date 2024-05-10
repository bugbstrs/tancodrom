#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "SceneObject.h"
#include "POV.h"

#pragma comment (lib, "glfw3dll.lib")
#pragma comment (lib, "OpenGL32.lib")

class Camera : public SceneObject
{
public:
    Camera(const glm::vec3& position, const glm::vec3& size, const glm::vec3 rotation);

    void Update() override;

    void ProcessInput();
    void SetTank(SceneObject* tank);
    void SetHelicopter(SceneObject* helicopter);

    const glm::mat4 GetViewMatrix() const;
    const glm::mat4 GetProjectionMatrix() const;

    POV GetCameraPOV();

private:
    void Reshape();

    const float m_zNEAR = 0.1f;
    const float m_zFAR = 500.f;
    const float m_cameraSpeedFactor = 25.5f;
    const float m_mouseSensitivity = 50.0f;

    // Perspective properties
    SceneObject* m_tank;
    SceneObject* m_helicopter;
    POV m_pov;

    float m_FOV;
    int m_width;
    int m_height;
};
