#include "stdafx.h"

#include <Rendering/Resources/Model.h>
#include <Rendering/Resources/Loaders/MeshLoader.h>
#include <Rendering/Shader/Shader.h>


Rendering::Resources::Model::Model(const std::string& p_filePath)
{
    m_mesh = Rendering::Resources::Loaders::MeshLoader::Load(p_filePath);
}

std::shared_ptr<Rendering::Resources::Mesh> Rendering::Resources::Model::LoadMesh(const char* p_filePath)
{
    return Rendering::Resources::Loaders::MeshLoader::Load(p_filePath);
}
