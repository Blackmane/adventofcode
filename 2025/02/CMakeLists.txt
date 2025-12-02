add_executable (02 main.cpp 02.cpp)
target_link_libraries(02 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
target_include_directories(02 PRIVATE ${CMAKE_SOURCE_DIR}/common)

if (ENABLE_PRINT_TIMING)
    add_definitions(-DPRINT_TIMING)
endif ()

if (ENABLE_TESTING)
    add_executable(test_02 $<TARGET_OBJECTS:MAIN_objs> test.cpp 02.cpp)
    target_link_libraries(test_02 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
    target_include_directories(test_02 PRIVATE ${CMAKE_SOURCE_DIR}/common)
    add_test(NAME 02_test COMMAND test_02)
endif ()

