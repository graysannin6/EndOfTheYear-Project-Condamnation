#include "stdafx.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <Rendering/Resources/Texture.h>
#include "iostream"


Rendering::Resources::Texture::Texture() : m_data(nullptr), m_Width(1), m_Height(1), m_BPP(0), m_texture(0)
{
    m_texId = rand() % 16;
    glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &m_texture);

}

Rendering::Resources::Texture::~Texture()
{
	glDeleteTextures(1, &m_texture);
}

void Rendering::Resources::Texture::Bind()
{
    glActiveTexture(m_texId);
    glBindTexture(GL_TEXTURE_2D, m_texture);
}

void Rendering::Resources::Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Rendering::Resources::Texture::Load(const char* p_filePath)
{
    m_name = p_filePath;
    
	m_data = stbi_load(p_filePath, &m_Width, &m_Height, &m_BPP, STBI_rgb_alpha);

	if (m_data != nullptr)
	{

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		std::cout << "Texture loaded: " << p_filePath << "\n";
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data);

	}
	else
	{
		std::cout << "Texture : " << p_filePath << "not loaded" << "\n";
	}


}