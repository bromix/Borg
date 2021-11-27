project(Tests VERSION 0.0.1)

add_executable(${PROJECT_NAME} "")

target_sources(${PROJECT_NAME}
    PRIVATE
        test_string.cpp
)

# target_compile_features(${PROJECT_NAME}
#     PUBLIC
#         cxx_std_17
# )

find_package(GTest CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
        GTest::gtest GTest::gtest_main
        Borg
)
