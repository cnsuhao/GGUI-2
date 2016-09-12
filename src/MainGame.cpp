#include "MainGame.h"

#include <sstream>

#include "Pane.h"
#include "GUIText.h"

Pane        pane     = Pane();
GUIText     txt      = GUIText();
Rectangle   progress = Rectangle();

MainGame::MainGame()
{
}
MainGame::~MainGame()
{
}

void MainGame::Load()
{
	cout << "Application loaded..." << endl;
    
    progress.Load();
	pane.Load();
	txt.Load();
    pane.setSize(500, 200);
    pane.setPosition(Globals::windowWidth/2.0f - pane.getSize().x/2.0f, Globals::windowHeight/2.0f - pane.getSize().y/2.0f-200.0f);
    pane.setDistance(10);
    progress.setSize(400, 40);
    progress.setDistance(10);
    progress.setPosition(Globals::windowWidth/2.0f - pane.getSize().x/2.0f, Globals::windowHeight/2.0f - progress.getSize().y/2.0f-150.0f);
	txt.SetFontSize(52.0f);
    txt.setPosition(pane.getPosition() + 30.0f);
    txt.setPositionX(txt.getPosition().x + 100.0f);
    txt.SetText("Compressing...");
    
}

void MainGame::Update(glm::vec2* mousePos)
{
	//pane.setPosition((*mousePos).x - pane.getSize().x / 2.0f, (*mousePos).y - pane.getSize().y / 2.0f);
    //txt.setPosition(pane.getPosition() + 9.0f);

    pane.Update();
    txt.Update();
    progress.Update();
}

void MainGame::Render(Camera* camera, ShaderOptions* shader)
{
    pane.Draw(camera, shader);
	txt.Draw(camera, shader);
    shader->Color = glm::vec3(0,1,0);
    progress.Draw(camera, shader);
    shader->Color = glm::vec3(1);

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

