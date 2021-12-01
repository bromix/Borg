project(Borg VERSION 0.0.1)

add_library(${PROJECT_NAME} STATIC "")

target_compile_features(${PROJECT_NAME}
    PUBLIC
        cxx_std_17
)

file(GLOB BORG_HEADER_FILES "include/Borg/*.h")
file(GLOB BORG_SOURCE_FILES "src/*.cpp" "src/*.h")
target_sources(${PROJECT_NAME}
    PRIVATE
        ${BORG_HEADER_FILES}
        ${BORG_SOURCE_FILES}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> # Build-Tree
        $<INSTALL_INTERFACE:include/${PROJECT_NAME}>           # Install-Tree
)

# include platform specific sources.
add_subdirectory(src/Platform)

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${BORG_HEADER_FILES}")
include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
)
