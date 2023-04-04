#pragma once

#include <glad/glad.h>
#include <glm.hpp>

#include "gameobject.h"
#include "texture.h"

class BallObject : public GameObject
{
public:
	float radius;
	bool stuck;

	BallObject();
	BallObject(glm::vec2 pos, float rad, glm::vec2 vel, Texture2D spr);
	glm::vec2 Move(float dt, unsigned int windowWidth);
	void reset(glm::vec2 pos, glm::vec2 vel);
};