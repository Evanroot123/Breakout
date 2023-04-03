#pragma once

#include <vector>
#include <glad/glad.h>
#include <glm.hpp>
#include "gameobject.h"
#include "spriterenderer.h"
#include "resourcemanager.h"

class GameLevel
{
public:
	std::vector<GameObject> bricks;
	GameLevel() {}
	void load(const char* file, unsigned int levelWidth, unsigned int levelHeight);
	void draw(SpriteRenderer& renderer);
	bool isCompleted();
private:
	void init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight);
};