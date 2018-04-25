#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 


#include <Game.h>

int main(void)
{
	// Setup SFML Context Settings
	// https://www.sfml-dev.org/documentation/2.0/ContextSettings_8hpp_source.php
	sf::ContextSettings settings;
	settings.depthBits = 24u; // for depth buffer Z-Buffer
	settings.antialiasingLevel = 4u;

	std::srand(time(NULL));

	// Create a reference to the game and run
	Game& game = Game(settings);
	game.run();
}