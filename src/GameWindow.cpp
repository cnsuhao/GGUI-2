#include "GameWindow.h"

GameWindow::GameWindow()
{

}

GameWindow::~GameWindow()
{
	SDL_Quit();
}

void GameWindow::Run()
{
    
    if (Load() == false)
	{
		return;
	}

    time_t curTime;

    //Init shader options
    ShaderOptions shaderoptions;
    shaderoptions.Opacity = 1.0;
    shaderoptions.Color = glm::vec3(1.0f);
    shaderoptions.FontRendering = false;
    Globals::shaderOptions = &shaderoptions;

	while (Globals::curGamestate != EXIT)
	{
		//Frame start time
#if _WIN32
		unsigned int frameStartTime = clock();
#endif // _WIN32

		ProcessInput();
		Update();

		//Draw each frame -- FOR DEBUGGING
		//Globals::refreshScreen = true;
		if (Globals::refreshScreen == true)
		{
			Render(Globals::shaderOptions);
			Globals::refreshScreen = false;
			//FPS counter
			fpscounter++;
		}
		

        curTime = time(0);

		if (curTime != fpslastSec)
		{
            //Globals::refreshScreen = true;
            if(fpscounter != 0) {deltams = glm::clamp((1000 / fpscounter) - (1000 / Globals::FPSLimit),0,1000);}else{deltams=0;}
			cout << "FPS: " << fpscounter << endl;
			fpscounter = 0;
			fpslastSec = curTime;
			cout << "DeltaTime: " << Globals::deltaTime << endl;
			//cout << "Time: " << clock() << endl;
		}

#if _WIN32
		// Calculate frame delta time in milliseconds
		unsigned int frameDeltaTime = clock() - frameStartTime;

		// Adjust FPS to hit target FPS
		unsigned int fpsTargetMS = 1000 / Globals::FPSLimit;
		if (frameDeltaTime < fpsTargetMS)
		{
			SDL_Delay(fpsTargetMS - frameDeltaTime);
		}
#endif // _WIN32

	}
	Unload();
}

bool GameWindow::Load()
{

	SDL_Init(SDL_INIT_EVERYTHING);
	// Settings
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,	8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,	8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,	8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,	8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,	32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,	24);
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, Globals::AASamples);

	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
//#if __unix__
//#endif // __unix__
    
    /*
    cout << Globals::AASamples << endl;
	Globals::AASamples = 1;
	Globals::AASamples = 4;
	Globals::AASamples = 9;
	Globals::AASamples = 2;
	Globals::AASamples = 10;
    cout << Globals::AASamples << endl;
*/

	Globals::gameWindow = SDL_CreateWindow(
		Globals::windowTitle,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		Globals::windowWidth,
		Globals::windowHeight,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
		);


	if (Globals::Fullscreen)
	{
		SDL_SetWindowFullscreen(Globals::gameWindow, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
	}

	//Window
	if (Globals::gameWindow == NULL)
	{
		cout << "FAILED to create an SDL2 window! " << endl << SDL_GetError() << endl;
		return false;
	}

	//Context
	glContext = SDL_GL_CreateContext(Globals::gameWindow);
	if (glContext == NULL)
	{
		cout << "FAILED to create an SDL_GL context" << endl << SDL_GetError()  << endl;
		return false;
	}

	//GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		cout << "FAILED to initialize GLEW!" << endl;
		return false;
	}

	//CREATING THE RENDER TARGET
	passManager = PassManager();
	if (passManager.Load() == false)
	{
        cout << "FAILED to initialize PASS MANAGER!" << endl;
		return false;
	}

	//Clear color
	glClearColor(0.9, 0.9, 0.9, 1);

	//Depth testing
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);


	//Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_ONE, GL_ONE);
//	glBlendFunc(GL_ONE_MINUS_DST_ALPHA, GL_DST_ALPHA);

	//Anti aliasing
	glEnable(GL_MULTISAMPLE);

	//glPointSize(2.0f);

	Mesh::LoadGlobally();

    //SDL_StartTextInput();

	//Load MainGame
	mainGame.Load();

	return true;
}

