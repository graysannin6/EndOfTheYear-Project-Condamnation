#pragma once

#include <Rendering/Export.h>
#include <glm/glm.hpp>

namespace Rendering::LowRenderer
{
    class API_RENDERING Light
    {
    public:
        Light();
        ~Light() = default;

		const glm::vec3& GetPos() const noexcept { return m_pos; }
		const glm::vec3& GetColor() const noexcept { return m_color; }
		const float& GetIntensity() const noexcept { return intensity; }
		const bool& GetIsDirectional() const noexcept { return isDirectional; }
		void SetPos(const glm::vec3& p_pos) { m_pos = p_pos; }
		void SetPos(const float& p_x, const float& p_y, const float& p_z) { m_pos = glm::vec3{ p_x,p_y,p_z }; }
		void SetColor(const float& p_r, const float& p_g, const float& p_b) { m_color = glm::vec3{ p_r,p_g,p_b }; }
		void SetIntensity(const float& p_intensity) { intensity = p_intensity; }
		void SetDirectional(const float& p_isDirectional) { intensity = p_isDirectional; }
        
    private:
        glm::vec3 m_pos{};
        glm::vec3 m_color{};
		float intensity{ 0.0f };
		bool isDirectional{ false };
    };
}

