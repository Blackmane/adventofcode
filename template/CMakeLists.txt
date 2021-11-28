add_executable ($DAY main.cpp $DAY.cpp)
target_link_libraries($DAY PRIVATE $$<TARGET_OBJECTS:COMMON_objs> )
target_include_directories($DAY PRIVATE $${CMAKE_SOURCE_DIR}/common)

if (ENABLE_TESTING)
    add_executable($TEST $$<TARGET_OBJECTS:MAIN_objs> test.cpp $DAY.cpp)
    target_link_libraries($TEST PRIVATE $$<TARGET_OBJECTS:COMMON_objs> )
    target_include_directories($TEST PRIVATE $${CMAKE_SOURCE_DIR}/common)
    add_test(NAME $TESTCOMMAND COMMAND $TEST)
endif ()

