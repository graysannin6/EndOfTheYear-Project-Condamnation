#include "stdafx.h"

#include <Rendering/Buffers/IndexBuffer.h>

using namespace Rendering::Buffers;

IndexBuffer::IndexBuffer(const uint32_t* p_data, const size_t& p_countElements) noexcept
{
    glGenBuffers(1, &m_id);
    Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 p_countElements * sizeof(uint32_t),
                 p_data,
                 GL_STATIC_DRAW);
}

IndexBuffer::IndexBuffer(const std::vector<uint32_t>& p_data) noexcept : IndexBuffer(p_data.data(),
                                                                                     p_data.size())
{
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_id);
}

void IndexBuffer::Bind() const noexcept
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void IndexBuffer::Unbind() const noexcept
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::LoadData(const void* p_data, const GLsizeiptr& p_sizeData)
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 p_sizeData,
                 p_data,
                 GL_STATIC_DRAW);
}
