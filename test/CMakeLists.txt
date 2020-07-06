add_executable(test-runner
  ../src/Dataset.cpp
  ../src/logging/Log.cpp
  ../src/logging/Log.h
  ../third-party/catch.hpp
  main.cpp
  Dataset.cpp
)

set_target_properties(test-runner PROPERTIES CXX_STANDARD 17)
target_compile_options(test-runner PRIVATE -Wall -Wextra -pedantic)
target_compile_definitions(test-runner PRIVATE TESTDATA="${CMAKE_CURRENT_SOURCE_DIR}/testdata/")

target_include_directories(test-runner PRIVATE
  ../src
  ../third-party
  "${DCMTK_INCLUDE_DIRS}"
)

target_link_libraries(test-runner "${DCMTK_LIBRARIES}")
