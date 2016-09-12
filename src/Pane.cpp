#include "Pane.h"


Pane::Pane()
{
}

Pane::Pane(string filename) {
	_filename = filename;
}

Pane::~Pane()
{
}


void Pane::Load() {
	//Create them
	if (_filename != "")
	{
		_rect = Rectangle(_filename);
	}
	else{
		_rect = Rectangle();
	}

	_shadow = Shadow();

	//Load them
	_rect.Load();
	_shadow.Load();

	//Init parameters
	_rect.setPosition(_position);
	_rect.setSize(_size);

	float inset = 50.0f;
	_shadow.setPosition(_rect.getPosition() + glm::vec2(inset));
	_shadow.setSize(_rect.getSize() - glm::vec2(2.0f * inset));


}

void Pane::Update() {

	const float inset = 50.0f;

	if (_sizeChanged) {
		_rect.setSize(_size);
		_shadow.setSize(_rect.getSize() - glm::vec2(2.0f * inset));
		_sizeChanged = false;
	}

	if (_positionChanged) {
		_rect.setPosition(_position);
		_shadow.setPosition(_rect.getPosition() + glm::vec2(inset));
		_positionChanged = false;
	}
    
    if (_distanceChanged) {
        _shadow.setDistance(_distance);
        _rect.setDistance(_distance);
    }

	_rect.Update();
	_shadow.Update();

}

void Pane::Draw(Camera* camera, ShaderOptions* shader) {

	_shadow.Draw(camera, shader);
	_rect.Draw(camera, shader);
}

