#include "MainGame.h"

#include <sstream>

#include "Pane.h"
#include "GUIText.h"

Pane    pane    = Pane();
GUIText txt     = GUIText();

MainGame::MainGame()
{
}
MainGame::~MainGame()
{
}

void MainGame::Load()
{
	cout << "Application loaded..." << endl;

	pane.Load();
	txt.Load();
	txt.SetFontSize(52.0f);

}

void MainGame::Update(glm::vec2* mousePos)
{
	pane.setPosition((*mousePos).x - pane.getSize().x / 2.0f, (*mousePos).y - pane.getSize().y / 2.0f);
    txt.setPosition(pane.getPosition() + 9.0f);

	pane.Update();
	txt.Update();
}

void MainGame::Render(Camera* camera, ShaderOptions* shader)
{
	pane.Draw(camera, shader);
	txt.Draw(camera, shader);

}

void MainGame::Unload()
{
}

void MainGame::KeyDown(char Key)
{
    stringstream ss;
    ss << txt.GetText() << Key;
    txt.SetText(ss.str());

}

