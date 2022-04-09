#pragma once

#include <memory>

#include <Rendering/Export.h>
#include <Rendering/LowRenderer/Camera.h>
#include <Rendering/Managers/InputManager.h>

namespace Rendering::Managers
{
    class API_RENDERING CameraManager
    {
    public:
        CameraManager(const glm::vec3& p_position = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& p_up = glm::vec3(0.0f, 1.0f, 0.0f), const float& p_yaw = -90.0f, const float& p_pitch = 0, bool p_freeFloat = true);
        CameraManager(const float& p_posX, const float& p_posY, const float& p_posZ, const float& p_upX, const float& p_upY, const float& p_upZ, const float& p_yaw, const float& p_pitch);

        void Init(const glm::vec3& p_position, const glm::vec3& p_up, const float& p_yaw, const float& p_pitch);

        void ProcessKeyInput(const float& p_deltaTime);
        void ProcessMouseInput();
        void MoveCamera(const glm::vec3& p_direction) const;

		std::shared_ptr<LowRenderer::Camera> GetCamera() const noexcept { return m_camera; }

    private:
		bool m_freeFloat;
		std::shared_ptr<LowRenderer::Camera> m_camera{};

        float m_lastX = 1920 / 2;
        float m_lastY = 1080 / 2;
    };
}
