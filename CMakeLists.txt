cmake_minimum_required(VERSION 3.10)
project(dcm-viewer)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(dcm-viewer
  src/main.cpp
  src/gui/Main_window.cpp
  src/gui/Main_window.h
  src/gui/run_gui.cpp
  src/gui/run_gui.h
  src/gui/View.cpp
  src/gui/View.h
  src/gui/View_area.cpp
  src/gui/View_area.h
  src/logging/Log.cpp
  src/logging/Log.h
  src/logging/Logger.h
  src/logging/Console_logger.cpp
  src/logging/Console_logger.h
)

set_target_properties(dcm-viewer PROPERTIES CXX_STANDARD 17)
target_compile_options(dcm-viewer PRIVATE -Wall -Wextra -pedantic)
target_include_directories(dcm-viewer PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_link_libraries(dcm-viewer Qt5::Widgets)
