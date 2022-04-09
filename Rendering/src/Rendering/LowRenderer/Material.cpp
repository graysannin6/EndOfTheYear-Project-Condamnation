#include "stdafx.h"
#include <Rendering/LowRenderer/Material.h>

void Rendering::LowRenderer::Material::LoadTexture(const char* p_filePath)
{
    m_tex.Bind();
    m_tex.Load(p_filePath);
    m_tex.Unbind();
}

void Rendering::LowRenderer::Material::SetTextureActive()
{
    glActiveTexture(m_tex.GetID());
    m_tex.Bind();
}
