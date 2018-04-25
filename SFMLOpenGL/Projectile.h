#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

class Projectile
{
public:
	Projectile();
	~Projectile();

	void init();

	void loadIdentity();
	void setCube(glm::mat4 t_mat);
	void goToPlayer(glm::mat4 t_mat);
	glm::mat4 getModel() const;

private:
	glm::mat4 cube;
	glm::vec3 rotation, location;
};