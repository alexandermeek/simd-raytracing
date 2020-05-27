cmake_minimum_required(VERSION 3.10)
project(SIMD-RayTracing VERSION 1.0 LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON) # Hide extra projects in solution under a folder.

file (GLOB NLP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

file (GLOB NLP_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

add_executable(SIMD-RayTracing ${NLP_SOURCES} ${NLP_HEADERS} ${VerifyCXX})

target_include_directories(SIMD-RayTracing PRIVATE 
                           ${CMAKE_CURRENT_SOURCE_DIR} 
                           ${CMAKE_CURRENT_SOURCE_DIR}/src 
                           ${CMAKE_CURRENT_SOURCE_DIR}/include 
                           ${CMAKE_CURRENT_SOURCE_DIR}/lib)


if(MSVC)
    add_compile_options("/W4" "$<$<CONFIG:RELEASE>:/O2>")
else()
    add_compile_options("-Wall" "-Wextra" "-Werror" "$<$<CONFIG:RELEASE>:-O3>")
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        add_compile_options("-stdlib=libc++")
    else()
        # GCC compile options...
    endif()
endif()