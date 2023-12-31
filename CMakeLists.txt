cmake_minimum_required(VERSION 3.8)
project(blueberry)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)

# ros dependencies
find_package(std_msgs REQUIRED)

# opengl, glfw and glew
cmake_policy(SET CMP0072 NEW)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 3.3 REQUIRED)

add_executable(blueberry
  src/blueberry.cpp
  
  src/internal/simplerenderer.cpp
  src/internal/shader.cpp
  src/internal/window.cpp
)

target_link_libraries(blueberry
  OpenGL::GL
  GLEW::GLEW
  glfw
)

target_include_directories(blueberry PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>

  src
)

target_compile_features(blueberry
  PUBLIC 
  c_std_99 
  cxx_std_17
)  # Require C99 and C++17
ament_target_dependencies(
  blueberry
  std_msgs
)

install(TARGETS blueberry
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
