#pragma once

#include <iostream>
#include <GL/glew.h>

#include <Rendering/LowRenderer/Camera.h>
#include <Rendering/LowRenderer/Transform.h>
#include <Rendering/LowRenderer/Light.h>
#include <Rendering/LowRenderer/Material.h>
#include <Rendering/Export.h>

namespace Rendering::Shaders
{
	class API_RENDERING Shader
	{

	public:
		Shader();
		~Shader();
        void Unbind();

        GLuint shaderProgram;
		GLint m_data[7];
        
        const char* m_vertPath;
        const char* m_fragPath;

		static GLuint CreateShader(const GLuint& p_type, const std::string& p_source);
        static std::string GetSource(const std::string& p_filePath);
		void Load(const char* p_Shader, const GLuint& p_type, const char* p_pathf, const GLuint& p_typef);
		void Update(const LowRenderer::Camera& cam, const LowRenderer::Transform& trans, const LowRenderer::Material& p_mat, LowRenderer::Light* p_lights, const size_t& p_lightSize);
		void ApplyShader();
	};
}
