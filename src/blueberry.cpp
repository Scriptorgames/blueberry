#include "internal/include/window.hpp"
#include "internal/include/renderer.hpp"

#include <GL/glew.h>

void gl_debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{
  (void)source;
  (void)type;
  (void)id;
  (void)severity;
  (void)length;
  (void)userParam;

  printf("[GL 0x%08X] %s\r\n", id, message);
}

int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;

  if (!blueberry::Window::Init()) // failed to init glfw
    return 1;

  auto window = blueberry::Window::Create(800, 600, "Hello World!");
  if (!window) // failed to create window
  {
    blueberry::Window::Terminate();
    return 2;
  }

  window->AddSizeCallback(
      [](GLFWwindow *window, int width, int height)
      {
        (void)window;

        glViewport(0, 0, width, height);
      });
  window->AddKeyCallback(
      [](GLFWwindow *window, int key, int scancode, int action, int mods)
      {
        (void)scancode;
        (void)mods;

        if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
          glfwSetWindowShouldClose(window, GLFW_TRUE);
      });

  if (glewInit() != GLEW_OK) // failed to init glew
  {
    blueberry::Window::Terminate();
    return 3;
  }

  glDebugMessageCallback(gl_debug_callback, NULL);
  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

  glClearColor(0.2f, 0.3f, 0.9f, 1.0f);

  blueberry::SimpleRenderer renderer;

  while (window->Update())
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderer.Render();
  }

  renderer.Delete();

  window->Destroy();
  blueberry::Window::Terminate();

  return 0;
}
