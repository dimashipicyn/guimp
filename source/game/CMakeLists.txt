target_sources(${PROJECT_NAME}
PRIVATE
	game_app.h
	game_app.cpp
	game_state.h
	game_state.cpp
)

add_subdirectory(ui/components)