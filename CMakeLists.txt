cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



option(BUILD_COVERAGE "Build coverage" OFF)
option(BUILD_THIRD "Build 3rd task (broker)" OFF)

set(
        HUNTER_CACHE_SERVERS
        "https://github.com/bmstu-iu8-cpp-sem-3/hunter-cache"
        CACHE STRING "Default cache server"
)

include("tools/gate/cmake/HunterGate.cmake")

HunterGate(
        URL "https://github.com/ruslo/hunter/archive/v0.23.214.tar.gz"
        SHA1 "e14bc153a7f16d6a5eeec845fb0283c8fad8c358"
)

project(Json)


hunter_add_package(nlohmann_json)

find_package(nlohmann_json CONFIG REQUIRED)
add_executable(lab01 sources/main sources/source.cpp include/header.hpp)
target_link_libraries(lab01 PUBLIC nlohmann_json::nlohmann_json)

string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)
hunter_add_package(Boost COMPONENTS)
find_package(Boost CONFIG REQUIRED)

add_library(
        ${PROJECT_NAME}
        STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/json.cpp


)

add_executable(
        tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.cpp

)

target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${BOOST_ROOT}/include
)

target_include_directories(
        tests
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${GTEST_ROOT}/include
)

target_link_libraries(
        tests
        ${CMAKE_THREAD_LIBS_INIT}
        GTest::main
        GTest::gtest
        ${PROJECT_NAME}
)

enable_testing()
add_test(NAME unit_tests COMMAND tests)


#if (BUILD_THIRD)
#  hunter_add_package(nlohmann_json)
#  find_package(nlohmann_json CONFIG REQUIRED)
#
#  set(BROKER_NAME ${PROJECT_NAME}header)
#  add_executable(
#          ${BROKER_NAME}
#          ${CMAKE_CURRENT_SOURCE_DIR}/sources/source.cpp
#          ${CMAKE_CURRENT_SOURCE_DIR}/sources/main.cpp
#  )
#
#  target_include_directories(
#          ${BROKER_NAME}
#          PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
#  )
#  target_link_libraries(${THIRD_NAME} ${PROJECT_NAME} nlohmann_json::nlohmann_json)
#endif ()




#target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

if (BUILD_COVERAGE)
  set(ENABLE_COVERAGE ON CACHE BOOL "Enable coverage build." FORCE)
  list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
  find_package(codecov)
  add_coverage(${PROJECT_NAME})
  add_coverage(tests)
  list(APPEND LCOV_REMOVE_PATTERNS "'${PROJECT_SOURCE_DIR}/tests/*'")
  coverage_evaluate()
endif ()