#include "stdafx.h"

#include <Physics/BoxCollider.h>

Physics::Collider::Collider(std::vector<glm::vec3>& p_vec) : m_points( p_vec )
{
    m_modelMat = glm::mat4(1.0f);
    m_pos = glm::vec3(0, 0, 0);
}

void Physics::Collider::SetBoundingBox()
{
    float m_maxX = -10000;
    float m_minX = 10000;
    float m_maxY = -10000;
    float m_minY = 10000;
    float m_maxZ = -10000;
    float m_minZ = 10000;

    for (auto& result : m_points)
    {
        glm::vec4 resultFinal = m_modelMat * glm::vec4(result, 1.0);
        if (resultFinal.x > m_maxX)
            m_maxX = resultFinal.x;

        if (resultFinal.x < m_minX)
            m_minX = resultFinal.x;

        if (resultFinal.y > m_maxY)
            m_maxY = resultFinal.y;

        if (resultFinal.y < m_minY)
            m_minY = resultFinal.y;

        if (resultFinal.z > m_maxZ)
            m_maxZ = resultFinal.z;

        if (resultFinal.z < m_minZ)
            m_minZ = resultFinal.z;
    }

    m_minVectmp = glm::vec4(m_minX, m_minY, m_minZ, 1.0);
    m_maxVectmp = glm::vec4(m_maxX, m_maxY, m_maxZ, 1.0);
}

void Physics::Collider::UpdateBoundingBox()
{
    SetBoundingBox();
    m_maxVec = m_maxVectmp;
    m_minVec = m_minVectmp;
}

void Physics::Collider::PrintBoundingBox() const
{
	std::cout << "maxVec: " << m_maxVec.x << " / " << m_maxVec.y << " / " << m_maxVec.z << '\n';
	std::cout << "minVec: " << m_minVec.x << " / " << m_minVec.y << " / " << m_minVec.z << '\n';
    puts("");
}
