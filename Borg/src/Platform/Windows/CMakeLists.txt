file(GLOB_RECURSE BORG_SOURCE_FILES "*.cpp" "*.h")
target_sources(${PROJECT_NAME}
    PRIVATE
        ${BORG_SOURCE_FILES}
)

# Windows should be used with UNICODE.
target_compile_definitions(${PROJECT_NAME}
PUBLIC
    UNICODE _UNICODE
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Comctl32
        Shcore
        Wininet
)