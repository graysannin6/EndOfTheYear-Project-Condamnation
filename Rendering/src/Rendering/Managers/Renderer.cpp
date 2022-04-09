#include "stdafx.h"

#include <Rendering/Managers/Renderer.h>

void Rendering::Managers::Renderer::Clear() const noexcept
{
    m_driver->Clear();
}

void Rendering::Managers::Renderer::PolygoneModeLine() const noexcept
{
    m_driver->PolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Rendering::Managers::Renderer::PolygoneModeFill() const noexcept
{
    m_driver->PolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Rendering::Managers::Renderer::SetupCulling()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void Rendering::Managers::Renderer::Draw(const Resources::Mesh& m_mesh) const noexcept
{
    m_mesh.Bind();

    if (m_mesh.GetIndicesCount() > 0)
    {
        glDrawElements(GL_TRIANGLES, m_mesh.GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
    }
    else
        glDrawArrays(GL_TRIANGLES, 0, m_mesh.GetVertexCount());

    m_mesh.Unbind();
}