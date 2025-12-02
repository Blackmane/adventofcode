add_executable (01 main.cpp 01.cpp)
target_link_libraries(01 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
target_include_directories(01 PRIVATE ${CMAKE_SOURCE_DIR}/common)

if (ENABLE_PRINT_TIMING)
    add_definitions(-DPRINT_TIMING)
endif ()

if (ENABLE_TESTING)
    add_executable(test_01 $<TARGET_OBJECTS:MAIN_objs> test.cpp 01.cpp)
    target_link_libraries(test_01 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
    target_include_directories(test_01 PRIVATE ${CMAKE_SOURCE_DIR}/common)
    add_test(NAME 01_test COMMAND test_01)
endif ()

