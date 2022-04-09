#include "stdafx.h"

#include <Rendering/LowRenderer/Light.h>

Rendering::LowRenderer::Light::Light()
{
    isDirectional = false;
    intensity = 1;
    m_pos = glm::vec3(0, 0, 0);
    m_color = glm::vec3(1, 1, 1);
}
