#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Rendering/Export.h>

namespace Rendering::LowRenderer
{
    class API_RENDERING Transform
    {
    public:
		Transform();
		~Transform() = default;

        void Translate(const glm::vec3& p_translation);
        void Rotate(const glm::vec3& p_rotation);
        void Scale(const glm::vec3& p_scaling);

		glm::vec3 GetPosition() const noexcept { return glm::vec3(m_transMat[3].x, m_transMat[3].y, m_transMat[3].z); };
		const glm::vec3& GetRawPosition() const noexcept { return m_pos; };
        const glm::vec3& GetRotation() const noexcept { return m_rot; };
        const glm::mat4& GetTransMat() const noexcept { return m_transMat; };
        const glm::vec3& GetScale() const noexcept { return m_scale; };
        
        void SetPosition(const glm::vec3 & p_pos);
        void SetTransMat(const glm::mat4& p_transMat) noexcept { m_transMat = p_transMat; };

    private:
        glm::vec3 m_pos;
        glm::vec3 m_rot;
        glm::vec3 m_scale;
        glm::mat4 m_transMat;
    };
}