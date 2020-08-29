cmake_minimum_required(VERSION 3.10)
project(dcm-viewer)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(DCMTK REQUIRED)

add_executable(dcm-viewer
  src/Dataset.cpp
  src/Dataset.h
  src/gui/Data_element_model.cpp
  src/gui/Data_element_model.h
  src/gui/Dicom_view_factory.cpp
  src/gui/Dicom_view_factory.h
  src/gui/Gui_util.cpp
  src/gui/Gui_util.h
  src/gui/Main_window.cpp
  src/gui/Main_window.h
  src/gui/Start_screen.cpp
  src/gui/Start_screen.h
  src/gui/View_factory.h
  src/gui/View_manager.cpp
  src/gui/View_manager.h
  src/gui/menu/File_menu.cpp
  src/gui/menu/File_menu.h
  src/gui/menu/Menu.cpp
  src/gui/menu/Menu.h
  src/gui/menu/Menu_bar.cpp
  src/gui/menu/Menu_bar.h
  src/gui/menu/Tool_bar.cpp
  src/gui/menu/Tool_bar.h
  src/gui/menu/View_menu.cpp
  src/gui/menu/View_menu.h
  src/gui/run_gui.cpp
  src/gui/run_gui.h
  src/gui/studio/Dicom_studio.cpp
  src/gui/studio/Dicom_studio.h
  src/gui/studio/Start_studio.cpp
  src/gui/studio/Start_studio.h
  src/gui/studio/Studio.cpp
  src/gui/studio/Studio.h
  src/gui/tool/Pan_tool.cpp
  src/gui/tool/Pan_tool.h
  src/gui/tool/Tool.h
  src/gui/tool/Zoom_tool.cpp
  src/gui/tool/Zoom_tool.h
  src/gui/view/Data_element_view.cpp
  src/gui/view/Data_element_view.h
  src/gui/view/Image_view.cpp
  src/gui/view/Image_view.h
  src/gui/view/View.cpp
  src/gui/view/View.h
  src/gui/view/View_actions.cpp
  src/gui/view/View_actions.h
  src/logging/Console_logger.cpp
  src/logging/Console_logger.h
  src/logging/Log.cpp
  src/logging/Log.h
  src/logging/Logger.h
  src/main.cpp
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
