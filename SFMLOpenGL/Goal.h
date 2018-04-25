#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include <SFML\Graphics.hpp>

class Goal
{
public:
	Goal();
	~Goal();

	void init();
	void loadIdentity();
	void setCube(glm::mat4 t_mat);
	int getPosition();
	glm::mat4 getModel();
	void newPositipon();
	bool positionTimer(sf::Time t_deltaTime);

private:
	int position; //variable to store position numbers corresopond to left right and middle
	sf::Time timer;	
	glm::mat4 cube;
};