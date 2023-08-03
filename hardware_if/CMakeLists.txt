cmake_minimum_required(VERSION 3.5)

project(hardware_if)

# Default to C++17
if (NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()
if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra)
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(pigpio REQUIRED)
find_package(iugv_interfaces REQUIRED)

include_directories(include/)

find_library(pigpio_LIBRARY
		NAMES libpigpio.so
		HINTS /usr/local/lib)

find_library(pigpio_if2_LIBRARY
		NAMES libpigpiod_if2.so
		HINTS /usr/local/lib)

add_executable(${PROJECT_NAME} src/${PROJECT_NAME}.cpp)
ament_target_dependencies(${PROJECT_NAME} pigpio rclcpp iugv_interfaces)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} ${pigpio_LIBRARY} ${pigpio_if2_LIBRARY})

install(
  DIRECTORY include/
  DESTINATION include
)

install(TARGETS ${PROJECT_NAME}
  DESTINATION lib/${PROJECT_NAME}
)

ament_export_include_directories(include/)
ament_package()