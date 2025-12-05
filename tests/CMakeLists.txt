# WeBridge Tests CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(WeBridge_Tests)

# set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add source files for the bridge library
set(BRIDGE_SOURCES
    ../src/cpp/src/bridge.cpp
    ../src/cpp/src/type_converter.cpp
)

# add bridge library
add_library(WeBridge STATIC ${BRIDGE_SOURCES})

# include directories for the bridge library
target_include_directories(WeBridge PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/cpp/include
)

# find Python development libraries
find_package(Python3 COMPONENTS Development REQUIRED)

# link Python to the bridge library
target_link_libraries(WeBridge PUBLIC Python3::Python)

# platform-specific linking
if(WIN32)
    # Windows: link against dynamic loader
    target_link_libraries(WeBridge PUBLIC)
elseif(UNIX AND NOT APPLE)
    # Linux: link against dynamic loader
    target_link_libraries(WeBridge PUBLIC dl)
elseif(APPLE)
    # macOS: link against dynamic loader
    target_link_libraries(WeBridge PUBLIC dl)
endif()

# add test executable
add_executable(test_webridge test.cpp)

# link test executable with bridge library
target_link_libraries(test_webridge PRIVATE WeBridge)

# include directories for the test
target_include_directories(test_webridge PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/cpp/include
)

# enable testing
enable_testing()

# add test
add_test(NAME WeBridgeTest COMMAND test_webridge)

# optional: other test files here
# add_executable(test_cpp ../examples/cpp_example.cpp)
# target_link_libraries(test_cpp PRIVATE WeBridge)
# add_test(NAME CppExampleTest COMMAND test_cpp)

# status
message(STATUS "=== WeBridge Build Configuration ===")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Python Version: ${Python3_VERSION}")
message(STATUS "Python Include: ${Python3_INCLUDE_DIRS}")
message(STATUS "Python Libraries: ${Python3_LIBRARIES}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "====================================")
