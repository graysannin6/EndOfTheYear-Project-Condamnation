#include "stdafx.h"

#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include <Rendering/Shader/Shader.h>

Rendering::Shaders::Shader::Shader()
{
	shaderProgram = glCreateProgram();
}

Rendering::Shaders::Shader::~Shader()
{
	glDeleteProgram(shaderProgram);
}

void Rendering::Shaders::Shader::Unbind()
{
    glUseProgram(0);
}

GLuint Rendering::Shaders::Shader::CreateShader(const GLuint & p_type, const std::string & p_source)
{

	const char* m_shaderSource = p_source.c_str();
	GLuint m_shaderID = glCreateShader(p_type);

	glShaderSource(m_shaderID, 1, &m_shaderSource, nullptr);
	glCompileShader(m_shaderID);

	int success;
	char infoLog[512];
	glGetShaderInfoLog(m_shaderID, 512, nullptr, infoLog);
	glGetShaderiv(m_shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		std::cout << "Error, shader compilation failed\n" << infoLog << std::endl;
	}

	return m_shaderID;
}

std::string Rendering::Shaders::Shader::GetSource(const std::string& p_filePath)
{
	std::string code;
	std::ifstream file;
	std::stringstream dataStream;

	try
	{
		file.open(p_filePath);
		dataStream << file.rdbuf();
		code = dataStream.str();
		file.close();
	}
	catch (std::ifstream::failure& exception)
	{
		std::cout << "Issue occured with specified file\n";
		std::cout << exception.what() << '\n';

	}

    return code;
}

void Rendering::Shaders::Shader::Load(const char* p_Shader, const GLuint& p_type, const char* p_pathf, const GLuint& p_typef)
{
	GLuint m_shaderTypeID = CreateShader(p_type, GetSource(p_Shader));
	GLuint m_shaderTypeIDA = CreateShader(p_typef, GetSource(p_pathf));

	glAttachShader(shaderProgram, m_shaderTypeID);
	glAttachShader(shaderProgram, m_shaderTypeIDA);

	glLinkProgram(shaderProgram);

	glDeleteShader(m_shaderTypeID);
	glDeleteShader(m_shaderTypeIDA);

	m_data[0] = glGetUniformLocation(shaderProgram, "ProjectionMatrix");
	m_data[1] = glGetUniformLocation(shaderProgram, "CameraMatrix");
	m_data[2] = glGetUniformLocation(shaderProgram, "ModelMatrix");
	m_data[3] = glGetUniformLocation(shaderProgram, "viewPos");
	m_data[4] = glGetUniformLocation(shaderProgram, "objColor");
	m_data[5] = glGetUniformLocation(shaderProgram, "objShininess");
	m_data[6] = glGetUniformLocation(shaderProgram, "objOpacity");

}

void Rendering::Shaders::Shader::Update(const LowRenderer::Camera& cam, const LowRenderer::Transform& trans, const LowRenderer::Material& p_mat, LowRenderer::Light* p_lights, const size_t& p_lightSize)
{
	glUniformMatrix4fv(m_data[0], 1, GL_FALSE, value_ptr(cam.GetPerspectiveMatrix()));
	glUniformMatrix4fv(m_data[1], 1, GL_FALSE, value_ptr(cam.GetViewMatrix()));
	glUniformMatrix4fv(m_data[2], 1, GL_FALSE, value_ptr(trans.GetTransMat()));
	glUniform3f(m_data[3], cam.GetPosition().x, cam.GetPosition().y, cam.GetPosition().z);
    glUniform3f(m_data[4], p_mat.GetColorR(), p_mat.GetColorG(), p_mat.GetColorB());
    glUniform1f(m_data[5], p_mat.GetShininess());
    glUniform1f(m_data[6], p_mat.GetOpacity());

    for (unsigned int i = 0; i < p_lightSize; ++i)
    {
        std::string isDirectionnalS = "pointLights[" + std::to_string(i) + "].isDirectional";
        std::string intensityS = "pointLights[" + std::to_string(i) + "].intensity";
        std::string positionS = "pointLights[" + std::to_string(i) + "].LightPos";
        std::string colorS = "pointLights[" + std::to_string(i) + "].LightColor";
        std::string lightShader = "lightColor";

        if (trans.GetPosition() == p_lights[i].GetPos())
            glUniform3f(glGetUniformLocation(shaderProgram, lightShader.c_str()), p_lights[i].GetColor().x, p_lights[i].GetColor().y, p_lights[i].GetColor().z);
        
        glUniform1i(glGetUniformLocation(shaderProgram, isDirectionnalS.c_str()), static_cast<GLint>(p_lights[i].GetIsDirectional()));
        glUniform1f(glGetUniformLocation(shaderProgram, intensityS.c_str()), p_lights[i].GetIntensity());
        glUniform3f(glGetUniformLocation(shaderProgram, positionS.c_str()), p_lights[i].GetPos().x, p_lights[i].GetPos().y, p_lights[i].GetPos().z);
        glUniform3f(glGetUniformLocation(shaderProgram, colorS.c_str()), p_lights[i].GetColor().x, p_lights[i].GetColor().y, p_lights[i].GetColor().z);

    }
    
}

void Rendering::Shaders::Shader::ApplyShader()
{
	glUseProgram(shaderProgram);
}
