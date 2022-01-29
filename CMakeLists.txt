cmake_minimum_required(VERSION 3.10)
project(dcmedit)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(DCMTK CONFIG REQUIRED)

add_executable(dcmedit WIN32
  assets/assets.qrc
  src/Dicom_file.cpp
  src/Dicom_file.h
  src/Dicom_util.cpp
  src/Dicom_util.h
  src/Version.cpp
  src/Version.h
  src/common/Event.h
  src/common/Scoped_event_handlers.cpp
  src/common/Scoped_event_handlers.h
  src/dcmedit.cpp
  src/dcmedit.h
  src/Exceptions.cpp
  src/Exceptions.h
  src/logging/Console_logger.cpp
  src/logging/Console_logger.h
  src/logging/Log.cpp
  src/logging/Log.h
  src/logging/Logger.h
  src/main.cpp
  src/models/Dataset_model.cpp
  src/models/Dataset_model.h
  src/models/Dicom_files.cpp
  src/models/Dicom_files.h
  src/models/File_tree_model.cpp
  src/models/File_tree_model.h
  src/models/Tool.h
  src/models/Tool_bar.cpp
  src/models/Tool_bar.h
  src/models/Transform_tool.cpp
  src/models/Transform_tool.h
  src/presenters/Add_element_presenter.cpp
  src/presenters/Add_element_presenter.h
  src/presenters/Dataset_presenter.cpp
  src/presenters/Dataset_presenter.h
  src/presenters/Edit_all_files_presenter.cpp
  src/presenters/Edit_all_files_presenter.h
  src/presenters/Edit_value_presenter.cpp
  src/presenters/Edit_value_presenter.h
  src/presenters/Gui_util.h
  src/presenters/IPresenter.h
  src/presenters/Image_presenter.cpp
  src/presenters/Image_presenter.h
  src/presenters/Main_presenter.cpp
  src/presenters/Main_presenter.h
  src/presenters/Open_files_presenter.cpp
  src/presenters/Open_files_presenter.h
  src/presenters/Split_presenter.cpp
  src/presenters/Split_presenter.h
  src/views/About_view.cpp
  src/views/About_view.h
  src/views/Add_element_view.cpp
  src/views/Add_element_view.h
  src/views/Dashboard_view.cpp
  src/views/Dashboard_view.h
  src/views/Dataset_view.cpp
  src/views/Dataset_view.h
  src/views/Edit_all_files_view.cpp
  src/views/Edit_all_files_view.h
  src/views/Edit_value_view.cpp
  src/views/Edit_value_view.h
  src/views/File_tree_view.cpp
  src/views/File_tree_view.h
  src/views/IAbout_view.h
  src/views/IAdd_element_view.h
  src/views/IDashboard_view.h
  src/views/IDataset_view.h
  src/views/IEdit_all_files_view.h
  src/views/IEdit_value_view.h
  src/views/IFile_tree_view.h
  src/views/IImage_view.h
  src/views/IMain_view.h
  src/views/IOpen_files_view.h
  src/views/ISplit_view.h
  src/views/Image_view.cpp
  src/views/Image_view.h
  src/views/Main_view.cpp
  src/views/Main_view.h
  src/views/Open_files_view.cpp
  src/views/Open_files_view.h
  src/views/Split_view.cpp
  src/views/Split_view.h
  src/views/View_factory.cpp
  src/views/View_factory.h
)

set_property(SOURCE src/Version.cpp PROPERTY SKIP_AUTOGEN ON)

add_custom_command(
  OUTPUT "${CMAKE_SOURCE_DIR}/src/Version.cpp" phony_output
  COMMAND "${CMAKE_COMMAND}" -P "${CMAKE_SOURCE_DIR}/version.cmake"
  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
  VERBATIM)

set_target_properties(dcmedit PROPERTIES CXX_STANDARD 17)
if(MSVC)
  target_compile_options(dcmedit PRIVATE /W4 /WX)
else()
  target_compile_options(dcmedit PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

target_include_directories(dcmedit PRIVATE
  src
  "${DCMTK_INCLUDE_DIRS}"
)

target_link_libraries(dcmedit
  Qt5::Widgets
  "${DCMTK_LIBRARIES}"
)

add_subdirectory(test)
