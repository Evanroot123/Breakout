#include "Game.h"
#include "resourcemanager.h"
#include "spriterenderer.h"
#include "ballobject.h"

SpriteRenderer* renderer;
GameObject* player;
BallObject* ball;

const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
const float BALL_RADIUS = 12.5f;

Game::Game(unsigned int wid, unsigned int hei) :
	state(GAME_ACTIVE), keys(), width(wid), height(hei)
{

}

Game::~Game()
{
	delete renderer;
	delete player;
	delete ball;
}

void Game::init()
{
	ResourceManager::loadShader("..//Shaders//sprite.vert", "..//Shaders//sprite.frag", nullptr, "sprite");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);
	ResourceManager::getShader("sprite").use().setInteger("image", 0);
	ResourceManager::getShader("sprite").setMatrix4f("projection", projection);
	renderer = new SpriteRenderer(ResourceManager::getShader("sprite"));
	ResourceManager::loadTexture("..//Resources//Sprites//background.jpg", false, "background");
	ResourceManager::loadTexture("..//Resources//Sprites//awesomeface.png", true, "face");
	ResourceManager::loadTexture("..//Resources//Sprites//block.png", false, "block");
	ResourceManager::loadTexture("..//Resources//Sprites//block_solid.png", false, "blockSolid");
	ResourceManager::loadTexture("..//Resources//Sprites//paddle.png", true, "paddle");

	// levels
	GameLevel one; one.load("..//Resources//Levels//one.lvl", width, height / 2);
	GameLevel two; two.load("..//Resources//Levels//two.lvl", width, height / 2);
	GameLevel three; three.load("..//Resources//Levels//three.lvl", width, height / 2);
	GameLevel four; four.load("..//Resources//Levels//four.lvl", width, height / 2);
	levels.push_back(one);
	levels.push_back(two);
	levels.push_back(three);
	levels.push_back(four);
	level = 0;

	glm::vec2 playerPos = glm::vec2(width / 2.0f - PLAYER_SIZE.x / 2.0f, height - PLAYER_SIZE.y);
	player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::getTexture("paddle"));
	glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -BALL_RADIUS * 2.0f);
	ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::getTexture("face"));
}

void Game::update(float dt)
{
	ball->Move(dt, width);
}

void Game::processInput(float dt)
{
	if (state == GAME_ACTIVE)
	{
		float velocity = PLAYER_VELOCITY * dt;

		if (keys[GLFW_KEY_A])
		{
			if (player->position.x >= 0.0f)
			{
				player->position.x -= velocity;
				if (ball->stuck)
					ball->position.x -= velocity;
			}
		}
		if (keys[GLFW_KEY_D])
		{
			if (player->position.x <= width - player->size.x)
			{
				player->position.x += velocity;
				if (ball->stuck)
					ball->position.x += velocity;
			}
		}
		if (keys[GLFW_KEY_SPACE])
		{
			ball->stuck = false;
		}
	}
}

void Game::render()
{
	if (state == GAME_ACTIVE)
	{
		renderer->drawSprite(ResourceManager::getTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(width, height), 0.0f);
		levels[level].draw(*renderer);
		player->draw(*renderer);
		ball->draw(*renderer);
	}
}