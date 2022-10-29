cmake_minimum_required(VERSION 3.14)
project(dcmedit)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(DCMTK CONFIG REQUIRED)

add_executable(dcmedit WIN32 MACOSX_BUNDLE
  assets/assets.qrc
  src/Dcmedit.cpp
  src/Dcmedit.h
  src/common/App_info.cpp
  src/common/App_info.h
  src/common/Defer_event.cpp
  src/common/Defer_event.h
  src/common/Dicom_util.cpp
  src/common/Dicom_util.h
  src/common/Event.h
  src/common/Scoped_event_handlers.cpp
  src/common/Scoped_event_handlers.h
  src/common/Status.cpp
  src/common/Status.h
  src/logging/Console_logger.cpp
  src/logging/Console_logger.h
  src/logging/Log.cpp
  src/logging/Log.h
  src/logging/Logger.h
  src/main.cpp
  src/models/Dataset_model.cpp
  src/models/Dataset_model.h
  src/models/Dicom_file.cpp
  src/models/Dicom_file.h
  src/models/Dicom_files.cpp
  src/models/Dicom_files.h
  src/models/File_tree_model.cpp
  src/models/File_tree_model.h
  src/models/Tool.h
  src/models/Tool_bar.cpp
  src/models/Tool_bar.h
  src/models/Transform_tool.cpp
  src/models/Transform_tool.h
  src/ui/Gui_util.h
  src/ui/IPresenter.h
  src/ui/IView.h
  src/ui/IView_factory.h
  src/ui/View_factory.cpp
  src/ui/View_factory.h
  src/ui/about_dialog/About_view.cpp
  src/ui/about_dialog/About_view.h
  src/ui/about_dialog/IAbout_view.h
  src/ui/add_element_dialog/Add_element_presenter.cpp
  src/ui/add_element_dialog/Add_element_presenter.h
  src/ui/add_element_dialog/Add_element_view.cpp
  src/ui/add_element_dialog/Add_element_view.h
  src/ui/add_element_dialog/IAdd_element_view.h
  src/ui/dashboard_view/Dashboard_view.cpp
  src/ui/dashboard_view/Dashboard_view.h
  src/ui/dashboard_view/IDashboard_view.h
  src/ui/dataset_view/Dataset_presenter.cpp
  src/ui/dataset_view/Dataset_presenter.h
  src/ui/dataset_view/Dataset_view.cpp
  src/ui/dataset_view/Dataset_view.h
  src/ui/dataset_view/IDataset_view.h
  src/ui/edit_all_files_dialog/Edit_all_files_presenter.cpp
  src/ui/edit_all_files_dialog/Edit_all_files_presenter.h
  src/ui/edit_all_files_dialog/Edit_all_files_view.cpp
  src/ui/edit_all_files_dialog/Edit_all_files_view.h
  src/ui/edit_all_files_dialog/IEdit_all_files_view.h
  src/ui/edit_value_dialog/Edit_value_presenter.cpp
  src/ui/edit_value_dialog/Edit_value_presenter.h
  src/ui/edit_value_dialog/Edit_value_view.cpp
  src/ui/edit_value_dialog/Edit_value_view.h
  src/ui/edit_value_dialog/IEdit_value_view.h
  src/ui/file_tree_view/File_tree_presenter.cpp
  src/ui/file_tree_view/File_tree_presenter.h
  src/ui/file_tree_view/File_tree_view.cpp
  src/ui/file_tree_view/File_tree_view.h
  src/ui/file_tree_view/IFile_tree_view.h
  src/ui/image_view/IImage_view.h
  src/ui/image_view/Image_presenter.cpp
  src/ui/image_view/Image_presenter.h
  src/ui/image_view/Image_view.cpp
  src/ui/image_view/Image_view.h
  src/ui/main_view/IMain_view.h
  src/ui/main_view/Main_presenter.cpp
  src/ui/main_view/Main_presenter.h
  src/ui/main_view/Main_view.cpp
  src/ui/main_view/Main_view.h
  src/ui/new_file_dialog/INew_file_view.h
  src/ui/new_file_dialog/New_file_presenter.cpp
  src/ui/new_file_dialog/New_file_presenter.h
  src/ui/new_file_dialog/New_file_view.cpp
  src/ui/new_file_dialog/New_file_view.h
  src/ui/open_files_dialog/IOpen_files_view.h
  src/ui/open_files_dialog/Open_files_presenter.cpp
  src/ui/open_files_dialog/Open_files_presenter.h
  src/ui/open_files_dialog/Open_files_view.cpp
  src/ui/open_files_dialog/Open_files_view.h
  src/ui/split_view/ISplit_view.h
  src/ui/split_view/Split_factory.cpp
  src/ui/split_view/Split_factory.h
  src/ui/split_view/Split_presenter.cpp
  src/ui/split_view/Split_presenter.h
  src/ui/split_view/Split_view.cpp
  src/ui/split_view/Split_view.h
)

set_property(SOURCE src/common/App_info.cpp PROPERTY SKIP_AUTOGEN ON)

add_custom_command(
  OUTPUT "${CMAKE_SOURCE_DIR}/src/common/App_info.cpp" phony_file
  COMMAND python3 "${CMAKE_SOURCE_DIR}/scripts/generate_app_info.py"
  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
  VERBATIM
)

set_target_properties(dcmedit PROPERTIES
  MACOSX_BUNDLE_INFO_PLIST "${CMAKE_SOURCE_DIR}/macOS.plist"
)

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
