cmake_minimum_required(VERSION 3.9)
project(evoke)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message(
    FATAL_ERROR
    "Prevented in-tree build. Please create a build directory outside of the source directory and call cmake from there."
  )
endif()

if(EVOKE_BUILD_WITH_UNITTEST)
    add_subdirectory("toolsets/test")
endif()

set(INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/evoke/include
    ${CMAKE_CURRENT_SOURCE_DIR}/fw/include
    ${CMAKE_CURRENT_SOURCE_DIR}/project/include
    ${CMAKE_CURRENT_SOURCE_DIR}/reporter/include
    ${CMAKE_CURRENT_SOURCE_DIR}/toolsets/include
    ${CMAKE_CURRENT_SOURCE_DIR}/utils/include
    ${CMAKE_CURRENT_SOURCE_DIR}/view/include
)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/evoke/src/Executor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/evoke/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/evoke/src/JsonCompileDb.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/fw/src/Configuration.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/fw/src/FileParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/fw/src/dotted.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/project/src/CMakeListsTxt.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/project/src/Component.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/project/src/File.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/project/src/PendingCommand.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/project/src/PredefComponents.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/project/src/Project.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/project/src/ReadCode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/project/src/tarjan.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/reporter/src/ConsoleReporter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/reporter/src/Reporter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/reporter/src/SimpleReporter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/toolsets/src/android.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/toolsets/src/clang.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/toolsets/src/gcc.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/toolsets/src/generic.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/toolsets/src/known.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/toolsets/src/msvc.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/toolsets/src/Toolset.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

if (MINGW)
  set(Boost_ARCHITECTURE -x64)
  target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32)
endif()

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC"
   OR (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS "8.0.0")
   OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
  find_package(Boost REQUIRED COMPONENTS filesystem system)
  target_link_libraries(${PROJECT_NAME} PRIVATE Boost::disable_autolinking)
else()
  find_package(Boost REQUIRED COMPONENTS system)
  target_link_libraries(${PROJECT_NAME} PRIVATE stdc++fs)
endif()

target_include_directories(${PROJECT_NAME}
                           PRIVATE ${INCLUDES} ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}
                      PRIVATE Threads::Threads ${Boost_LIBRARIES})
