#pragma once

#include <GLFW/glfw3.h>

#include "imgui/imgui.h"

#include <iostream>

namespace blueberry
{
    enum WindowMode
    {
        WINDOWED,
        FULLSCREEN,
        FRAMED
    };

    struct WindowState
    {
        int x, y, w, h;
    };

    class Window
    {
    public:
        static Window &Create(int width, int height, const char *title)
        {
            if (__instance)
                throw;

            return *(__instance = new Window(width, height, title));
        }

        static Window &Get()
        {
            if (__instance)
                return *__instance;

            throw;
        }

        static void Destroy()
        {
            delete __instance;
            __instance = NULL;
        }

    private:
        static Window *__instance;

    public:
        GLFWwindow *GetGLFWwindow() const { return m_Window; }
        bool ShouldClose() const { return glfwWindowShouldClose(m_Window); }

        void Close() { glfwSetWindowShouldClose(m_Window, GLFW_TRUE); }
        void SwitchFullscreen(bool framed);
        void LoopOnce();

    private:
        Window(int width, int height, const char *title);
        ~Window()
        {
            glfwDestroyWindow(m_Window);
            glfwTerminate();

            glfwSetErrorCallback(NULL);
        }

        GLFWmonitor *GetCurrentMonitor(GLFWwindow *window);

    private:
        GLFWwindow *m_Window;
        WindowMode m_Mode = WINDOWED;
        WindowState m_State = {0, 0, 0, 0};
    };
}