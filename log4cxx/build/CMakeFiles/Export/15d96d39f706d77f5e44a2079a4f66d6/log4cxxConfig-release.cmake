#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "log4cxx" for configuration "Release"
set_property(TARGET log4cxx APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(log4cxx PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX;RC"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/log4cxx.lib"
  )

list(APPEND _cmake_import_check_targets log4cxx )
list(APPEND _cmake_import_check_files_for_log4cxx "${_IMPORT_PREFIX}/lib/log4cxx.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
