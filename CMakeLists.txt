# OBridge Root CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(OBridge VERSION 0.0.1 LANGUAGES CXX)

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
# OBridge Core Library
# -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

set(BRIDGE_SOURCES
    src/cpp/src/bridge.cpp
    src/cpp/src/type_converter.cpp
)

add_library(obridge STATIC ${BRIDGE_SOURCES})

target_include_directories(obridge PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cpp/include
)

target_link_libraries(obridge PUBLIC
    Python3::Python
)

# platform-specific configurations
if(WIN32)
    target_compile_definitions(obridge PRIVATE WINDOWS_BUILD)
elseif(UNIX AND NOT APPLE)
    target_link_libraries(obridge PUBLIC dl)
    target_compile_definitions(obridge PRIVATE LINUX_BUILD)
elseif(APPLE)
    target_link_libraries(obridge PUBLIC dl)
    target_compile_definitions(obridge PRIVATE MACOS_BUILD)
endif()

# -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
# examples
# -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

add_executable(cpp_example examples/cpp_example.cpp)
target_link_libraries(cpp_example PRIVATE obridge)
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

install(TARGETS obridge
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(DIRECTORY src/cpp/include/
    DESTINATION include/obridge
)

# -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
# build summary
# -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

message(STATUS "")
message(STATUS "=== OBridge Build Configuration ===")
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
message(STATUS "  - obridge (static library)")
message(STATUS "  - cpp_example (executable)")
message(STATUS "  - test_obridge (executable)")
message(STATUS "")
