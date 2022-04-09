#include "stdafx.h"

#include <Rendering/Resources/Loaders/ShaderLoader.h>
#include <Rendering/Shader/Shader.h>

std::shared_ptr<Rendering::Shaders::Shader> Rendering::Resources::Loaders::ShaderLoader::LoadShader(const char* p_shaderPath, const char* p_shaderPathB)
{
	std::shared_ptr<Shaders::Shader> m_shader = std::make_shared<Shaders::Shader>();
    m_shader->m_vertPath = p_shaderPath;
    m_shader->m_fragPath = p_shaderPathB;

	m_shader->Load(p_shaderPath, GL_VERTEX_SHADER, p_shaderPathB, GL_FRAGMENT_SHADER);

	return m_shader;
}
