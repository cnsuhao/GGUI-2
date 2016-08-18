#ifndef MAIN_GAME_H
#define MAIN_GAME_H
#include <iostream>
#include <map>
#include <ctime>
#include "Globals.h"
#include "Mesh.h"
#include "GGUIShader.h"
#include "Texture.h"

using namespace std;

class MainGame
{
public:
	MainGame();
	~MainGame();

	void Load();
	void Update(glm::vec2 *mousex);
	void Render(Camera* camera, ShaderOptions* shader);
	void Unload();

    void KeyDown(char Key);
};

#endif
