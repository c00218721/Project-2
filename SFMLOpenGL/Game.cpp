#include <Game.h>
#include <Cube.h>

// Helper to convert Number to String for HUD
template <typename T>
std::string toString(T number)
{
	std::ostringstream oss;
	oss << number;
	return oss.str();
}

GLuint	vertShader,
		fragShader,
		progID,		// Program ID
		vao = 0,	// Vertex Array ID
		vbo,		// Vertex Buffer ID
		vib,		// Vertex Index Buffer
		to[1];		// Texture ID
GLint	positionID,	// Position ID
		colorID,	// Color ID
		mvpID[3],	// Model View Projection ID
		textureID,	// Texture ID
		uvID,		// UV ID
		x_offsetID, // X offset ID
		y_offsetID,	// Y offset ID
		z_offsetID;	// Z offset ID

GLenum	error;		// OpenGL Error Code

int width;				
int height;					
int comp_count;					
const int PLAYER = 0;
const int PROJ = 1;
const int GOAL = 2;
const std::string filename = ".//Assets//Textures//cube.tga"; //opens texture from file
float x_offset, y_offset, z_offset; // offset on screen (Vertex Shader)


unsigned char* img_data;		// image data

glm::mat4 mvp[3], projection, view;	// Model View Projectio
sf::Font font;						// Game font


Game::Game() : 
	m_window(sf::VideoMode(800, 600),	"Introduction to OpenGL Texturing")
{
}

Game::Game(sf::ContextSettings settings) : 
	m_window(sf::VideoMode(800, 600), 
	"Introduction to OpenGL Texturing", 
	sf::Style::Default, 
	settings)
{
}

Game::~Game()
{
}

void Game::run()
{
	initialize();

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps
	while (m_window.isOpen())
	{
#if (DEBUG >= 2)
		DEBUG_MSG("Game running...");
#endif
		processEvents(); // as many as possible


		timeSinceLastUpdate += clock.restart();

		while (timeSinceLastUpdate > timePerFrame && isRunning)
		{

			timeSinceLastUpdate -= timePerFrame;

			processEvents(); // as many as possible
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}

}

void Game::processEvents()
{
	sf::Event event;

	while (m_window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type) // window message
		{
#if (DEBUG >= 2)
			DEBUG_MSG("Calling Cleanup...");
#endif
			unload();
			m_window.close();
		}

		if (sf::Event::KeyPressed == event.type) //user key press
		{
			if (sf::Keyboard::Escape == event.key.code)
			{
				m_exitGame = true;

			}


		}
	}
}

void Game::initialize()
{
	isRunning = true;
	GLint isCompiled = 0;
	GLint isLinked = 0;

	if (!glewInit()) { DEBUG_MSG("glewInit() failed"); }

	DEBUG_MSG(glGetString(GL_VENDOR));
	DEBUG_MSG(glGetString(GL_RENDERER));
	DEBUG_MSG(glGetString(GL_VERSION));

	// Vertex Array Buffer
	glGenBuffers(1, &vbo);		// Generate Vertex Buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Vertices (3) x,y,z , Colors (4) RGBA, UV/ST (2)
	glBufferData(GL_ARRAY_BUFFER, ((3 * VERTICES) + (4 * COLORS) + (2 * UVS)) * sizeof(GLfloat), NULL, GL_STATIC_DRAW);

	glGenBuffers(1, &vib); //Generate Vertex Index Buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vib);

	// Indices to be drawn
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * INDICES * sizeof(GLuint), indices, GL_STATIC_DRAW);

	setShader();
	
	// Set image data
	// https://github.com/nothings/stb/blob/master/stb_image.h
	img_data = stbi_load(filename.c_str(), &width, &height, &comp_count, 4);

	if (img_data == NULL)
	{
		DEBUG_MSG("ERROR: Texture not loaded");
	}

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &to[0]);
	glBindTexture(GL_TEXTURE_2D, to[0]);

	// Wrap around
	// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	// Filtering
	// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Camera Matrix
	view = glm::lookAt(
		glm::vec3(0.0f, 4.0f, 10.0f),	// Camera (x,y,z), in World Space
		glm::vec3(0.0f, 0.0f, 0.0f),		// Camera looking at origin
		glm::vec3(0.0f, 1.0f, 0.0f)		// 0.0f, 1.0f, 0.0f Look Down and 0.0f, -1.0f, 0.0f Look Up
	);

	// Bind to OpenGL
	// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexImage2D.xml
	glTexImage2D(
		GL_TEXTURE_2D,			// 2D Texture Image
		0,						// Mipmapping Level 
		GL_RGBA,				// GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_BGR, GL_RGBA 
		width,					// Width
		height,					// Height
		0,						// Border
		GL_RGBA,				// Bitmap
		GL_UNSIGNED_BYTE,		// Specifies Data type of image data
		img_data				// Image Data
		);

	// Projection Matrix 
	projection = glm::perspective(
		45.0f,					// Field of View 45 degrees
		4.0f / 3.0f,			// Aspect ratio
		5.0f,					// Display Range Min : 0.1f unit
		100.0f					// Display Range Max : 100.0f unit
		);




	// Enable Depth Test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

	// Load Font
	font.loadFromFile(".//Assets//Fonts//BBrick.ttf");

	initCubes();
}

