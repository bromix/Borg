file(GLOB_RECURSE BORG_SOURCE_FILES "*.cpp" "*.h")
target_sources(${PROJECT_NAME}
    PRIVATE
        ${BORG_SOURCE_FILES}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Wininet
)