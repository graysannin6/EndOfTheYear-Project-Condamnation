#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H
#include <Rendering/Shader/Shader.h>

namespace GUI
{
    struct API_RENDERING Character
    {
        GLuint     TextureID;
        glm::ivec2 Size;
        glm::ivec2 Bearing;
        GLuint     Advance;
    };

    class API_RENDERING TextUI
    {
    public:
        TextUI() = delete;
        TextUI(Rendering::Shaders::Shader& p_shader);
        ~TextUI() = default;

        void LoadFont();
        void RenderText(const std::string& p_text, GLfloat p_x,
                        GLfloat            p_y,
                        GLfloat            p_scale, glm::vec3 p_color);

        void RenderUI();

    private:
        glm::mat4                   m_projection;
        GLuint                      m_VAO;
        GLuint                      m_VBO;
        Rendering::Shaders::Shader  m_shader;
        std::map<GLchar, Character> Characters;
    };
}
