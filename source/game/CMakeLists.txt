target_sources(${PROJECT_NAME}
PRIVATE
	game_app.h
	game_app.cpp
	signal.h
	canvas.h
	canvas.cpp
)

add_subdirectory(ui/components)
add_subdirectory(tools)