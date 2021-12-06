file(GLOB BORG_SOURCE_FILES "*.cpp" "*.h")
target_sources(${PROJECT_NAME}
    PRIVATE
        ${BORG_SOURCE_FILES}
)