#include "stdafx.h"
#include <Rendering/GUI/TextUI.h>
#include <iostream>

GUI::TextUI::TextUI(Rendering::Shaders::Shader& p_shader) : m_shader(p_shader)
{
    m_projection = glm::ortho(0.0f, static_cast<GLfloat>(1920), 0.0f,
                              static_cast<GLfloat>(1080));
    LoadFont();
}

void GUI::TextUI::LoadFont()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    FT_Library ft;
    if (FT_Init_FreeType(&ft))
        std::cout << "ERROR::FREETYPE: could not init freetype library\n";

    FT_Face face;
    if (FT_New_Face(ft, R"(..\Resources\Font\Doom.ttf)", 0, &face))
        std::cout << "ERROR::FREETYPRE: failed to load font\n";

    FT_Set_Pixel_Sizes(face, 0, 48);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (GLubyte c = 0; c < 128; c++)
    {
        //load character Glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYPE: failed to load Glyph\n";
            continue;
        }

        //generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
                     GL_TEXTURE_2D,
                     0,
                     GL_RED,
                     face->glyph->bitmap.width,
                     face->glyph->bitmap.rows,
                     0,
                     GL_RED,
                     GL_UNSIGNED_BYTE,
                     face->glyph->bitmap.buffer
                    );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        Character character = {
        texture,
        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
        face->glyph->advance.x
        };
        Characters.insert(std::pair<GLchar, Character>(c, character));
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void GUI::TextUI::RenderText(const std::string&          p_text, GLfloat p_x,
                             GLfloat                     p_y,
                             GLfloat                     p_scale,
                             glm::vec3                   p_color)
{
    m_shader.ApplyShader();
    glUniformMatrix4fv(glGetUniformLocation(m_shader.shaderProgram, "projection"), 1,
                       GL_FALSE, glm::value_ptr(m_projection));
    glUniform3f(glGetUniformLocation(m_shader.shaderProgram, "textColor"), p_color.x,
                p_color.y, p_color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(m_VAO);

    //iteration through all characters
    std::string::const_iterator c;
    for (c = p_text.begin(); c != p_text.end(); ++c)
    {
        Character ch = Characters[*c];

        GLfloat xPos = p_x + ch.Bearing.x * p_scale;
        GLfloat yPos = p_y - (ch.Size.y - ch.Bearing.y) * p_scale;

        GLfloat w = ch.Size.x * p_scale;
        GLfloat h = ch.Size.y * p_scale;

        //update vbo for each character
        GLfloat vertices[6][4] = {
            {xPos, yPos + h, 0.0, 0.0},
            {xPos, yPos, 0.0, 1.0},
            {xPos + w, yPos, 1.0, 1.0},

            {xPos, yPos + h, 0.0, 0.0},
            {xPos + w, yPos, 1.0, 1.0},
            {xPos + w, yPos + h, 1.0, 0.0}
        };

        //render glyph texture
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        
        //update content of vbo
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        //render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        p_x += (ch.Advance >> 6) * p_scale;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void GUI::TextUI::RenderUI()
{
    RenderText("LIFE : 100", 25.0f, 25.0f, 1.0f, glm::vec3(1.0, 0.2, 0.2));
    RenderText("AMMO : UNLIMITED", 1175.0f, 25.0f, 1.0f, glm::vec3(1.0, 0.2, 0.2));

    //crosshair
    RenderText(".", 960.0f, 500.0f, 1.0f, glm::vec3(1.0, 1., 1.0));
}
