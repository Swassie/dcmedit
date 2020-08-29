cmake_minimum_required(VERSION 3.10)
project(dcm-viewer)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(DCMTK REQUIRED)

add_executable(dcm-viewer
  src/main.cpp
  src/Dataset.cpp
  src/Dataset.h
  src/gui/Data_element_model.cpp
  src/gui/Data_element_model.h
  src/gui/Data_element_view.cpp
  src/gui/Data_element_view.h
  src/gui/Dicom_studio.cpp
  src/gui/Dicom_studio.h
  src/gui/Gui_util.cpp
  src/gui/Gui_util.h
  src/gui/Image_view.cpp
  src/gui/Image_view.h
  src/gui/Initial_studio.cpp
  src/gui/Initial_studio.h
  src/gui/Initial_view.cpp
  src/gui/Initial_view.h
  src/gui/Main_window.cpp
  src/gui/Main_window.h
  src/gui/Pan_tool.cpp
  src/gui/Pan_tool.h
  src/gui/run_gui.cpp
  src/gui/run_gui.h
  src/gui/Studio.cpp
  src/gui/Studio.h
  src/gui/Tool.h
  src/gui/Tool_bar.cpp
  src/gui/Tool_bar.h
  src/gui/View_factory.cpp
  src/gui/View_factory.h
  src/gui/Menu.h
  src/gui/Workspace_view.cpp
  src/gui/Workspace_view.h
  src/gui/Zoom_tool.cpp
  src/gui/Zoom_tool.h
  src/logging/Log.cpp
  src/logging/Log.h
  src/logging/Logger.h
  src/logging/Console_logger.cpp
  src/logging/Console_logger.h
  src/util/Filesystem.cpp
  src/util/Filesystem.h
)

set_target_properties(dcm-viewer PROPERTIES CXX_STANDARD 17)
target_compile_options(dcm-viewer PRIVATE -Wall -Wextra -pedantic)

target_include_directories(dcm-viewer PRIVATE
  src
  "${DCMTK_INCLUDE_DIRS}"
)

target_link_libraries(dcm-viewer
  Qt5::Widgets
  "${DCMTK_LIBRARIES}"
  stdc++fs
)

add_subdirectory(test)
