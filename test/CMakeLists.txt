add_executable(test-runner
  ../third-party/catch.hpp
  main.cpp
)

set_target_properties(test-runner PROPERTIES CXX_STANDARD 17)
target_compile_options(test-runner PRIVATE -Wall -Wextra -pedantic)
target_include_directories(test-runner PRIVATE
  ../src
  ../third-party
)
