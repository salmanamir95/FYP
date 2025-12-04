# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.16)

# Define the project name, version, and language
project(DataExSys VERSION 1.0 LANGUAGES CXX)

# --- Compiler and C++ Standard Configuration ---
# Set the C++ standard to C++20, which is required for std::jthread
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- Find Dependencies ---
# Find the OpenSSL library (for cryptography and hashing)
find_package(OpenSSL REQUIRED)

# Find the Threads library (for std::thread and std::jthread)
find_package(Threads REQUIRED)

# --- Project Sources ---
# Use specific GLOB commands for each source directory to avoid scanning the build directory.
file(GLOB ROOT_SOURCES      RELATIVE ${CMAKE_SOURCE_DIR} "*.cpp")
file(GLOB BLOCKCHAIN_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "Blockchain/PKCertChain/*.cpp")
file(GLOB CONSENSUS_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "Consensus/*.cpp")
# Helper and Security directories do not contain .cpp files, only .h files.

set(PROJECT_SOURCES
    ${ROOT_SOURCES}
    ${BLOCKCHAIN_SOURCES}
    ${CONSENSUS_SOURCES})

# --- Create the Executable ---
# Add an executable target named 'DataExSys' using the source files found.
add_executable(DataExSys ${PROJECT_SOURCES})

# --- Include Directories ---
# Add the project's root directory to the include path.
# This allows you to use includes like #include <Consensus/PoW.h>
target_include_directories(DataExSys PUBLIC ${CMAKE_SOURCE_DIR})

# --- Link Libraries ---
# Link the executable against the required libraries.
target_link_libraries(DataExSys PRIVATE
    # Link against OpenSSL's crypto library
    OpenSSL::Crypto

    # Link against the POSIX threads library
    Threads::Threads
)

# --- Recommended Compiler Flags for Development ---
# These flags help catch common errors and enforce good practices.
target_compile_options(DataExSys PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Werror # Optional: treat warnings as errors for very strict builds
)

# --- Doxygen Documentation (Optional) ---
# Find Doxygen and create a 'docs' target if found.
find_package(Doxygen)
if(DOXYGEN_FOUND)
    message(STATUS "Doxygen found. You can build the documentation with 'make docs'")
    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen..."
        VERBATIM
    )
endif()

# --- Final Output Message ---
message(STATUS "Project configured. Build with 'cmake --build .'")
message(STATUS "Run the application with './DataExSys'")