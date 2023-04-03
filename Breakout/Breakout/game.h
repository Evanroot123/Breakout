#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

enum GameState {GAME_ACTIVE, GAME_MENU, GAME_WIN};

class Game
{
public:
	GameState state;
	bool keys[1024];
	unsigned int width, height;

	Game(unsigned int wid, unsigned hei);
	~Game();

	void init();
	void processInput(float dt);
	void update(float dt);
	void render();
};