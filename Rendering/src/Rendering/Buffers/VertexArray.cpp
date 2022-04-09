#include "stdafx.h"

#include <Rendering/Buffers/VertexArray.h>

using namespace Rendering::Buffers;

VertexArray::VertexArray() noexcept
{
    glCreateVertexArrays(1, &m_id);
}

VertexArray::~VertexArray() noexcept
{
    glDeleteVertexArrays(1, &m_id);
}

void VertexArray::Bind() const noexcept
{
    glBindVertexArray(m_id);
}

void VertexArray::Unbind() const noexcept
{
    glBindVertexArray(0);
}

void VertexArray::AddBuffer(const VertexBuffer& p_buffer,
    const int& p_countElements, const GLType& p_type) noexcept
{
    Bind();
    p_buffer.Bind();

    glEnableVertexAttribArray(m_availableLocation);
    glVertexAttribPointer(m_availableLocation,
                          static_cast<GLint>(p_countElements),
                          static_cast<GLenum>(p_type),
                          GL_FALSE,
                          0,
                          nullptr);

    p_buffer.Unbind();
    Unbind();

    ++m_availableLocation;
}
