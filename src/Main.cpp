#include <iostream>
#include <string>
#include "GameWindow.h"
#include "Globals.h"
//#include <GL/glew.h>

int main(int argc, char** argv)
{
    for (int i = 0; i < argc; i++) {
        cout << "Arg " << i << ": " << argv[i] << endl;
    }
    
    
	std::cout << "Creating application object" << std::endl;
	GameWindow _window = GameWindow();

	//Globals::gameWindowObject.Run(60.0, 60.0);
	_window.Run();

	//Wait for keypress
	//std::cout << "Press ENTER to continue" << std::endl;
	//std::string str = "";
	//std::getline(std::cin, str);
	return 0;
}
