cmake_minimum_required(VERSION 3.25)
project(Socket)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)


set(LIBSOCKET_SOURCES src/Socket.cpp)
set(LIBSOCKET_INCLUDE_DIRECTORIES include)

# libSocket.a
add_library(Socket_static STATIC ${LIBSOCKET_SOURCES})
target_include_directories(Socket_static PUBLIC ${LIBSOCKET_INCLUDE_DIRECTORIES})
set_target_properties(
    Socket_static
    PROPERTIES 
    OUTPUT_NAME Socket
)

# libSocket.so
add_library(Socket_shared SHARED ${LIBSOCKET_SOURCES})
target_include_directories(Socket_shared PUBLIC ${LIBSOCKET_INCLUDE_DIRECTORIES})
set_target_properties(
    Socket_shared
    PROPERTIES 
    OUTPUT_NAME Socket
)


# VS Code CMake Tools Commands
# CMake:Configure                                           : cmake -S . -B build
# CMake:Delete Cache and reconfigure                        : cmake --fresh -S . -B build
# CMake:Clean Rebuild                                       : cmake --build . --target clean; cmake --build . --target all
# CMake:Build Target                                        : cmake --build . --target <target-name>
# CMake:Build                               (F7)            : cmake --build . --target all
# CMake:Run without Debugging               (Shift + F5)    : <executable>
# CMake:Debug                               (Ctrl + F5)
