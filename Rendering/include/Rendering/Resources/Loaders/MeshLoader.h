#pragma once

#include <Rendering/Export.h>
#include <Rendering/Resources/Mesh.h>

namespace Rendering::Resources::Loaders
{
    class API_RENDERING MeshLoader
    {
    public:
        MeshLoader() = delete;
        ~MeshLoader() = delete;

		static std::shared_ptr<Rendering::Resources::Mesh> Load(const std::string& pfile);
    };
	
}
