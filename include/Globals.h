#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL2/SDL.h>
//#include <string>
#include <glm/glm.hpp>
//#include <vector>
//#include "Input.h"
#include <GL/glew.h>

using namespace std;

enum GameState	{PLAY, EXIT};
enum MouseState	{ATTRACTING, IDLE, REPELLING};

struct ShaderOptions
{
    // Upload checking
    //bool BasicChanged;

    // Basic options
    float Opacity;
    glm::vec3 Color;

    //Font rendering
    bool FontInfoChanged;
    bool CharacterInfoChanged;
    bool FontRendering;

    //Font info
    float TextureWidth;
    float TextureHeight;

    //Character info
    float FontX;
    float FontY;
    float FontWidth;
    float FontHeight;

};


namespace Globals
{
	//Window
	static SDL_Window*		gameWindow;
	//static Input			input;

	//Window Startup settings
	static const char *		windowTitle		= "OpenGL - Pong - 1.0";
	static int				windowWidth		= 1280;
	static int				windowHeight	= 720;
	static bool				Fullscreen		= false;
	static int				FPSLimit		= 60;
	static int				AASamples   	= 0;



	//Game
	static GameState		curGamestate	= PLAY;
	static MouseState		curMouseState	= IDLE;
	static glm::vec2		mousePos		= glm::vec2(0.0f, 0.0f);
	//static int				mouseX			= 0;
	//static int				mouseY			= 0;
	static double			deltaTime		= 0.0;
	//static const int		MAXparticles	= 10000;
	//static vector<Particle> particles;

	// Update screen
	static bool				refreshScreen	= true;


	//Shader properties to pass along - DO NOT TOUCH!
	//static float			nextOpacity		= 1.0f;
    //static glm::vec3        nextColor       = glm::vec3(1.0f);
    static ShaderOptions*   shaderOptions;

}

#endif
