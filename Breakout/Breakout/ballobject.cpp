#include "ballobject.h"

BallObject::BallObject() :
	GameObject(), radius(12.5f), stuck(true)
{

}

BallObject::BallObject(glm::vec2 pos, float rad, glm::vec2 vel, Texture2D spr) :
	GameObject(pos, glm::vec2(rad * 2.0f, rad * 2.0f), spr, glm::vec3(1.0f), vel), radius(rad), stuck(true)
{

}

glm::vec2 BallObject::Move(float dt, unsigned int windowWidth)
{
	if (!stuck)
	{
		position += velocity * dt;
		if (position.x <= 0.0f)
		{
			velocity.x = -velocity.x;
			position.x = 0.0f;
		}
		else if (position.x + size.x >= windowWidth)
		{
			velocity.x = -velocity.x;
			position.x = windowWidth - size.x;
		}
		if (position.y <= 0.0f)
		{
			velocity.y = -velocity.y;
			position.y = 0.0f;
		}
	}

	return position;
}

void BallObject::reset(glm::vec2 pos, glm::vec2 vel)
{
	position = pos;
	velocity = vel;
	stuck = true;
}