#pragma once

#include <glm/glm.hpp>

#include <Rendering/Export.h>

namespace Rendering::Geometry
{
    struct API_RENDERING Vertex
    {
        Vertex() = default;

        Vertex(const glm::vec3& p_position, const glm::vec2& p_textCoords, const glm::vec3& p_normal) :
            m_position{p_position}, m_textCoords{p_textCoords}, m_normal{p_normal} {}

        glm::vec3 m_position{};
        glm::vec2 m_textCoords{};
        glm::vec3 m_normal{};
    };
}

