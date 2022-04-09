#pragma once

#include <vector>
#include <memory>

#include <Rendering/Export.h>
#include <Rendering/Geometry/Vertex.h>
#include <Rendering/Buffers/VertexArray.h>
#include <Rendering/Buffers/VertexBuffer.h>
#include <Rendering/Buffers/IndexBuffer.h>

namespace Rendering::Resources
{
    class API_RENDERING Mesh
    {
    public:
        Mesh() noexcept = default;
        Mesh(const std::vector<Geometry::Vertex>& p_vertices,
            const std::vector<uint32_t>& p_indices) noexcept;
        ~Mesh();

        void Bind() const noexcept;
        void Unbind() const noexcept;

        const uint32_t& GetVertexCount() const noexcept { return m_vertexCount;}
		;
        const uint32_t& GetIndicesCount() const noexcept { return m_indicesCount; }

        void CreateBuffers(const std::vector<Geometry::Vertex>& p_vertices,
            const std::vector<uint32_t>& p_indices) noexcept;

        std::vector<glm::vec3> m_positions;

    private:
        const uint32_t m_vertexCount{};
        const uint32_t m_indicesCount{};

        
        std::unique_ptr<Buffers::VertexArray> m_vertexArray;

        std::unique_ptr<Buffers::VertexBuffer> m_vboPosition;
        std::unique_ptr<Buffers::VertexBuffer> m_vboTextCoords;
        std::unique_ptr<Buffers::VertexBuffer> m_vboNormal;

        std::unique_ptr<Buffers::IndexBuffer> m_indexBuffer;
    };
}