cmake_minimum_required(VERSION 3.0)
project(ascii_art_renderer)

set(CMAKE_CXX_STANDARD 23)

find_package(OpenCV REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(ascii 
	main.cpp
	video_ascii.cpp
	image_ascii.cpp
)

target_include_directories(ascii PRIVATE
    ${OpenCV_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}  # Include the project root directory
)



target_link_libraries(ascii PRIVATE ${OpenCV_LIBS})

