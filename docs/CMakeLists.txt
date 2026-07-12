find_package(Doxygen COMPONENTS dot)

if(NOT DOXYGEN_FOUND)
  message(STATUS "Doxygen not found -- 'docs' target will not be available")
  return()
endif()

set(DOXYGEN_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}" CACHE PATH "Doxygen output directory")

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in"
  "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
  @ONLY
)

add_custom_target(docs
  COMMAND Doxygen::doxygen "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
  COMMENT "Generating API documentation with Doxygen"
  VERBATIM
)
