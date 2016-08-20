#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
//#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>


#ifdef _WIN32
	#include <ctime>
#elif __APPLE__
    #include <sys/time.h>
#endif

//#include <thread>
#include <iostream>
#include <vector>
#include <map>

#include "Globals.h"
#include "MainGame.h"

#include "PassManager.h"
#include "Mesh.h"
#include "Texture.h"
#include "BlurPass.h"

class GameWindow
{
public:
	GameWindow();
	~GameWindow();

	/*
	Description:
	UPS: Updates per second
	FPS: Frames per second
	0 = ∞
	*/
	void Run();

private:
	bool Load();
	void Update();
	void Render(ShaderOptions* shader);
	void Unload();
	void ProcessInput();

	//Variables
	MainGame	mainGame = MainGame();
	int			fpscounter = 0, fpslastSec = 0, deltams = 0;

#if _WIN32
    double		lastTime = 0.0;
#endif
    
	SDL_GLContext glContext;

	PassManager passManager;

	Camera SceneCamera = Camera(
		glm::vec3(0.0f, 0.0f, -5.0f),
		70.0f,
		(float)Globals::windowWidth / (float)Globals::windowHeight,
		1.5f,
		100.0f
		);



};

#endif
