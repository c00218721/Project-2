#include "Player.h"



Player::Player()
{

}


Player::~Player()
{
}

void Player::init(int t_x, int t_y, int t_z)
{
	cube = glm::translate(cube, glm::vec3(t_x, t_y, t_z));
}

void Player::loadIdentity()
{
	cube = glm::mat4(
		1.0f					// Identity Matrix
	);
}

void Player::setCube(glm::mat4 t_mat)
{
	cube = t_mat;
}

glm::mat4 Player::getModel() const
{
	return cube;
}
