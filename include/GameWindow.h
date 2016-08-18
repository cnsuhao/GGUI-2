#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
//#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

#if __unix__
	#include <sys/time.h>
#endif // __unix__
#if _WIN32
	#include <ctime>
#endif // _WIN32

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
	double		lastTime = 0.0;

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
