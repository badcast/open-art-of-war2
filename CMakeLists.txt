cmake_minimum_required(VERSION 3.10)

project(oaow2 LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

option(USE_SYSRONIN "Using system ronin-engine" OFF)

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")

if(WIN32)
  add_executable(oaow2 WIN32 ${HEADERS} ${SOURCES})
else()
  add_executable(oaow2 ${HEADERS} ${SOURCES})
endif()

target_include_directories(oaow2 PRIVATE include)
target_compile_features(oaow2 PRIVATE cxx_std_17)

if(NOT USE_SYSRONIN)
  set(RONIN_NO_CONFIG ON)
  add_subdirectory(3rdParty/ronin-engine)
  target_link_libraries(oaow2 PRIVATE RoninEngine)
else()

  find_package(PkgConfig)

  if(NOT MSVC AND PkgConfig_FOUND)
      pkg_check_modules(RoninEngine REQUIRED RoninEngine)
  else()
      find_package(RoninEngine REQUIRED)
  endif()

  target_include_directories(oaow2 PRIVATE ${RoninEngine_INCLUDE_DIRS})
  target_link_libraries(oaow2 PRIVATE ${RoninEngine_LIBRARIES})
endif()

# set the executable name
set_target_properties(oaow2 PROPERTIES OUTPUT_NAME oaow2)

# create link resources "data:resources"
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(_DATA_DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/data")
if(NOT EXISTS "${_DATA_DESTINATION}")
  message(STATUS "Linking data to \"${_DATA_DESTINATION}\"")
  file(CREATE_LINK "${CMAKE_CURRENT_SOURCE_DIR}/resources/data"
       "${_DATA_DESTINATION}" SYMBOLIC)
else()
  message(STATUS "Symbolic link exists - not required")
endif()
unset(_DATA_DESTINATION)