void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		unload();
		m_window.close();
	}

	doInput(t_deltaTime);

	if (moving && 
		glm::distance(glm::vec3(m_bulletCube.getModel()[3].x, m_bulletCube.getModel()[3].y, m_bulletCube.getModel()[3].z), glm::vec3(m_playerModel.getModel()[3].x , m_playerModel.getModel()[3].y, m_playerModel.getModel()[3].z)) <= 20)
	{
		glm::mat4 mat = glm::translate(m_bulletCube.getModel(), glm::vec3(0, 0, -0.075 * t_deltaTime.asMilliseconds()));
		m_bulletCube.setCube(mat);
		checkCollsions();
	}
	else if (glm::distance(glm::vec3(m_bulletCube.getModel()[3].x, m_bulletCube.getModel()[3].y, m_bulletCube.getModel()[3].z), glm::vec3(m_playerModel.getModel()[3].x, m_playerModel.getModel()[3].y, m_playerModel.getModel()[3].z)) > 20 && moving)
	{
		moving = false;
		m_lives--;
	}

	#if (DEBUG >= 2)
	DEBUG_MSG("Updating...");
	#endif
	// Update Model View Projection
	// For mutiple objects (cubes) create multiple models
	// To alter Camera modify view & projection
	mvp[PLAYER] = projection * view * m_playerModel.getModel();
	mvp[PROJ] = projection * view * m_bulletCube.getModel();
	mvp[GOAL] = projection * view * m_scoreArea.getModel();

	if (m_lives < 0)
	{
		initCubes();
	}

	if (m_scoreArea.positionTimer(t_deltaTime))
	{
		changeGoal();
	}
	else
	{
		glm::mat4 mat = glm::rotate(m_scoreArea.getModel(), 0.4f * t_deltaTime.asMilliseconds(), glm::vec3(0.0f, 1.0f, 0.0f));
		m_scoreArea.setCube(mat);
	}
}

void Game::render()
{

#if (DEBUG >= 2)
	DEBUG_MSG("Render Loop...");
#endif

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Save current OpenGL render states
	// https://www.sfml-dev.org/documentation/2.0/classsf_1_1RenderTarget.php#a8d1998464ccc54e789aaf990242b47f7
	m_window.pushGLStates();

	std::string hud = "lives: "	+ std::to_string(m_lives) + "                             score: " + std::to_string(m_score);


	sf::Text text(hud, font);
	
	text.setColor(sf::Color(255, 255, 255, 170));
	text.setPosition(25.f, 25.f);


	m_window.draw(text);


	// Restore OpenGL render states
	// https://www.sfml-dev.org/documentation/2.0/classsf_1_1RenderTarget.php#a8d1998464ccc54e789aaf990242b47f7

	m_window.popGLStates();

	// Rebind Buffers and then set SubData
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vib);

	// Use Progam on GPU
	glUseProgram(progID);

	drawCubes();

	m_window.display();

	// Disable Arrays
	glDisableVertexAttribArray(positionID);
	//glDisableVertexAttribArray(colorID);
	glDisableVertexAttribArray(uvID);

	// Unbind Buffers with 0 (Resets OpenGL States...important step)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Reset the Shader Program to Use
	glUseProgram(0);

	// Check for OpenGL Error code
	error = glGetError();
	if (error != GL_NO_ERROR) {
		DEBUG_MSG(error);
	}
}

void Game::unload()
{
#if (DEBUG >= 2)
	DEBUG_MSG("Cleaning up...");
#endif
	glDetachShader(progID, vertShader);	// Shader could be used with more than one progID
	glDetachShader(progID, fragShader);	// ..
	glDeleteShader(vertShader);			// Delete Vertex Shader
	glDeleteShader(fragShader);			// Delete Fragment Shader
	glDeleteProgram(progID);		// Delete Shader
	
	glDeleteBuffers(1, &vbo);		// Delete Vertex Buffer
	glDeleteBuffers(1, &vib);		// Delete Vertex Index Buffer
	stbi_image_free(img_data);		// Free image stbi_image_free(..)
}

