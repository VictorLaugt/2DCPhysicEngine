add_library(physic_engine STATIC force.c geometry.c physic_object.c vector.c world.c)
target_include_directories(physic_engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
