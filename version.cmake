execute_process(
  COMMAND git describe --dirty --tags --always
  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
  RESULT_VARIABLE exit_code
  OUTPUT_VARIABLE version
  ERROR_QUIET
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

if(NOT exit_code EQUAL 0)
  set(version "No version")
  message(WARNING "Could not get version. Git describe exit code: ${exit_code}")
endif()

string(TIMESTAMP date "%Y-%m-%d")
set(long_version "${version} ${date}")

configure_file("${CMAKE_SOURCE_DIR}/src/Version.cpp.tmpl" "${CMAKE_SOURCE_DIR}/src/Version.cpp")
