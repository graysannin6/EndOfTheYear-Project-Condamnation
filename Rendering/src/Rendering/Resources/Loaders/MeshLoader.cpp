#include "stdafx.h"

#include <string>

#include <../assimp/include/assimp/Importer.hpp>
#include <../assimp/include/assimp/scene.h>
#include <../assimp/include/assimp/postprocess.h>

#include <Rendering/Resources/Loaders/MeshLoader.h>

std::shared_ptr<Rendering::Resources::Mesh> Rendering::Resources::Loaders::MeshLoader::Load(const std::string& pfile)
{

	std::vector<Geometry::Vertex> vertices;
	std::vector<uint32_t> indices;

    int offset = 0;

	Assimp::Importer m_importer;
	const aiScene* m_scene = m_importer.ReadFile(pfile,
        aiProcess_CalcTangentSpace
		| aiProcess_OptimizeMeshes 
		| aiProcess_OptimizeGraph
		| aiProcess_Triangulate
		| aiProcess_SortByPType
		| aiProcess_GenNormals
		| aiProcess_FixInfacingNormals 
		| aiProcess_GenUVCoords
        | aiProcess_FlipUVs
		);

    assert(m_scene != nullptr);

    if (m_scene == nullptr)
    {
        puts("Mesh Path error");
        return nullptr;
    }
    //Load Meshes
	for (unsigned int i = 0; i < m_scene->mNumMeshes; ++i)
	{
		aiMesh* t_mesh = m_scene->mMeshes[i];

        //Load Vertices
		for (unsigned int vertIdx = 0u; vertIdx < t_mesh->mNumVertices; vertIdx++)
		{
			Geometry::Vertex vertex;

			aiVector3D vert = t_mesh->mVertices[vertIdx];
			aiVector3D norm = t_mesh->mNormals[vertIdx];

			if (t_mesh->HasTextureCoords(0))
			{
				aiVector3D UV = t_mesh->mTextureCoords[0][vertIdx];
				vertex.m_textCoords = glm::vec2(UV.x, UV.y);
			}

            vertex.m_position = glm::vec3(vert.x, vert.y , vert.z);
			vertex.m_normal = glm::vec3(norm.x, norm.y , norm.z );

			vertices.push_back(vertex);
		} 
        //Load Indices
		for (unsigned int faceIdx = 0; faceIdx < t_mesh->mNumFaces; faceIdx++)
		{
			if (t_mesh->mFaces[faceIdx].mNumIndices == 3)
			{
				indices.push_back(t_mesh->mFaces[faceIdx].mIndices[0] + offset);
				indices.push_back(t_mesh->mFaces[faceIdx].mIndices[1] + offset);
				indices.push_back(t_mesh->mFaces[faceIdx].mIndices[2] + offset);
			}
		}
        offset += t_mesh->mNumVertices;
	}
    return std::shared_ptr<Mesh>(new Mesh{vertices, indices});
}