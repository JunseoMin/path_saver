cmake_minimum_required(VERSION 3.8)
project(path_saver)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(tf2_ros REQUIRED)

# Add executable
add_executable(path_saver_node src/path_saver.cpp)
add_executable(path_loader_node src/path_loader.cpp)
add_executable(path_generator_node src/path_generator.cpp)
ament_target_dependencies(path_saver_node rclcpp nav_msgs geometry_msgs)
ament_target_dependencies(path_loader_node rclcpp nav_msgs geometry_msgs)
ament_target_dependencies(path_generator_node rclcpp nav_msgs geometry_msgs tf2_ros)

# Include headers
target_include_directories(path_saver_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_include_directories(path_loader_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_include_directories(path_generator_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

install(TARGETS
  path_saver_node
  path_loader_node
  path_generator_node
  DESTINATION lib/${PROJECT_NAME})

ament_package()
