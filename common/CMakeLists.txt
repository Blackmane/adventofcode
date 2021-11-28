# ===== ===== ===== Build Library ===== ===== =====

if (ENABLE_TESTING)
    # ===== ===== ===== Main Obj ===== ===== =====
    add_library(MAIN_objs OBJECT main_catch.cpp)
    # target_compile_features(MAIN_objs PUBLIC cxx_std_11)
endif ()
