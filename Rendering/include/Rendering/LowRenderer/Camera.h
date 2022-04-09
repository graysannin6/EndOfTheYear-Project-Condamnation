#pragma once

#include <glm/gtc/matrix_transform.hpp>

#include <Rendering/Export.h>

namespace Rendering::LowRenderer
{
    class API_RENDERING Camera
    {
    public:
        //constructor with vector
        Camera(const glm::vec3& p_position = glm::vec3(0.0f, 0.0f, 0.0f),
               const glm::vec3& p_up       = glm::vec3(0.0f, 1.0f, 0.0f),
               const float&     p_yaw      = -90.0f,
               const float&     p_pitch    = 0.0f);
        Camera(const float&     p_posX, const float& p_posY, const float& p_posZ,
               const float&     p_upX,
               const float&     p_upY, const float& p_upZ, const float& p_yaw,
               const float&     p_pitch);

        glm::mat4 GetViewMatrix() const noexcept
        {
            return lookAt(m_position, m_position + m_front, m_up);
        };

        static glm::mat4 GetPerspectiveMatrix() noexcept
        {
            return glm::perspective(45.0f, 16.0f / 9.0f, 0.1f, 1000000.0f);
        };

        void UpdateCameraVectors();

        enum Camera_Movement
        {
            FORWRARD,
            BACKWARD,
            LEFT,
            RIGHT
        };

		const glm::vec3& GetPosition() const noexcept { return m_position; }
		const glm::vec3& GetFront() const noexcept { return m_front; }
		const glm::vec3& GetUp() const noexcept { return m_up; }
		const glm::vec3& GetRight() const noexcept { return m_right; }
		const glm::vec3& GetWorldUp() const noexcept { return m_worldUp; }
		const glm::mat4& GetMatrix() const noexcept { return m_matrix; }

		const float& GetYaw() const noexcept { return m_yaw; }
		const float& GetPitch() const noexcept { return m_pitch; }

		const float& GetMovementSpeed() const noexcept { return m_movementSpeed; }
		const float& GetMouseSensitivity() const noexcept { return m_mouseSensitivity; }
		const float& GetZoom() const noexcept { return m_zoom; }

		void SetPosition(const glm::vec3& p_position) { m_position = p_position; }
		void SetYaw(const float& p_yaw) { m_yaw = p_yaw; }
		void SetPitch(const float& p_pitch) { m_pitch = p_pitch; }
        
    private:
        //camera attriutes
        glm::vec3 m_position{};
        glm::vec3 m_front{};
        glm::vec3 m_up{};
        glm::vec3 m_right{};
        glm::vec3 m_worldUp{};
        glm::mat4 m_matrix{};
        //euler angles
        float m_yaw{-90.0f};
        float m_pitch{0.0f};

        //camera option
        float m_movementSpeed{0.5f};
        float m_mouseSensitivity{0.05f};
        float m_zoom{45.0f};

    };
}
