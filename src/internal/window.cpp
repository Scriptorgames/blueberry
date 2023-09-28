#include "window.h"

blueberry::Window *blueberry::Window::__instance;

void error_callback(int error_code, const char *description)
{
    std::cerr << "GLFW Error " << error_code << ": " << description << std::endl;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    (void)scancode;
    (void)mods;

    if (ImGui::GetIO().WantCaptureKeyboard)
        return;

    if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    if (key == GLFW_KEY_F11 && action == GLFW_RELEASE)
        blueberry::Window::Get().SwitchFullscreen(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT));
}

void size_callback(GLFWwindow *window, int width, int height)
{
    (void)window;

    glViewport(0, 0, width, height);
}

blueberry::Window::Window(int width, int height, const char *title)
{
    glfwSetErrorCallback(error_callback);

    int glfw_status = glfwInit();
    if (glfw_status != GLFW_TRUE)
    {
        std::cerr << "failed to init GLFW" << std::endl;
        throw;
    }

    std::cout << "Hello from GLFW version " << glfwGetVersionString() << std::endl;

    glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!m_Window)
    {
        std::cerr << "failed to create GLFW window" << std::endl;
        throw;
    }

    glfwSetKeyCallback(m_Window, key_callback);
    glfwSetWindowSizeCallback(m_Window, size_callback);

    glfwMakeContextCurrent(m_Window);
}

void blueberry::Window::SwitchFullscreen(bool framed)
{
    if (m_Mode == WINDOWED)
    {
        glfwGetWindowSize(m_Window, &m_State.w, &m_State.h);
        glfwGetWindowPos(m_Window, &m_State.x, &m_State.y);

        GLFWmonitor *monitor = GetCurrentMonitor(m_Window);
        if (!monitor)
        {
            std::cerr << "failed to get current monitor" << std::endl;
            throw;
        }

        const GLFWvidmode *vidmode = glfwGetVideoMode(monitor);

        int mx, my;
        glfwGetMonitorPos(monitor, &mx, &my);

        if (framed)
        {
            glfwSetWindowAttrib(m_Window, GLFW_DECORATED, GLFW_FALSE);
            glfwSetWindowMonitor(m_Window, NULL, mx, my, vidmode->width, vidmode->height, vidmode->refreshRate);
            m_Mode = FRAMED;
        }
        else
        {
            glfwSetWindowMonitor(m_Window, monitor, mx, my, vidmode->width, vidmode->height, vidmode->refreshRate);
            m_Mode = FULLSCREEN;
        }
    }
    else
    {
        if (m_Mode == FRAMED)
            glfwSetWindowAttrib(m_Window, GLFW_DECORATED, GLFW_TRUE);

        glfwSetWindowMonitor(m_Window, NULL, m_State.x, m_State.y, m_State.w, m_State.h, GLFW_DONT_CARE);

        m_Mode = WINDOWED;
    }
}

void blueberry::Window::LoopOnce()
{
    glfwPollEvents();

    // Update and Render additional Platform Windows
    // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
    //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow *backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }

    glfwSwapBuffers(m_Window);
}

GLFWmonitor *blueberry::Window::GetCurrentMonitor(GLFWwindow *window)
{
    int nmonitors, i;
    int wx, wy, ww, wh;
    int mx, my, mw, mh;
    int overlap, bestoverlap;
    GLFWmonitor *bestmonitor;
    GLFWmonitor **monitors;
    const GLFWvidmode *mode;

    bestoverlap = 0;
    bestmonitor = NULL;

    glfwGetWindowPos(window, &wx, &wy);
    glfwGetWindowSize(window, &ww, &wh);
    monitors = glfwGetMonitors(&nmonitors);

    for (i = 0; i < nmonitors; i++)
    {
        mode = glfwGetVideoMode(monitors[i]);
        glfwGetMonitorPos(monitors[i], &mx, &my);
        mw = mode->width;
        mh = mode->height;

        overlap =
            std::max(0, std::min(wx + ww, mx + mw) - std::max(wx, mx)) *
            std::max(0, std::min(wy + wh, my + mh) - std::max(wy, my));

        if (bestoverlap < overlap)
        {
            bestoverlap = overlap;
            bestmonitor = monitors[i];
        }
    }

    return bestmonitor;
}