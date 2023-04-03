#pragma once

#include <glad/glad.h>
#include <glm.hpp>
#include "texture.h"
#include "spriterenderer.h"

class GameObject
{
public:
	glm::vec2 position, size, velocity;
	glm::vec3 color;
	float rotation;
	bool isSolid;
	bool destroyed;
	Texture2D sprite;
	GameObject();
	GameObject(glm::vec2 pos, glm::vec2 siz, Texture2D spr, glm::vec3 col = glm::vec3(1.0f), glm::vec2 vel = glm::vec2(0.0f, 0.0f));
	virtual void draw(SpriteRenderer& renderer);
};