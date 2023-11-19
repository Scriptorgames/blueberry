#include <fstream>
#include <map>

#include "include/graphics.hpp"

GLenum shader_type(const std::string &filename)
{
    static std::map<std::string, GLenum> ENDINGS =
        {
            {"vsh", GL_VERTEX_SHADER},
            {"fsh", GL_FRAGMENT_SHADER},
            {"csh", GL_COMPUTE_SHADER},
        };
    auto ending = filename.substr(filename.find_last_of('.') + 1);
    return ENDINGS[ending];
}

namespace blueberry
{
    Shader::Shader(const std::vector<std::string> &filenames)
    {
        m_Program = glCreateProgram();

        for (auto &filename : filenames)
        {
            std::ifstream stream(filename);
            if (!stream.is_open())
                printf("failed to open file '%s'\r\n", filename.c_str());

            std::string source;
            for (std::string line; getline(stream, line);)
                source += line + '\n';

            const char *source_ptr = source.c_str();

            GLuint shader = glCreateShader(shader_type(filename));
            glShaderSource(shader, 1, &source_ptr, NULL);
            glCompileShader(shader);
            glAttachShader(m_Program, shader);
            glDeleteShader(shader);

            stream.close();
        }

        glLinkProgram(m_Program);
        glValidateProgram(m_Program);
    }

    void Shader::Bind() const
    {
        glUseProgram(m_Program);
    }

    void Shader::Unbind() const
    {
        glUseProgram(0);
    }

    void Shader::Delete()
    {
        glDeleteProgram(m_Program);
    }
}
