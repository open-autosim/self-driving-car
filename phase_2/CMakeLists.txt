cmake_minimum_required(VERSION 3.5)

project(phase_2)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find SFML
find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Include directories
set(INCLUDE_DIRS include /opt/homebrew/include)
include_directories(${INCLUDE_DIRS})

# Source files
file(GLOB_RECURSE SOURCES 
     "src/*.cpp"
)

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link SFML libraries
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

# Link ImGui library
target_link_libraries(${PROJECT_NAME} imgui)

# Link OpenGL libraries
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})

add_subdirectory(ext) # Add ImGui subdirectory