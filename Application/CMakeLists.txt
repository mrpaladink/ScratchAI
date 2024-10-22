cmake_minimum_required(VERSION 3.5.0)

# Project Settings
project(scratchai)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set(SOURCE_FILES src/main.cpp src/MainLoop.cpp src/Logger.cpp src/RenderWindow.cpp src/RenderElement.cpp src/Texture.cpp src/Image.cpp src/Font.cpp src/VectorGraphic.cpp src/Vector2.cpp src/Mouse.cpp src/Keyboard.cpp src/File.cpp src/TextInput.cpp src/RenderBox.cpp src/GUI/Edit.cpp)
set(HEADER_FILES include/MainLoop.hpp include/Logger.hpp include/RenderWindow.hpp include/RenderElement.hpp include/Texture.hpp include/Image.hpp include/Font.hpp include/VectorGraphic.hpp include/Vector2.hpp include/Rect.hpp include/Mouse.hpp include/Keyboard.hpp include/File.hpp include/TextInput.hpp include/RenderBox.hpp include/GUI/Edit.hpp)

# SDL
add_subdirectory(libs/SDL)

# Executable
add_executable(scratchai ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(scratchai PUBLIC libs/SDL/include)
target_include_directories(scratchai PUBLIC include/)
target_include_directories(scratchai PUBLIC libs/)
target_link_libraries(scratchai PUBLIC SDL3::SDL3)