cmake_minimum_required(VERSION 3.5)
project(physic)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/physic_engine)
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/graphic_engine)

add_executable(main main.c)
target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(main LINK_PUBLIC physic_engine)
