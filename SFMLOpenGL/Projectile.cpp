#include "Projectile.h"



Projectile::Projectile()
{
}


Projectile::~Projectile()
{
}

void Projectile::init()
{
	cube = glm::scale(cube, glm::vec3(0.5, 0.5, 0.5));
}

void Projectile::loadIdentity()
{
	cube = glm::mat4(
		1.0f					// Identity Matrix
	);
}

void Projectile::setCube(glm::mat4 t_mat)
{
	cube = t_mat;
}

void Projectile::goToPlayer(glm::mat4 t_mat)
{
	cube[3] = t_mat[3];
}

glm::mat4 Projectile::getModel() const
{
	return cube;
}
