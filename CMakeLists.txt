cmake_minimum_required(VERSION 3.10)
project(dcmedit)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(DCMTK REQUIRED)

add_executable(dcmedit
  src/Dicom_file.cpp
  src/Dicom_file.h
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
  src/gui/tool/Tool.h
  src/gui/tool/Transform_tool.cpp
  src/gui/tool/Transform_tool.h
  src/gui/view/Add_element_dialog.cpp
  src/gui/view/Add_element_dialog.h
  src/gui/view/Dataset_table.cpp
  src/gui/view/Dataset_table.h
  src/gui/view/Dataset_view.cpp
  src/gui/view/Dataset_view.h
  src/gui/view/Edit_element_dialog.cpp
  src/gui/view/Edit_element_dialog.h
  src/gui/view/Image_view.cpp
  src/gui/view/Image_view.h
  src/gui/view/Sequence_table.cpp
  src/gui/view/Sequence_table.h
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
)

set_target_properties(dcmedit PROPERTIES CXX_STANDARD 17)
target_compile_options(dcmedit PRIVATE -Wall -Wextra -pedantic)

target_include_directories(dcmedit PRIVATE
  src
  "${DCMTK_INCLUDE_DIRS}"
)

target_link_libraries(dcmedit
  Qt5::Widgets
  "${DCMTK_LIBRARIES}"
)

add_subdirectory(test)
