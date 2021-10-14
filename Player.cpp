#include "Player.h"

//Initializer functions
void Player::initVariable()
{
}

void Player::initComponents()
{
	this->createMovementComponent(200.f, 10.f, 4.f);
}

//Constructor / Destructors
Player::Player(float x, float y, sf::Texture& texture)
{
	this->initVariable();
	this->initComponents();

	this->setTexture(texture);
	this->setPosition(x, y);
}

Player::~Player()
{
}
