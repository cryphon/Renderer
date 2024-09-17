cmake_minimum_required(VERSION 3.30)
project(ThreeBodySimulation)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Find SDL2 package
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Find OpenGL
find_package(OpenGL REQUIRED)

# Find GLEW (for OpenGL extensions)
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

# Add source files to project
set(SOURCES
    src/main.cpp
    src/physics.cpp
    src/renderer.cpp
    src/vec3.cpp
    src/body.cpp
    src/renderer.cpp
    src/collision.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/include)


add_executable(${PROJECT_NAME} ${SOURCES})

# Link libs
target_link_libraries(${PROJECT_NAME}
    ${SDL2_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
)

# Optionally include some flags to avoid warning spam
if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(ThreeBodySimulation PRIVATE -Wall -Wextra -Wpedantic)
endif()



# Add custom run target
add_custom_target(run
    COMMAND ${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    COMMENT "Build and run ThreeBodySimulation"
)
