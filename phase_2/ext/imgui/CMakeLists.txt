# set(SFML_STATIC_LIBRARIES TRUE)  # Commented out to use dynamic libraries

set(SOURCES
	imgui.cpp
	imgui_demo.cpp
	imgui_draw.cpp
	imgui_widgets.cpp
	misc/cpp/imgui_stdlib.cpp
	imgui-sfml/imgui-SFML.cpp
)

add_library(imgui ${SOURCES})
target_include_directories(imgui PUBLIC . misc/cpp imgui-sfml)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

if(SFML_FOUND)
	target_include_directories(imgui PUBLIC ${SFML_INCLUDE_DIR})
	target_link_libraries(imgui sfml-graphics)
endif()
