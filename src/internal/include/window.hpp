#pragma once

#include <memory>
#include <string>
#include <vector>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace blueberry
{
    class Window
    {
    public:
        static bool Init();
        static void Terminate();

        static std::shared_ptr<Window> Create(int width, int height, const std::string &title);

    public:
        bool Update();
        void Destroy();

        void AddSizeCallback(GLFWwindowsizefun callback);
        void AddKeyCallback(GLFWkeyfun callback);

    private:
        Window(GLFWwindow *window);

    private:
        GLFWwindow *m_Window;

        std::vector<GLFWwindowsizefun> m_SizeCallbacks;
        std::vector<GLFWkeyfun> m_KeyCallbacks;
    };
}
