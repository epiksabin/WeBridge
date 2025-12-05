# WeBridge Root CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(WeBridge VERSION 0.0.1 LANGUAGES CXX)

# set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# find required packages
find_package(Python3 COMPONENTS Development REQUIRED)

# -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
# WeBridge Core Library
# -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

set(BRIDGE_SOURCES
    src/cpp/src/bridge.cpp
    src/cpp/src/type_converter.cpp
)

add_library(WeBridge STATIC ${BRIDGE_SOURCES})

target_include_directories(WeBridge PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cpp/include
)

target_link_libraries(WeBridge PUBLIC
    Python3::Python
)

# platform-specific configurations
if(WIN32)
    target_compile_definitions(WeBridge PRIVATE WINDOWS_BUILD)
elseif(UNIX AND NOT APPLE)
    target_link_libraries(WeBridge PUBLIC dl)
    target_compile_definitions(WeBridge PRIVATE LINUX_BUILD)
elseif(APPLE)
    target_link_libraries(WeBridge PUBLIC dl)
    target_compile_definitions(WeBridge PRIVATE MACOS_BUILD)
endif()

# -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
# examples
# -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

add_executable(cpp_example examples/cpp_example.cpp)
target_link_libraries(cpp_example PRIVATE WeBridge)
target_include_directories(cpp_example PRIVATE src/cpp/include)

# -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
# tests
# -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

enable_testing()

# add tests subdirectory
add_subdirectory(tests)

# -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
# installation configuration
# -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-   

install(TARGETS WeBridge
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(DIRECTORY src/cpp/include/
    DESTINATION include/WeBridge
)

# -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
# build summary
# -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

message(STATUS "")
message(STATUS "=== WeBridge Build Configuration ===")
message(STATUS "Project: ${PROJECT_NAME} v${PROJECT_VERSION}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "")
message(STATUS "Dependencies:")
message(STATUS "  Python: ${Python3_VERSION}")
message(STATUS "  Python Include: ${Python3_INCLUDE_DIRS}")
message(STATUS "  Python Libraries: ${Python3_LIBRARIES}")
message(STATUS "")
message(STATUS "Output Directories:")
message(STATUS "  Runtime: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "  Libraries: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
message(STATUS "")
message(STATUS "Targets:")
message(STATUS "  - WeBridge (static library)")
message(STATUS "  - cpp_example (executable)")
message(STATUS "  - test_webridge (executable)")
message(STATUS "")
