#include "stdafx.h"

#include <Rendering/Resources/Mesh.h>

Rendering::Resources::Mesh::Mesh(const std::vector<Geometry::Vertex>& p_vertices,
    const std::vector<uint32_t>& p_indices) noexcept
    : m_vertexCount(static_cast<uint32_t>(p_vertices.size())),
    m_indicesCount(static_cast<uint32_t>(p_indices.size()))
{

    for (const auto& vertex : p_vertices)
    {
        m_positions.push_back(vertex.m_position);
    }

    m_vertexArray = std::make_unique<Buffers::VertexArray>();
    CreateBuffers(p_vertices, p_indices);
}

Rendering::Resources::Mesh::~Mesh()
{
    m_vboPosition.reset();
    m_vboNormal.reset();
    m_vboTextCoords.reset();
}

void Rendering::Resources::Mesh::Bind() const noexcept
{
    m_vertexArray->Bind();
    m_indexBuffer->Bind();
}

void Rendering::Resources::Mesh::Unbind() const noexcept
{
    m_indexBuffer->Unbind();
    m_vertexArray->Unbind();
}

void Rendering::Resources::Mesh::CreateBuffers(const std::vector<Geometry::Vertex>& p_vertices, const std::vector<uint32_t>& p_indices) noexcept
{
    std::vector<float> rawPositions{};
    std::vector<float> rawTextCoords{};
    std::vector<float> rawNormals{};

    for (const auto& vertex : p_vertices)
    {
        // position
        rawPositions.push_back(vertex.m_position[0]);
        rawPositions.push_back(vertex.m_position[1]);
        rawPositions.push_back(vertex.m_position[2]);

        // text coords
        rawTextCoords.push_back(vertex.m_textCoords[0]);
        rawTextCoords.push_back(vertex.m_textCoords[1]);

        // normal
        rawNormals.push_back(vertex.m_normal[0]);
        rawNormals.push_back(vertex.m_normal[1]);
        rawNormals.push_back(vertex.m_normal[2]);
    }

    // buffers gen
    m_vboPosition = std::make_unique<Buffers::VertexBuffer>(rawPositions);
    m_vboTextCoords = std::make_unique<Buffers::VertexBuffer>(rawTextCoords);
    m_vboNormal = std::make_unique<Buffers::VertexBuffer>(rawNormals);
    m_indexBuffer = std::make_unique<Buffers::IndexBuffer>(p_indices);

    // vao configuration
    m_vertexArray->AddBuffer(*m_vboPosition, 3, Buffers::GLType::FLOAT);
    m_vertexArray->AddBuffer(*m_vboTextCoords, 2, Buffers::GLType::FLOAT);
    m_vertexArray->AddBuffer(*m_vboNormal, 3, Buffers::GLType::FLOAT);
}
