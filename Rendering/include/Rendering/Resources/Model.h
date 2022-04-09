#pragma once

#include <Rendering/Export.h>
#include <Rendering/Resources/Mesh.h>
#include <Rendering/Shader/Shader.h>

#include <memory>

namespace Rendering::Resources
{
    class API_RENDERING Model
    {
    public:
		Model() = default;
        Model(const std::string& p_filePath);
        ~Model() = default;

		static std::shared_ptr<Mesh> LoadMesh(const char* p_filePath);

        std::shared_ptr<Shaders::Shader> GetShader() const noexcept { return m_shader; };
		void SetShader(std::shared_ptr<Shaders::Shader> p_shader) { m_shader = p_shader; };

        std::shared_ptr<Mesh> GetMesh() const noexcept
        {
            if (m_mesh != nullptr)
                return m_mesh;
            return {};
        }

		void SetMesh(std::shared_ptr<Mesh> p_mesh) { m_mesh = p_mesh; };
    
    private:
        std::shared_ptr<Mesh> m_mesh{};
		std::shared_ptr<Shaders::Shader> m_shader{};
    };
}
