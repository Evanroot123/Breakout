#include "Game.h"
#include "resourcemanager.h"
#include "spriterenderer.h"

SpriteRenderer* renderer;

Game::Game(unsigned int wid, unsigned int hei) :
	state(GAME_ACTIVE), keys(), width(wid), height(hei)
{

}

Game::~Game()
{
	delete renderer;
}

void Game::init()
{
	ResourceManager::loadShader("..//Shaders//sprite.vert", "..//Shaders//sprite.frag", nullptr, "sprite");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);
	ResourceManager::getShader("sprite").use().setInteger("image", 0);
	ResourceManager::getShader("sprite").setMatrix4f("projection", projection);
	renderer = new SpriteRenderer(ResourceManager::getShader("sprite"));
	ResourceManager::loadTexture("..//Resources//Sprites//awesomeface.png", true, "face");
}

void Game::update(float dt)
{

}

void Game::processInput(float dt)
{

}

void Game::render()
{
	renderer->drawSprite(ResourceManager::getTexture("face"), glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}