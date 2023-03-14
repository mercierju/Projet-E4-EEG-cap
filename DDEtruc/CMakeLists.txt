cmake_minimum_required(VERSION 3.20.0)
# give a name to the project
project(Nimporte)

#compile_options(-O3)   # specify some compilation flags


# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR}/dependencies/cmake_modules)
  

# specify the system
message(VERBOSE "CMAKE_VERSION           : " ${CMAKE_VERSION})
message(VERBOSE "CMAKE_SYSTEM_NAME       : " ${CMAKE_SYSTEM_NAME})
message(VERBOSE "CMAKE_SYSTEM            : " ${CMAKE_SYSTEM})
message(VERBOSE "CMAKE_SYSTEM_PROCESSOR  : " ${CMAKE_SYSTEM_PROCESSOR} "\n")

# specify the directories
message(VERBOSE "CMAKE_BINARY_DIR        : " ${CMAKE_BINARY_DIR})
message(VERBOSE "CMAKE_SOURCE_DIR        : " ${CMAKE_SOURCE_DIR})
message(VERBOSE "CMAKE_HOME_DIRECTORY    : " ${CMAKE_HOME_DIRECTORY})
message(VERBOSE "PROJECT_BINARY_DIR      : " ${PROJECT_BINARY_DIR})
message(VERBOSE "PROJECT_SOURCE_DIR      : " ${PROJECT_SOURCE_DIR} "\n")

# compile flags
message(VERBOSE "CMAKE_CXX_FLAGS         : " ${CMAKE_CXX_FLAG})
message(VERBOSE "CMAKE_CXX_FLAGS_DEBUG   : " ${CMAKE_CXX_FLAGS_DEBUG})
message(VERBOSE "CMAKE_CXX_FLAGS_RELEASE : " ${CMAKE_CXX_FLAGS_RELEASE})
message(VERBOSE "CMAKE_CXX_COMPILER      : " ${CMAKE_CXX_COMPILER} "\n")


# (optional) debug or release
#set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE Release)

# (optional) put the binary files in this directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)



get_filename_component(PROJ_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
message("Creating target '${PROJ_NAME}'")
project(${PROJ_NAME} LANGUAGES C CXX)


# file(GLOB_RECURSE src_file src/*.cpp)

# file(GLOB_RECURSE eemagine_includes eemagine/sdk)
set(file_exe ${PROJ_NAME})
add_executable(${PROJ_NAME} src/main.cpp)

add_library(eemagine SHARED "")
message("test" ${file_exe})

target_sources(eemagine
    PRIVATE
        eemagine/sdk/wrapper.cc
    PUBLIC
        eemagine/sdk/android.h
        eemagine/sdk/._visibility.h
        eemagine/sdk/amplifier.h
        eemagine/sdk/factory.h
        eemagine/sdk/stream.h
        eemagine/sdk/exceptions.h
        eemagine/sdk/wrapper.h
        eemagine/sdk/channel.h
        eemagine/sdk/version.h
        eemagine/sdk/visibility.h
        eemagine/sdk/buffer.h
        eemagine/sdk/._amplifier.h
)

target_compile_features(${file_exe} PRIVATE cxx_std_20) # use at least c++ 11
target_compile_options(${file_exe} PRIVATE  -O3)   # specify some compilation flags

target_include_directories(eemagine PUBLIC ${CMAKE_CURRENT_LIST_DIR})



target_compile_definitions(eemagine PUBLIC EEGO_SDK_BIND_STATIC)
target_compile_definitions(eemagine PUBLIC _UNICODE)



# Your-external "mylib", add GLOBAL if the imported library is located in directories above the current.
add_library( eego_sdk SHARED IMPORTED )


if (WIN32)
set_target_properties( eego_sdk PROPERTIES IMPORTED_LOCATION  ${CMAKE_CURRENT_LIST_DIR}/windows/64bit/eego-SDK.lib)
file(COPY ${CMAKE_CURRENT_LIST_DIR}/windows/64bit/eego-SDK.ddl
    DESTINATION ${CMAKE_BINARY_DIR}/eego-SDK.ddl)

endif (WIN32)
if (UNIX)
set_target_properties( eego_sdk PROPERTIES IMPORTED_LOCATION  ${CMAKE_CURRENT_LIST_DIR}/linux/64bit/libeego-SDK.so)
endif (UNIX)


# You can define two import-locations: one for debug and one for release.



target_link_libraries(${PROJ_NAME} PUBLIC eego_sdk)
target_link_libraries(${PROJ_NAME} PUBLIC eemagine)





  
