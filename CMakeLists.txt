cmake_minimum_required(VERSION 3.15)
project(dcmedit)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(DCMTK CONFIG REQUIRED)

include(FetchContent)

FetchContent_Declare(
    eventi
    GIT_REPOSITORY https://github.com/Swassie/eventi.git
    GIT_TAG e74332bdf7f1e9159014934f310b4579024eba54)

FetchContent_MakeAvailable(eventi)

add_executable(dcmedit WIN32 MACOSX_BUNDLE
  assets/assets.qrc
  src/common/App_info.cpp
  src/common/App_info.h
  src/common/Dicom_util.cpp
  src/common/Dicom_util.h
  src/common/Exceptions.cpp
  src/common/Exceptions.h
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
  src/ui/Gui_util.cpp
  src/ui/Gui_util.h
  src/ui/IPresenter.h
  src/ui/IView.h
  src/ui/about_dialog/About_view.cpp
  src/ui/about_dialog/About_view.h
  src/ui/about_dialog/IAbout_view.h
  src/ui/add_element_dialog/Add_element_presenter.cpp
  src/ui/add_element_dialog/Add_element_presenter.h
  src/ui/add_element_dialog/Add_element_view.cpp
  src/ui/add_element_dialog/Add_element_view.h
  src/ui/add_element_dialog/IAdd_element_view.h
  src/ui/startup_view/Startup_view.cpp
  src/ui/startup_view/Startup_view.h
  src/ui/startup_view/IStartup_view.h
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
  src/ui/open_folder_dialog/IOpen_folder_view.h
  src/ui/open_folder_dialog/Open_folder_presenter.cpp
  src/ui/open_folder_dialog/Open_folder_presenter.h
  src/ui/open_folder_dialog/Open_folder_view.cpp
  src/ui/open_folder_dialog/Open_folder_view.h
  src/ui/progressbar/IProgress_view.h
  src/ui/progressbar/Progress_presenter.cpp
  src/ui/progressbar/Progress_presenter.h
  src/ui/progressbar/Progress_view.cpp
  src/ui/progressbar/Progress_view.h
  src/ui/split_view/ISplit_view.h
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

target_compile_features(dcmedit PRIVATE cxx_std_17)
set_target_properties(dcmedit PROPERTIES
  MACOSX_BUNDLE_INFO_PLIST "${CMAKE_SOURCE_DIR}/macOS.plist"
)

target_include_directories(dcmedit PRIVATE
  src
  "${DCMTK_INCLUDE_DIRS}"
)

target_link_libraries(dcmedit
  eventi
  Qt5::Widgets
  "${DCMTK_LIBRARIES}"
)

add_subdirectory(test)
