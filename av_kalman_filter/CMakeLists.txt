cmake_minimum_required(VERSION 3.8)
project(av_kalman_filter)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp)
find_package(rclcpp_components REQUIRED)
find_package(robot_localization REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

include_directories(include)

add_library(twist_msg_converter_component SHARED src/twist_msg_converter.cpp)

ament_target_dependencies(twist_msg_converter_component rclcpp
                          rclcpp_components geometry_msgs)

rclcpp_components_register_node(
  twist_msg_converter_component PLUGIN "util::TwistMsgConverter" EXECUTABLE
  twist_msg_converter)

ament_export_targets(export_twist_msg_converter_component)
install(
  TARGETS twist_msg_converter_component
  EXPORT export_twist_msg_converter_component
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)

install(DIRECTORY config DESTINATION share/${PROJECT_NAME})

install(DIRECTORY launch DESTINATION share/${PROJECT_NAME})

install(DIRECTORY rviz DESTINATION share/${PROJECT_NAME})

ament_package()
