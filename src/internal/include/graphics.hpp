#pragma once

#include <string>
#include <vector>

#include <GL/glew.h>

namespace blueberry
{
    class Shader
    {
    public:
        Shader(const std::vector<std::string> &filenames);

        void Bind() const;
        void Unbind() const;

        void Delete();

    private:
        GLuint m_Program;
    };
}
