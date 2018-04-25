#include "Goal.h"
#include <iostream>


Goal::Goal()
{
}


Goal::~Goal()
{
}

void Goal::init()
{
	newPositipon();
	timer = sf::Time::Zero;
	
	switch (position)
	{
	case 1:
		cube = glm::translate(cube, glm::vec3(-5, 0, -15));
		break;
	case 2:
		cube = glm::translate(cube, glm::vec3(0, 0, -15));
		break;
	case 3:
		cube = glm::translate(cube, glm::vec3(5, 0, -15));
		break;
	default:
		break;
	}
}

void Goal::loadIdentity()
{
	cube = glm::mat4(
		1.0f// goal Matrix
	);
}

void Goal::setCube(glm::mat4 t_mat)
{
	cube = t_mat;
}

glm::mat4 Goal::getModel()
{
	return cube;
}

int Goal::getPosition()
{
	return position;
}

void Goal::newPositipon()
{
	position = std::rand() % (3 - 1 + 1) + 1;
}

bool Goal::positionTimer(sf::Time t_deltaTime)
{
	if (timer.asSeconds() > 2.0f)
	{
		timer = sf::Time::Zero;
		return true;
	}
	else
	{
		timer += t_deltaTime;
		return false;
	}
}
