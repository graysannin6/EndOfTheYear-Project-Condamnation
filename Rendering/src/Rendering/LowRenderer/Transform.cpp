#include "stdafx.h"
#include <Rendering/LowRenderer/Transform.h>

using namespace Rendering::LowRenderer;

Transform::Transform()
{
	m_pos = glm::vec3(0, 0, 0);
	m_rot = glm::vec3(0, 0, 0);
	m_scale = glm::vec3(1, 1, 1);
	m_transMat = glm::mat4(1.0f);
	m_transMat = glm::translate(m_transMat, glm::vec3(0, 0, 0));
}

void Transform::Translate(const glm::vec3& p_translation)
{
    m_pos += p_translation;
    m_transMat = glm::translate(m_transMat, p_translation);
}

void Transform::Rotate(const glm::vec3& p_rotation)
{
    m_rot = p_rotation;
    m_transMat = glm::rotate(m_transMat, glm::radians(p_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    m_transMat = glm::rotate(m_transMat, glm::radians(p_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    m_transMat = glm::rotate(m_transMat, glm::radians(p_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Transform::Scale(const glm::vec3& p_scaling)
{
    m_scale = p_scaling;
    m_transMat = glm::scale(m_transMat, p_scaling);
}

void Transform::SetPosition(const glm::vec3 & p_pos)
{
    m_pos = p_pos;
	m_transMat[3] = glm::vec4(p_pos, 1.0f);
}
