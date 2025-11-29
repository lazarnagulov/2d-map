cmake_minimum_required(VERSION 3.16)
project(2d_map LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

find_package(GLEW QUIET)

if(NOT GLEW_FOUND)
    message(STATUS "System GLEW not found, fetching from source...")
    
    FetchContent_Declare(
        glew
        URL https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0.zip
    )
    FetchContent_GetProperties(glew)
    if(NOT glew_POPULATED)
        FetchContent_Populate(glew)
        
        add_library(libglew_static STATIC
            ${glew_SOURCE_DIR}/src/glew.c
        )
        
        target_include_directories(libglew_static PUBLIC
            ${glew_SOURCE_DIR}/include
        )
        
        target_compile_definitions(libglew_static PUBLIC
            GLEW_STATIC
        )
        
        if(WIN32)
            target_link_libraries(libglew_static PUBLIC opengl32)
        elseif(APPLE)
            target_link_libraries(libglew_static PUBLIC "-framework OpenGL")
        else()
            find_package(OpenGL REQUIRED)
            target_link_libraries(libglew_static PUBLIC OpenGL::GL)
        endif()
    endif()
    
    set(GLEW_LIB libglew_static)
else()
    message(STATUS "Using system GLEW")
    set(GLEW_LIB GLEW::GLEW)
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/vendor/glm/CMakeLists.txt)
    add_subdirectory(src/vendor/glm)
else()
    FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.1
    )
    FetchContent_MakeAvailable(glm)
endif()

add_library(stb_image
    src/vendor/stb_image/stb_image.cpp
)
target_include_directories(stb_image PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/vendor/stb_image
)

file(GLOB_RECURSE SRC_FILES
    src/*.cpp
)

list(FILTER SRC_FILES EXCLUDE REGEX "src/vendor/.*")

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/vendor
    ${CMAKE_CURRENT_SOURCE_DIR}/src/vendor/glm
    ${CMAKE_CURRENT_SOURCE_DIR}/src/vendor/stb_image
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    ${GLEW_LIB}
    stb_image
)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE opengl32)
elseif (APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)
    find_package(X11)
    if(X11_FOUND)
        target_link_libraries(${PROJECT_NAME} PRIVATE X11)
    endif()
    target_link_libraries(${PROJECT_NAME} PRIVATE pthread dl)
endif()