#ifndef PANE_H
#define PANE_H
#include "Rectangle.h"
#include "Shadow.h"

class Pane : public Drawable
{
public:
	Pane(string filename);
	Pane();
	~Pane();

	void Load();
	void Update();
	void Draw(Camera* camera, ShaderOptions* shader);

private:
	Rectangle	_rect;
	Shadow		_shadow;

	string		_filename;

};

#endif
