# ===== ===== ===== Build Library ===== ===== =====
add_library(COMMON_objs OBJECT common.h common.cpp)


if (ENABLE_TESTING OR ENABLE_COMMON_TESTING)
    # ===== ===== ===== Main Obj ===== ===== =====
    add_library(MAIN_objs OBJECT main_catch.cpp)
    # target_compile_features(MAIN_objs PUBLIC cxx_std_11)
endif ()

# Test Common
if (ENABLE_COMMON_TESTING)
    add_executable(test_common $<TARGET_OBJECTS:COMMON_objs> $<TARGET_OBJECTS:MAIN_objs> test_common.cpp)
    #target_include_directories(test_common PRIVATE ${CMAKE_SOURCE_DIR}/common)
    add_test(NAME common_test COMMAND test_common)
endif ()