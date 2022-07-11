add_executable(test-runner
  ../src/Dicom_file.cpp
  ../src/Dicom_util.cpp
  ../src/common/Status.cpp
  ../src/common/Status.h
  ../src/models/Dicom_files.cpp
  ../src/models/Transform_tool.cpp
  ../src/logging/Console_logger.cpp
  ../src/logging/Log.cpp
  ../third-party/catch/catch.hpp

  # Test files
  main.cpp
  Dicom_util_test.cpp
  common/Event_test.cpp
  models/Dicom_files_test.cpp
  models/Transform_tool_test.cpp
  test_constants.h
  test_utils/Check_event.h
  test_utils/Temp_dir.cpp
  test_utils/Temp_dir.h
)

set_target_properties(test-runner PROPERTIES CXX_STANDARD 17)
target_compile_definitions(test-runner PRIVATE DATA_PATH="${CMAKE_CURRENT_SOURCE_DIR}/test_data/")

if(MSVC)
  target_compile_options(test-runner PRIVATE /W4 /WX)
else()
  target_compile_options(test-runner PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

target_include_directories(test-runner PRIVATE
  .
  ../src
  ../third-party
  "${DCMTK_INCLUDE_DIRS}"
)

target_link_libraries(test-runner
  Qt5::Widgets
  "${DCMTK_LIBRARIES}"
)
