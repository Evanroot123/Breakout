#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "gamelevel.h"

enum GameState {GAME_ACTIVE, GAME_MENU, GAME_WIN};

const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
const float PLAYER_VELOCITY(500.0f);

class Game
{
public:
	GameState state;
	bool keys[1024];
	unsigned int width, height;
	std::vector<GameLevel> levels;
	unsigned int level;

	Game(unsigned int wid, unsigned hei);
	~Game();

	void init();
	void processInput(float dt);
	void update(float dt);
	void render();
};