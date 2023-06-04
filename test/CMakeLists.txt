find_package(Catch2 REQUIRED)
find_package(trompeloeil REQUIRED)

add_executable(unit-test
  ../src/Dcmedit.cpp
  ../src/Dcmedit.h
  ../src/common/App_info.h
  ../src/common/Callback_ref.cpp
  ../src/common/Callback_ref.h
  ../src/common/Dicom_util.cpp
  ../src/common/Dicom_util.h
  ../src/common/Event.h
  ../src/common/Event_exceptions.cpp
  ../src/common/Event_exceptions.h
  ../src/common/Exceptions.cpp
  ../src/common/Exceptions.h
  ../src/common/IEvent.h
  ../src/common/Scoped_callbacks.cpp
  ../src/common/Scoped_callbacks.h
  ../src/common/Scoped_defer.cpp
  ../src/common/Scoped_defer.h
  ../src/common/Scoped_disable.cpp
  ../src/common/Scoped_disable.h
  ../src/logging/Console_logger.cpp
  ../src/logging/Console_logger.h
  ../src/logging/Log.cpp
  ../src/logging/Log.h
  ../src/logging/Logger.h
  ../src/models/Dataset_model.cpp
  ../src/models/Dataset_model.h
  ../src/models/Dicom_file.cpp
  ../src/models/Dicom_file.h
  ../src/models/Dicom_files.cpp
  ../src/models/Dicom_files.h
  ../src/models/File_tree_model.cpp
  ../src/models/File_tree_model.h
  ../src/models/Tool.h
  ../src/models/Tool_bar.cpp
  ../src/models/Tool_bar.h
  ../src/models/Transform_tool.cpp
  ../src/models/Transform_tool.h
  ../src/ui/Gui_util.h
  ../src/ui/IPresenter.h
  ../src/ui/IView.h
  ../src/ui/IView_factory.h
  ../src/ui/about_dialog/IAbout_view.h
  ../src/ui/add_element_dialog/Add_element_presenter.cpp
  ../src/ui/add_element_dialog/Add_element_presenter.h
  ../src/ui/add_element_dialog/IAdd_element_view.h
  ../src/ui/dashboard_view/IDashboard_view.h
  ../src/ui/dataset_view/Dataset_presenter.cpp
  ../src/ui/dataset_view/Dataset_presenter.h
  ../src/ui/dataset_view/IDataset_view.h
  ../src/ui/edit_all_files_dialog/Edit_all_files_presenter.cpp
  ../src/ui/edit_all_files_dialog/Edit_all_files_presenter.h
  ../src/ui/edit_all_files_dialog/IEdit_all_files_view.h
  ../src/ui/edit_value_dialog/Edit_value_presenter.cpp
  ../src/ui/edit_value_dialog/Edit_value_presenter.h
  ../src/ui/edit_value_dialog/IEdit_value_view.h
  ../src/ui/file_tree_view/File_tree_presenter.cpp
  ../src/ui/file_tree_view/File_tree_presenter.h
  ../src/ui/file_tree_view/IFile_tree_view.h
  ../src/ui/image_view/IImage_view.h
  ../src/ui/image_view/Image_presenter.cpp
  ../src/ui/image_view/Image_presenter.h
  ../src/ui/main_view/IMain_view.h
  ../src/ui/main_view/Main_presenter.cpp
  ../src/ui/main_view/Main_presenter.h
  ../src/ui/new_file_dialog/INew_file_view.h
  ../src/ui/new_file_dialog/New_file_presenter.cpp
  ../src/ui/new_file_dialog/New_file_presenter.h
  ../src/ui/open_files_dialog/IOpen_files_view.h
  ../src/ui/open_files_dialog/Open_files_presenter.cpp
  ../src/ui/open_files_dialog/Open_files_presenter.h
  ../src/ui/open_folder_dialog/Open_folder_dialog.cpp
  ../src/ui/open_folder_dialog/Open_folder_dialog.h
  ../src/ui/split_view/ISplit_view.h
  ../src/ui/split_view/Split_factory.cpp
  ../src/ui/split_view/Split_factory.h
  ../src/ui/split_view/Split_presenter.cpp
  ../src/ui/split_view/Split_presenter.h

  # Test files
  main.cpp
  Dcmedit_test.cpp
  Fake_version.cpp
  common/Dicom_util_test.cpp
  common/Callback_ref_test.cpp
  common/Event_test.cpp
  common/Scoped_callbacks_test.cpp
  common/Scoped_defer_test.cpp
  common/Scoped_disable_test.cpp
  models/Dicom_files_test.cpp
  models/Transform_tool_test.cpp
  test_constants.h
  test_utils/Check_event.h
  test_utils/Temp_dir.cpp
  test_utils/Temp_dir.h
)

target_compile_definitions(unit-test PRIVATE DATA_PATH="${CMAKE_CURRENT_SOURCE_DIR}/test_data/")

if(MSVC)
  target_compile_options(unit-test PRIVATE /W4 /WX)
else()
  target_compile_options(unit-test PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

target_include_directories(unit-test PRIVATE
  .
  ../src
  "${DCMTK_INCLUDE_DIRS}"
)

target_link_libraries(unit-test
  Qt5::Widgets
  "${DCMTK_LIBRARIES}"
  Catch2::Catch2
  trompeloeil
)
