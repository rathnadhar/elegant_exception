cmake_minimum_required(VERSION 3.25)
project(elegant_exception LANGUAGES CXX)

# 1. Require C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 2. Install headers to /usr/local/include/elegant_exception
install(DIRECTORY include/elegant_exception
        DESTINATION include
        FILES_MATCHING PATTERN "*.h")

# 3. Command-line build type: DEBUG or RELEASE
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose Release or Debug" FORCE)
endif()

# 4. Ninja build support (auto-detected by CMake if generator is Ninja)

# 5. Release optimization flags
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
endif()

# 6. Force x64 architecture (optional, platform-specific)
if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64")
    message(STATUS "Targeting x64 architecture")
else()
    message(WARNING "Non-x64 architecture detected")
endif()

# Optional: Add a dummy target for testing or examples
add_library(elegant_exception INTERFACE)
target_include_directories(elegant_exception INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>

# Install LICENSE file
install(FILES LICENSE DESTINATION share/elegant_exception)
)