void Game::checkCollsions()
{
	if (glm::distance(glm::vec3(m_bulletCube.getModel()[3].x,
								m_bulletCube.getModel()[3].y,
								m_bulletCube.getModel()[3].z),
								glm::vec3(-5, 0, -15)) <= 1.5f)
	{//checks idistance of goal from cube
		if (m_scoreArea.getPosition() == 1)
		{
			m_score += 100;
			changeGoal();
			moving = false;
		}	
	}
	
	if (glm::distance(glm::vec3(m_bulletCube.getModel()[3].x,
								m_bulletCube.getModel()[3].y,
								m_bulletCube.getModel()[3].z),
								glm::vec3(0, 0, -15)) <= 1.5f)
	{
		if (m_scoreArea.getPosition() == 2)
		{
			m_score += 100;
			changeGoal();
			moving = false;
		}
	}
	
	if (glm::distance(glm::vec3(m_bulletCube.getModel()[3].x,
								m_bulletCube.getModel()[3].y,
								m_bulletCube.getModel()[3].z),
								glm::vec3(5, 0, -15)) <= 1.5f)
	{
		if (m_scoreArea.getPosition() == 3)
		{
			m_score += 100;
			changeGoal();
			moving = false;
		}
	}
}

void Game::changeGoal()
{
	m_scoreArea.loadIdentity();
	
	m_scoreArea.init();
}

void Game::loadIdentities()
{
	m_playerModel.loadIdentity(); 
	m_bulletCube.loadIdentity();
	m_scoreArea.loadIdentity();
}

void Game::drawCubes()
{
	// Find variables within the shader	
	// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetAttribLocation.xml
	positionID = glGetAttribLocation(progID, "sv_position");
	if (positionID < 0) { DEBUG_MSG("positionID not found"); }

	uvID = glGetAttribLocation(progID, "sv_uv");
	if (uvID < 0) { DEBUG_MSG("uvID not found"); }

	textureID = glGetUniformLocation(progID, "f_texture");
	if (textureID < 0) { DEBUG_MSG("textureID not found"); }

	mvpID[PLAYER] = glGetUniformLocation(progID, "sv_mvp");
	if (mvpID < 0) { DEBUG_MSG("mvpID not found"); }

	x_offsetID = glGetUniformLocation(progID, "sv_x_offset");
	if (x_offsetID < 0) { DEBUG_MSG("x_offsetID not found"); }

	y_offsetID = glGetUniformLocation(progID, "sv_y_offset");
	if (y_offsetID < 0) { DEBUG_MSG("y_offsetID not found"); }

	z_offsetID = glGetUniformLocation(progID, "sv_z_offset");
	if (z_offsetID < 0) { DEBUG_MSG("z_offsetID not found"); };

	// VBO Data....vertices, colors and UV's appended
	glBufferSubData(GL_ARRAY_BUFFER, 0 * VERTICES * sizeof(GLfloat), 3 * VERTICES * sizeof(GLfloat), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, 3 * VERTICES * sizeof(GLfloat), 4 * COLORS * sizeof(GLfloat), colors);
	glBufferSubData(GL_ARRAY_BUFFER, ((3 * VERTICES) + (4 * COLORS)) * sizeof(GLfloat), 2 * UVS * sizeof(GLfloat), uvs);

	// Send transformation to shader mvp uniform [0][0] is start of array
	glUniformMatrix4fv(mvpID[PLAYER], 1, GL_FALSE, &mvp[PLAYER][0][0]);

	// Set Active Texture .... 32 GL_TEXTURE0 .... GL_TEXTURE31
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(textureID, 0); // 0 .... 31

	// Set the X, Y and Z offset (this allows for multiple cubes via different shaders)
	// Experiment with these values to change screen positions
	glUniform1f(x_offsetID, 0.00f);
	glUniform1f(y_offsetID, 0.00f);
	glUniform1f(z_offsetID, 0.00f);

	// Set pointers for each parameter (with appropriate starting positions)
	// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glVertexAttribPointer.xml
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, 0, (VOID*)(3 * VERTICES * sizeof(GLfloat)));
	glVertexAttribPointer(uvID, 2, GL_FLOAT, GL_FALSE, 0, (VOID*)(((3 * VERTICES) + (4 * COLORS)) * sizeof(GLfloat)));

	// Enable Arrays
	glEnableVertexAttribArray(positionID);
	//glEnableVertexAttribArray(colorID);
	glEnableVertexAttribArray(uvID);

	// Draw Element Arrays
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	mvpID[PROJ] = glGetUniformLocation(progID, "sv_mvp");
	if (mvpID[PROJ] < 0) { DEBUG_MSG("mvpID not found"); }


	glBufferSubData(GL_ARRAY_BUFFER, 0 * VERTICES * sizeof(GLfloat), 3 * VERTICES * sizeof(GLfloat), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, 3 * VERTICES * sizeof(GLfloat), 4 * COLORS * sizeof(GLfloat), colors);
	glBufferSubData(GL_ARRAY_BUFFER, ((3 * VERTICES) + (4 * COLORS)) * sizeof(GLfloat), 2 * UVS * sizeof(GLfloat), uvs);
	glUniformMatrix4fv(mvpID[PROJ], 1, GL_FALSE, &mvp[PROJ][0][0]);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

	mvpID[GOAL] = glGetUniformLocation(progID, "sv_mvp");

	if (mvpID[GOAL] < 0) { DEBUG_MSG("mvpID not found"); }


	glBufferSubData(GL_ARRAY_BUFFER, 0 * VERTICES * sizeof(GLfloat), 3 * VERTICES * sizeof(GLfloat), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, 3 * VERTICES * sizeof(GLfloat), 4 * COLORS * sizeof(GLfloat), colors);
	glBufferSubData(GL_ARRAY_BUFFER, ((3 * VERTICES) + (4 * COLORS)) * sizeof(GLfloat), 2 * UVS * sizeof(GLfloat), uvs);
	glUniformMatrix4fv(mvpID[GOAL], 1, GL_FALSE, &mvp[GOAL][0][0]);
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);

}

