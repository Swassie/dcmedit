execute_process(
  COMMAND git describe --dirty --tags --always
  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
  RESULT_VARIABLE exit_code
  OUTPUT_VARIABLE git_describe
  ERROR_QUIET
  OUTPUT_STRIP_TRAILING_WHITESPACE)

if(NOT exit_code EQUAL 0)
  set(git_describe "No version")
  message(WARNING "Could not get version. Git describe exit code: ${exit_code}")
endif()

string(TIMESTAMP date "%Y-%m-%d")
set(version "${git_describe} ${date}")

file(
  WRITE
  "${CMAKE_SOURCE_DIR}/src/Version.cpp"
  "#include \"Version.h\"\n\nconst char* const dcmedit_version = \"${version}\";")
