#pragma once

#include <vector>

#include <GL/glew.h>

#include <Rendering/Export.h>

namespace Rendering::Buffers
{
    class API_RENDERING IndexBuffer
    {
    public:
        IndexBuffer() = delete;
        IndexBuffer(const uint32_t*              p_data, const size_t& p_countElements) noexcept;
        IndexBuffer(const std::vector<uint32_t>& p_data) noexcept;
        ~IndexBuffer();

        void Bind() const noexcept;
        void Unbind() const noexcept;
        void LoadData(const void* p_data, const GLsizeiptr& p_sizeData);

    private:
        GLuint m_id{0};
    };
}
