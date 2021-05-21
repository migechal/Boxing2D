file(GLOB sources "*.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC ../header/)

add_library(
            source
            ${sources}
            )
