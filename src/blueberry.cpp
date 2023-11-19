#include "internal/window.hpp"

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

  if (!Window::Init()) // failed to init glfw
    return 1;

  auto window = Window::Create(800, 600, "Hello World!");
  if (!window) // failed to create window
  {
    Window::Terminate();
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
    Window::Terminate();
    return 3;
  }

  glDebugMessageCallback(gl_debug_callback, NULL);
  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

  glClearColor(0.2f, 0.3f, 0.9f, 1.0f);

  GLfloat vdata[]{-0.5f, -0.5f, 0, 0, -0.5f, 0.5f, 0, 1, 0.5f, 0.5f, 1, 1, 0.5f, -0.5f, 1, 0}; // x,y, u,v
  GLuint idata[]{0, 1, 2, 2, 3, 0};
  const GLchar *vsource =
      "#version 420 core\n\
      layout(location = 0) in vec4 Position;\n\
      layout(location = 1) in vec2 UV;\n\
      out vec2 vUV;\n\
      void main() {\n\
        gl_Position = Position;\n\
        vUV = UV;\n\
      }\n";
  const GLchar *fsource =
      "#version 420 core\n\
      in vec2 vUV;\n\
      layout(location = 0) out vec4 Color;\n\
      void main() {\n\
        Color = vec4(vUV, 0.0, 1.0);\n\
      }\n";

  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vdata), vdata, GL_STATIC_DRAW);

  GLuint ibo;
  glGenBuffers(1, &ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idata), idata, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, (void *)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, (void *)(sizeof(GLfloat) * 2));

  GLuint program = glCreateProgram();

  GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vshader, 1, &vsource, NULL);
  glCompileShader(vshader);
  glAttachShader(program, vshader);
  glDeleteShader(vshader);

  GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fshader, 1, &fsource, NULL);
  glCompileShader(fshader);
  glAttachShader(program, fshader);
  glDeleteShader(fshader);

  glLinkProgram(program);
  glValidateProgram(program);

  glUseProgram(program);

  while (window->Update())
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, sizeof(idata) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
  }

  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &ibo);

  glDeleteProgram(program);

  window->Destroy();
  Window::Terminate();

  return 0;
}
