#pragma once

#include <GL/glew.h>

#include "graphics.hpp"

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
        Shader m_Shader;
        GLsizei m_Count;
    };
}