void Game::initCubes()
{
	loadIdentities();
	
	m_playerModel.init(0, 0, 2);
	m_bulletCube.init();
	changeGoal();

	m_score = 0;
	m_lives = 5;
}

void Game::setShader()
{
	GLint isCompiled = 0;
	GLint isLinked = 0;


	char *vs = NULL, *fs = NULL;

	vertShader = glCreateShader(GL_VERTEX_SHADER);
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	vs = textFileRead("cube.vert");//loads in the vertex shader code
	fs = textFileRead("cube.frag");//loads in the fragment shader code

	const char * vv = vs;
	const char * ff = fs;

	glShaderSource(vertShader, 1, &vv, NULL);
	glShaderSource(fragShader, 1, &ff, NULL);


	glCompileShader(vertShader);
	glCompileShader(fragShader);

	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Vertex Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Vertex Shader Compilation Error");
	}

	//Check is Shader Compiled
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Fragment Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Fragment Shader Compilation Error");
	}
	//DEBUG_MSG("Setting Up and Linking Shader");
	progID = glCreateProgram();	//Create program in GPU
	glAttachShader(progID, vertShader); //Attach Vertex Shader to Program
	glAttachShader(progID, fragShader); //Attach Fragment Shader to Program
	glLinkProgram(progID);
	//Check is Shader Linked
	glGetProgramiv(progID, GL_LINK_STATUS, &isLinked);
	if (isLinked == 1) {
		DEBUG_MSG("Shader Linked");
	}
	else
	{


		DEBUG_MSG("ERROR: Shader Link Error");
	}

	// Use Progam on GPU
	// https://www.opengl.org/sdk/docs/man/html/glUseProgram.xhtml
	glUseProgram(progID);

	// Find variables in the shader
	// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetAttribLocation.xml
	positionID = glGetAttribLocation(progID, "sv_position");
	//colorID = glGetAttribLocation(progID, "sv_color");
}

void Game::doInput(sf::Time t_deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		/// <summary>
		///creates new matrix that holds ytranslated player and later assigns it to player
		/// </summary>
		/// <param name="t_deltaTime"></param>
		glm::mat4 mat = glm::translate(m_playerModel.getModel(), glm::vec3(-0.005 * t_deltaTime.asMilliseconds(), 0, 0));
		m_playerModel.setCube(mat);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		glm::mat4 mat = glm::translate(m_playerModel.getModel(), glm::vec3(0.005 * t_deltaTime.asMilliseconds(), 0, 0));
		m_playerModel.setCube(mat);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !moving)
	{
		// shoooooooooooooooooooooooooooooot: gets position par tof the matrix and sets to cube so it spawns in 
		m_bulletCube.goToPlayer(m_playerModel.getModel());
		moving = true;
	}
}


