#include <GL/glew.h>

#include <iostream>

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "imgui/backends/imgui_impl_glfw.h"

#include "rclcpp/rclcpp.hpp"

#include "simple_pub.h"
#include "internal/window.h"
#include "widgets/creator.h"
#include "widgets/terminal.h"

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  auto simple_pub_ptr = std::make_shared<SimplePub>();
  rclcpp::executors::SingleThreadedExecutor executor;
  executor.add_node(simple_pub_ptr);

  std::thread executor_thread([&executor]()
                              { executor.spin(); });

  for (int arg = 0; arg < argc; arg++)
  {
    std::cout << argv[arg] << " ";
  }
  std::cout << std::endl;

  auto &window = blueberry::Window::Create(800, 600, "Blueberry v0.0.1");

  GLenum glew_status = glewInit();
  if (glew_status != GLEW_OK)
  {
    std::cerr << "Failed to init GLEW: " << glewGetErrorString(glew_status) << std::endl;
    return 1;
  }

  std::cout << "Hello from GLEW version " << glewGetString(GLEW_VERSION) << std::endl;
  std::cout << "Hello from OpenGL version " << glGetString(GL_VERSION) << std::endl;

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking Support
  // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Viewport Support

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  // ImGui::StyleColorsLight();

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(window.GetGLFWwindow(), true);
  ImGui_ImplOpenGL3_Init();

  glClearColor(0.2, 0.2, 0.2, 1.0);

  blueberry::Manager::Create();
  blueberry::Creator creator_window;

  while (!window.ShouldClose() && rclcpp::ok())
  {
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    if (ImGui::BeginMainMenuBar())
    {
      if (ImGui::BeginMenu("File"))
      {
        if (ImGui::MenuItem("Exit"))
          window.Close();

        ImGui::EndMenu();
      }
      ImGui::EndMainMenuBar();
    }
    ImGui::DockSpaceOverViewport(ImGui::GetWindowViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

    {
      // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
      ImGui::ShowDemoWindow();

      creator_window.Render("Creator");

      blueberry::Manager::Get().Draw();
    }

    // Rendering
    ImGui::Render();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    window.LoopOnce();
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  blueberry::Window::Destroy();
  blueberry::Manager::Destroy();

  rclcpp::shutdown();

  return 0;
}
