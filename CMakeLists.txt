cmake_minimum_required(VERSION 3.21)
project(collision-detection-box2d-3.1.1-sdl-3.3.4-c)
add_executable(app)

# Specify where the application source files are stored
target_sources(app
PRIVATE
    src/box2d-contact-listener.h
    src/box2d-debug-drawer.h
    src/main.c
)

# Check for WebAssembly
if (CMAKE_SYSTEM_NAME MATCHES "Emscripten")
    target_link_options("app" PRIVATE "SHELL:--embed-file ${CMAKE_CURRENT_SOURCE_DIR}/assets/fonts/LiberationSans-Regular.ttf@/assets/fonts/LiberationSans-Regular.ttf")
    set_property(TARGET "app" APPEND PROPERTY LINK_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/assets/fonts/LiberationSans-Regular.ttf")
endif()

# Check for Windows
if (WIN32)
    target_link_options(app PRIVATE -static)
endif()

find_package(box2d)
find_package(SDL3)
find_package(SDL3_ttf)
target_link_libraries(app PRIVATE box2d::box2d SDL3_ttf::SDL3_ttf SDL3::SDL3)

# For comments:
#[===[
# Some content here
#]===]
