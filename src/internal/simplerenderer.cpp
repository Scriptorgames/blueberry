#include "include/renderer.hpp"

namespace blueberry
{
    SimpleRenderer::SimpleRenderer()
        : m_Shader(
              {
                  "/home/schre/workspace/src/blueberry/res/shaders/default/default.vsh",
                  "/home/schre/workspace/src/blueberry/res/shaders/default/default.fsh",
              })
    {
        GLfloat vdata[]{-0.5f, -0.5f, 0, 0, -0.5f, 0.5f, 0, 1, 0.5f, 0.5f, 1, 1, 0.5f, -0.5f, 1, 0}; // x,y, u,v
        GLuint idata[]{0, 1, 2, 2, 3, 0};

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
    }

    SimpleRenderer::~SimpleRenderer()
    {
        Delete();
    }

    void SimpleRenderer::Render() const
    {
        glBindVertexArray(m_Vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo);
        m_Shader.Bind();

        glDrawElements(GL_TRIANGLES, m_Count, GL_UNSIGNED_INT, (const void *)0);

        m_Shader.Unbind();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void SimpleRenderer::Delete()
    {
        glDeleteVertexArrays(1, &m_Vao);
        glDeleteBuffers(1, &m_Vbo);
        glDeleteBuffers(1, &m_Ibo);
        m_Shader.Delete();
    }
}
