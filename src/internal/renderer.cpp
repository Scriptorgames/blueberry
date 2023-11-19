#include "renderer.hpp"

namespace blueberry
{
    SimpleRenderer::SimpleRenderer()
    {
        GLfloat vdata[]{-0.5f, -0.5f, 0, 0, -0.5f, 0.5f, 0, 1, 0.5f, 0.5f, 1, 1, 0.5f, -0.5f, 1, 0}; // x,y, u,v
        GLuint idata[]{0, 1, 2, 2, 3, 0};
        const GLchar *vsource =
            "#version 420 core\n\
             layout(location = 0) in vec4 Position;\n\
             layout(location = 1) in vec2 UV;\n\
             out vec2 vUV;\n\
             void main() {\n\
               gl_Position = Position;\n\
               vUV = UV;\n\
             }\n";
        const GLchar *fsource =
            "#version 420 core\n\
             in vec2 vUV;\n\
             layout(location = 0) out vec4 Color;\n\
             void main() {\n\
               Color = vec4(vUV, 0.0, 1.0);\n\
             }\n";

        m_Count = sizeof(idata) / sizeof(GLuint);

        glGenVertexArrays(1, &m_Vao);
        glBindVertexArray(m_Vao);

        glGenBuffers(1, &m_Vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vdata), vdata, GL_STATIC_DRAW);

        glGenBuffers(1, &m_Ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idata), idata, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, (void *)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, (void *)(sizeof(GLfloat) * 2));

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        m_Program = glCreateProgram();

        GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vshader, 1, &vsource, NULL);
        glCompileShader(vshader);
        glAttachShader(m_Program, vshader);
        glDeleteShader(vshader);

        GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fshader, 1, &fsource, NULL);
        glCompileShader(fshader);
        glAttachShader(m_Program, fshader);
        glDeleteShader(fshader);

        glLinkProgram(m_Program);
        glValidateProgram(m_Program);
    }

    SimpleRenderer::~SimpleRenderer()
    {
        Delete();
    }

    void SimpleRenderer::Render() const
    {
        glBindVertexArray(m_Vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo);
        glUseProgram(m_Program);

        glDrawElements(GL_TRIANGLES, m_Count, GL_UNSIGNED_INT, (const void *)0);

        glUseProgram(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void SimpleRenderer::Delete()
    {
        glDeleteVertexArrays(1, &m_Vao);
        glDeleteBuffers(1, &m_Vbo);
        glDeleteBuffers(1, &m_Ibo);
        glDeleteProgram(m_Program);
    }
}
