#include "gameobject.h"

GameObject::GameObject() :
	position(0.0f, 0.0f), size(1.0f, 1.0f), velocity(0.0f), color(1.0f), rotation(0.0f), sprite(), isSolid(false), destroyed(false)
{

}

GameObject::GameObject(glm::vec2 pos, glm::vec2 siz, Texture2D spr, glm::vec3 col, glm::vec2 vel) :
	position(pos), size(siz), velocity(vel), color(col), rotation(0.0f), sprite(spr), isSolid(false), destroyed(false)
{

}

void GameObject::draw(SpriteRenderer& renderer)
{
	renderer.drawSprite(sprite, position, size, rotation, color);
}