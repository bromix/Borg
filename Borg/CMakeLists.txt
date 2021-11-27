project(Borg VERSION 0.0.1)

add_library(${PROJECT_NAME} STATIC "")

target_compile_features(${PROJECT_NAME}
    PUBLIC
        cxx_std_17
)

target_sources(${PROJECT_NAME}
    PRIVATE
        "include/Borg/Base.h"

        "include/Borg/String.h"
        "src/String.cpp"
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> # Build-Tree
        $<INSTALL_INTERFACE:include/Borg>                      # Install-Tree
)

# include platform specific sources.
add_subdirectory(src/Platform)

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "include/Borg/Base.h")
include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Borg
)
