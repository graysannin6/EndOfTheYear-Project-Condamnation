#pragma once

#include <iostream>

#include <Rendering/Export.h>
#include <Rendering/Shader/Shader.h>

namespace Rendering::Resources::Loaders
{
	class API_RENDERING ShaderLoader
	{
	public:
		ShaderLoader();
		~ShaderLoader();

		static std::shared_ptr<Shaders::Shader> LoadShader(const char* p_shaderPath, const char* p_shaderPathB);
	};
}
