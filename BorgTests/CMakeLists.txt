project(BorgTests VERSION 0.0.1)

add_executable(${PROJECT_NAME} "")

file(GLOB_RECURSE BORG_TEST_FILES "test_*.cpp")

target_sources(${PROJECT_NAME}
    PRIVATE
        ${BORG_TEST_FILES}
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
