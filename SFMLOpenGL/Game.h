#ifndef GAME_H
#define GAME_H

#include <string>
#include <sstream>

#include <iostream>
#include <GL/glew.h>
#include <GL/wglew.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include <Debug.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <textfile.h>

#include <Player.h>
#include <Projectile.h>
#include <Goal.h>

class Game
{
public:
	Game();
	Game(sf::ContextSettings settings);
	~Game();
	void run();
private:
	sf::RenderWindow m_window;
	int m_lives = 5;
	int m_score = 0;
	bool moving = false;
	bool m_exitGame = false;

	bool isRunning = false;
	void initialize();
	void update(sf::Time t_deltaTime);
	void processEvents();
	void render();
	void unload();
	void checkCollsions();
	void doInput(sf::Time t_deltaTime);
	void setShader();	//przemek helped with loading shaders from the file
	void changeGoal();
	void loadIdentities();
	void drawCubes();
	void initCubes();

	Player m_playerModel;
	Projectile m_bulletCube;
	Goal m_scoreArea;
};

#endif  // ! GAME_H