void GameWindow::ProcessInput()
{
	SDL_Event event;

	/* Poll for events. SDL_PollEvent() returns 0 when there are no  */
	/* more events on the event queue, our while loop will exit when */
	/* that occurs.                                                  */
	while (SDL_PollEvent(&event)) {
		/* We are only worried about SDL_KEYDOWN and SDL_KEYUP events */
		switch (event.type) {
        case SDL_TEXTINPUT:
            mainGame.KeyDown(*event.text.text);
            break;
		case SDL_KEYDOWN:
			//printf("Key press detected\n");
			Globals::refreshScreen = true;
			switch (event.key.keysym.sym)
			{
			case SDLK_KP_PLUS:		passManager.CAPass_Amount += 1.0f; break;
			case SDLK_KP_MINUS:		passManager.CAPass_Amount -= 1.0f; break;
			case SDLK_t:			passManager.PCAPass_Amount = 3.0f; break;
			case SDLK_b:
				passManager.BlurPass_Amount == 1.0f ? passManager.BlurPass_Amount = 0.0f : passManager.BlurPass_Amount = 1.0f;
				break;
			}
            //mainGame.KeyDown(*event.text.text);
			break;

		case SDL_KEYUP:
			//printf("Key release detected\n");
			Globals::refreshScreen = true;
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:	Globals::curGamestate = EXIT; break;
			case SDLK_t:			passManager.PCAPass_Amount = 0.0f; break;
			case SDLK_F11:
				Globals::Fullscreen ?
					SDL_SetWindowFullscreen(Globals::gameWindow, SDL_WINDOW_OPENGL) :
					SDL_SetWindowFullscreen(Globals::gameWindow, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP) ;
				Globals::Fullscreen = !Globals::Fullscreen;
				break;

			}
			break;

		case SDL_QUIT:
			Globals::curGamestate = EXIT;
			//hasQuit = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			Globals::refreshScreen = true;
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				Globals::curMouseState = ATTRACTING;
			}
			else if(event.button.button == SDL_BUTTON_RIGHT)
			{
				Globals::curMouseState = REPELLING;
			}
			break;
		case SDL_MOUSEMOTION:
			Globals::mousePos.x = event.motion.x;
			Globals::mousePos.y = event.motion.y;
			//cout << Globals::mousePos.x << ", " << Globals::mousePos.y << endl;
			break;
		case SDL_MOUSEBUTTONUP:
			Globals::refreshScreen = true;

			if (event.button.button == SDL_BUTTON_LEFT)
			{
				if (Globals::curMouseState == ATTRACTING)
				{
					Globals::curMouseState = IDLE;
				}
			}
			else if (event.button.button == SDL_BUTTON_RIGHT)
			{
				if (Globals::curMouseState == REPELLING)
				{
					Globals::curMouseState = IDLE;
				}
			}
			break;
		case SDL_WINDOWEVENT:
			switch (event.window.event) {
			case SDL_WINDOWEVENT_RESIZED:
				SceneCamera.updateProjection(event.window.data1, event.window.data2);
				break;
			case SDL_WINDOWEVENT_SIZE_CHANGED:
				Globals::windowWidth = event.window.data1;
				Globals::windowHeight = event.window.data2;
				SceneCamera.updateProjection(event.window.data1, event.window.data2);
				break;
			case SDL_WINDOWEVENT_MINIMIZED:
				SDL_Log("Window %d minimized", event.window.windowID);
				break;
			case SDL_WINDOWEVENT_MAXIMIZED:
				SDL_Log("Window %d maximized", event.window.windowID);
				break;

			}
			Globals::refreshScreen = true;
			break;
		}
	}
}

void GameWindow::Update()
{

#if __unix__
	struct timeval tp;
    gettimeofday(&tp, NULL);
    long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;

	Globals::deltaTime = (ms - lastTime)/1000.0;
	lastTime = ms;
#endif // __unix__

    if(Globals::curMouseState == ATTRACTING || Globals::curMouseState == REPELLING)
    {
        Globals::refreshScreen = true;
    }

	//Update MainGame
	mainGame.Update(&Globals::mousePos);
}

void GameWindow::Render(ShaderOptions* shader)
{
	glViewport(0, 0, Globals::windowWidth, Globals::windowHeight); // Render on the whole framebuffer, complete from the lower left corner to the upper right
	//glViewport(0, 0,  width, height); // Render on the whole framebuffer, complete from the lower left corner to the upper right


	//Globals::CAPass::Amount = (glm::sin(clock() / 500.0f) + 1.0f)*10.0f;

	//enables
	//glEnable(GL_DEPTH_TEST);

	//passManager.Bind();

	//Clear screen
	glClear(GL_COLOR_BUFFER_BIT);

	//Render MainGame
	//glBindTexture(GL_TEXTURE_2D, 0);
	mainGame.Render(&SceneCamera, shader);


	//Depth testing
	//glDisable(GL_DEPTH_TEST);


	//PASS RENDERS
	//passManager.Render();
	//passManager.LastPass(Globals::windowWidth, Globals::windowHeight);


	//Swap Buffer
	SDL_GL_SwapWindow(Globals::gameWindow);
    /*
    GLenum err = glGetError();
    while (err != GL_NO_ERROR) {
        std::cout << "OpenGL Error: " << err << std::endl;
    }*/
    
}

void GameWindow::Unload()
{
	mainGame.Unload();

	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(Globals::gameWindow);
}
