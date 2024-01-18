cmake_minimum_required(VERSION 3.8)
project(your_package_name)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)

# Include C++ libraries
include_directories(include)

# Declare a C++ executable
add_executable(image_subscriber src/main.cpp)
ament_target_dependencies(image_subscriber rclcpp sensor_msgs cv_bridge OpenCV)

# Install the executable
install(TARGETS
  image_subscriber
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()