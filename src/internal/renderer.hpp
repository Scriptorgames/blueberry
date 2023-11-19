#pragma once

#include <GL/glew.h>

namespace blueberry
{
    class Renderer
    {
    public:
        virtual ~Renderer() {}

        virtual void Render() const = 0;
        virtual void Delete() = 0;
    };

    class SimpleRenderer : public Renderer
    {
    public:
        SimpleRenderer();
        ~SimpleRenderer();

        void Render() const override;
        void Delete() override;

    private:
        GLuint m_Vao;
        GLuint m_Vbo;
        GLuint m_Ibo;
        GLuint m_Program;
        GLsizei m_Count;
    };
}
