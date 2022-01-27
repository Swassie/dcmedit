add_executable(test-runner
  ../src/Dicom_file.cpp
  ../src/Dicom_util.cpp
  ../src/models/Transform_tool.cpp
  ../src/logging/Console_logger.cpp
  ../src/logging/Log.cpp
  ../third-party/catch/catch.hpp

  # Test files
  main.cpp
  Dicom_util_test.cpp
  common/Event_test.cpp
  models/Transform_tool_test.cpp
)

set_target_properties(test-runner PROPERTIES CXX_STANDARD 17)
target_compile_options(test-runner PRIVATE -Wall -Wextra -pedantic)

target_include_directories(test-runner PRIVATE
  ../src
  ../third-party
  "${DCMTK_INCLUDE_DIRS}"
)

target_link_libraries(test-runner
  Qt5::Widgets
  "${DCMTK_LIBRARIES}"
)
