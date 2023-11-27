add_library(physic_engine STATIC vector.c collision.c force.c physic_object.c world.c)
target_include_directories(physic_engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
