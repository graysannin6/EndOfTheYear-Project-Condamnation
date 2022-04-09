#pragma once

#include <Rendering/Resources/Mesh.h>
#include <Rendering/Shader/Shader.h>

#include <Core/GameObject.h>

namespace Core
{
    class MeshManager
    {
    public:
        MeshManager() = default;
        ~MeshManager() = default;

        void AddMesh(const char* p_filePath);
        void AddShader(const char* p_vertPath, const char* p_fragPath);
        void ReloadShader(std::vector<std::shared_ptr<GameObject>>& p_gameObjects);
        void LoadMeshes();
        void LoadShaders();

        std::shared_ptr<Rendering::Resources::Mesh> GetMesh(const int& p_position) const noexcept { return m_meshes[p_position];}
		const std::vector<std::shared_ptr<Rendering::Resources::Mesh>> GetMeshes() const noexcept { return m_meshes;}
		std::shared_ptr<Rendering::Shaders::Shader> GetShader(const int& p_position) const noexcept { return m_shaders[p_position];	}
		const std::vector<std::shared_ptr<Rendering::Shaders::Shader>> GetShaders() const noexcept { return m_shaders;	}

    private:
        std::vector<std::shared_ptr<Rendering::Resources::Mesh>> m_meshes;
        std::vector<std::shared_ptr<Rendering::Shaders::Shader>> m_shaders;
	};

}
