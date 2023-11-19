#include "window.hpp"

#include <map>
#include <stdio.h>

namespace blueberry
{
    std::map<GLFWwindow *, std::shared_ptr<Window>> WindowMap;

    void glfw_error_callback(int error_code, const char *description)
    {
        printf("[GLFW 0x%08X] %s\r\n", error_code, description);
    }

    bool Window::Init()
    {
        glfwSetErrorCallback(glfw_error_callback);
        int error = glfwInit();
        return error == GLFW_TRUE;
    }

    void Window::Terminate()
    {
        glfwTerminate();
        glfwSetErrorCallback(NULL);
    }

    std::shared_ptr<Window> Window::Create(int width, int height, const std::string &title)
    {
        glfwDefaultWindowHints();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        GLFWwindow *window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
        if (!window)
            return std::shared_ptr<Window>();
        return std::shared_ptr<Window>(new Window(window));
    }

    bool Window::Update()
    {
        glfwSwapBuffers(m_Window);
        glfwPollEvents();

        return !glfwWindowShouldClose(m_Window);
    }

    void Window::Destroy()
    {
        glfwDestroyWindow(m_Window);
    }

    void Window::AddSizeCallback(GLFWwindowsizefun callback)
    {
        m_SizeCallbacks.push_back(callback);
    }

    void Window::AddKeyCallback(GLFWkeyfun callback)
    {
        m_KeyCallbacks.push_back(callback);
    }

    Window::Window(GLFWwindow *window)
        : m_Window(window)
    {
        WindowMap[window] = std::shared_ptr<Window>(this); // add to window map for callbacks

        glfwSetWindowSizeCallback(
            m_Window,
            [](GLFWwindow *window, int width, int height)
            {
                for (auto &callback : WindowMap[window]->m_SizeCallbacks)
                    callback(window, width, height);
            });
        glfwSetKeyCallback(
            m_Window,
            [](GLFWwindow *window, int key, int scancode, int action, int mods)
            {
                for (auto &callback : WindowMap[window]->m_KeyCallbacks)
                    callback(window, key, scancode, action, mods);
            });

        glfwMakeContextCurrent(m_Window);
    }
}
