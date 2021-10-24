#include "stdafx.h"
#include "Player.h"
//Initializer functions
void Player::initVariable()
{
	this->attacking = false;
}

void Player::initComponents()
{
}

//Constructor / Destructors
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariable();

	this->setPosition(x, y);
	
	this->createHitboxComponent(this->sprite, 15.f, 11.f, 33.f, 53.f);
	this->createMovementComponent(350.f, 15.f, 5.f);
	this->createAnimationComponent(texture_sheet);

	//this->animationComponent->addAnimation("IDLE", 10.f, 0, 0, 14, 0, 616, 566);
	//this->animationComponent->addAnimation("WALK", 10.f, 0, 1, 14, 1, 616, 566);

	this->animationComponent->addAnimation("IDLE", 60.f, 0, 6, 7, 6, 64, 64);
	this->animationComponent->addAnimation("WALK_UP", 6.f, 0, 10, 8, 10, 64, 64);
	this->animationComponent->addAnimation("WALK_DOWN", 6.f, 0, 8, 8, 8, 64, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 6.f, 0, 9, 8, 9, 64, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 6.f, 0, 11, 8, 11, 64, 64);
	this->animationComponent->addAnimation("ATTACK_LEFT", 5.f, 0, 25, 5, 25, 64 * 3, 64);
	this->animationComponent->addAnimation("ATTACK_RIGHT", 5.f, 0, 31, 5, 31, 64 * 3, 64);
	
}

Player::~Player()
{

}

//Funtions
void Player::updateAttack()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->attacking = true;
	}
}

void Player::updateAnimation(const float& dt)
{
	if (this->attacking)
	{
		//set origin depending on direction
		if (this->sprite.getScale().x > 0.f) //Facing left
		{
			this->sprite.setOrigin(64.f, 0.f);
		}
		else //Facing right
		{
			this->sprite.setOrigin(64.f + 64.f, 0.f);
		}
		//Animate and check for animation end
		if (this->animationComponent->play("ATTACK_LEFT", dt, true))
		{
			this->attacking = false;

			if (this->sprite.getScale().x > 0.f) //Facing left
			{
				this->sprite.setOrigin(0.f, 0.f);
			}
			else //Facing right
			{
				this->sprite.setOrigin(64.f, 0.f);
			}
		}
	}

	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("WALK_UP", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("WALK_DOWN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		if (this->sprite.getScale().x < 0.f)
		{
			this->sprite.setOrigin(0.f, 0.f);
			this->sprite.setScale(1.f, 1.f);
		}

		this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		if (this->sprite.getScale().x > 0.f)
		{
			this->sprite.setOrigin(64.f, 0.f);
			this->sprite.setScale(-1.f, 1.f);
		}

		this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
}

void Player::update(const float& dt)
{
	this->movementComponent->update(dt);

	this->updateAttack();
	
	this->updateAnimation(dt);

	this->hitboxComponent->update();
}
