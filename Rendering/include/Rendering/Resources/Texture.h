#pragma once
#include <Rendering/Export.h>
#include <Rendering/Context/IWindow.h>

namespace Rendering::Resources
{
    class API_RENDERING Texture
    {
    public:
        Texture();
	    ~Texture();
        void Bind();
	    void Unbind();
	    const char* GetName() const { return m_name; }
	    const int& GetWidth() const { return m_Width; }
	    const int& GetHeight() const { return m_Height; }
        const int& GetID() const { return m_texId; }

        void SetWidth(const int& p_width) { m_Width = p_width; }
        void SetHeight(const int& p_height) { m_Height = p_height; }

	    void Load(const char* p_filePath);

    private:

        const char* m_name{};
	    unsigned int m_texture{0};
	    unsigned char* m_data{};
        int m_Width, m_Height, m_BPP, m_texId{0};
        
    };
}
