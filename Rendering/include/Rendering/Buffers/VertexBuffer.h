#pragma once

#include <vector>

#include <GL/glew.h>

#include <Rendering/Export.h>

namespace Rendering::Buffers
{
    class API_RENDERING VertexBuffer
    {
    public:
        VertexBuffer() = delete;
        VertexBuffer(const float*              p_data, const size_t& p_countElements) noexcept;
        VertexBuffer(const std::vector<float>& p_data) noexcept;
        ~VertexBuffer();

        void Bind() const noexcept;
        void Unbind() const noexcept;
        void LoadData(const void* p_data, const GLsizeiptr& p_sizeData);

    private:
        GLuint m_id{0};
    };
}
