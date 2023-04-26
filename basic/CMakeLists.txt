cmake_minimum_required(VERSION 3.8)
project(basic)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(interfaces REQUIRED)  # CHANGE

# Add the include directory to the include path
include_directories(include)

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

add_executable(01_hello src/01_hello.cpp)
ament_target_dependencies(01_hello rclcpp std_msgs)
add_executable(02_pub src/02_pub.cpp)
ament_target_dependencies(02_pub rclcpp std_msgs)
add_executable(03_sub src/03_sub.cpp)
ament_target_dependencies(03_sub rclcpp std_msgs)
add_executable(04_pub_sub src/04_pub_sub.cpp)
ament_target_dependencies(04_pub_sub rclcpp std_msgs)

add_executable(05_server src/05_server.cpp)
ament_target_dependencies(05_server rclcpp std_msgs example_interfaces)
add_executable(06_client src/06_client.cpp)
ament_target_dependencies(06_client rclcpp std_msgs example_interfaces)
add_executable(07_callback_lambda src/07_callback_lambda.cpp)
ament_target_dependencies(07_callback_lambda rclcpp std_msgs example_interfaces)

add_executable(08_customMsg_pub src/08_customMsg_pub.cpp)
ament_target_dependencies(08_customMsg_pub rclcpp interfaces)    # CHANGE
add_executable(09_customMsg_sub src/09_customMsg_sub.cpp)
ament_target_dependencies(09_customMsg_sub rclcpp interfaces)   # CHANGE
add_executable(10_customSrv_ser src/10_customSrv_ser.cpp)
ament_target_dependencies(10_customSrv_ser rclcpp interfaces)   # CHANGE
add_executable(11_customSrv_cli src/11_customSrv_cli.cpp)
ament_target_dependencies(11_customSrv_cli rclcpp interfaces)   # CHANGE


add_library(12_my_source_file src/12_my_source_file.cpp)
add_executable(13_some_other_node src/13_some_other_node.cpp)
target_link_libraries(13_some_other_node 12_my_source_file)

# this line to exports the library so other pkgs can use
ament_export_targets(12_my_source_file)

install(TARGETS
  01_hello
  02_pub 
  03_sub
  04_pub_sub
  
  06_client
  07_callback_lambda
  08_customMsg_pub
  09_customMsg_sub
  10_customSrv_ser
  11_customSrv_cli
  12_my_source_file
  13_some_other_node
  DESTINATION lib/${PROJECT_NAME})

ament_package()
