cmake_minimum_required(VERSION 3.25)
project(Socket LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(LIBSOCKET_INCLUDE_DIRECTORIES
    "${CMAKE_CURRENT_SOURCE_DIR}/include/"
    PARENT_SCOPE
)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE ${LIBSOCKET_INCLUDE_DIRECTORIES})


# VS Code CMake Tools Commands
# CMake:Configure                                           : cmake -S . -B build
# CMake:Delete Cache and reconfigure                        : cmake --fresh -S . -B build
# CMake:Clean Rebuild                                       : cmake --build . --target clean; cmake --build . --target all
# CMake:Build Target                                        : cmake --build . --target <target-name>
# CMake:Build                               (F7)            : cmake --build . --target all
# CMake:Run without Debugging               (Shift + F5)    : <executable>
# CMake:Debug                               (Ctrl + F5)
