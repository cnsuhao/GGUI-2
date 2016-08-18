#include "Shadow.h"


Shadow::Shadow()
{

}


Shadow::~Shadow()
{
}


void Shadow::Load() {
	sC = Rectangle("ShadowComponents/ShadowC");
	sL = Rectangle("ShadowComponents/ShadowL");
	sR = Rectangle("ShadowComponents/ShadowR");
	sT = Rectangle("ShadowComponents/ShadowT");
	sB = Rectangle("ShadowComponents/ShadowB");
	sTL = Rectangle("ShadowComponents/ShadowTL");
	sTR = Rectangle("ShadowComponents/ShadowTR");
	sBL = Rectangle("ShadowComponents/ShadowBL");
	sBR = Rectangle("ShadowComponents/ShadowBR");

	sC.Load();
	sL.Load();
	sR.Load();
	sT.Load();
	sB.Load();
	sTL.Load();
	sTR.Load();
	sBL.Load();
	sBR.Load();

}

void Shadow::Draw(Camera* camera, ShaderOptions* shader) {
	sC .Draw(camera, shader);
	sL .Draw(camera, shader);
	sR .Draw(camera, shader);
	sT .Draw(camera, shader);
	sB .Draw(camera, shader);
	sTL.Draw(camera, shader);
	sTR.Draw(camera, shader);
	sBL.Draw(camera, shader);
	sBR.Draw(camera, shader);
}

void Shadow::Update() {

	bool shadowUpdated = false;

	if (_sizeChanged) {
		UpdateShadow();
		shadowUpdated = true;
		_sizeChanged = false;
	}

	if (_positionChanged) {
		if (shadowUpdated == false)
			UpdateShadow();
		_positionChanged = false;
	}


	if (_distanceChanged)
	{
		_distanceChanged = false;
	}

	sC.Update();
	sL.Update();
	sR.Update();
	sT.Update();
	sB.Update();
	sTL.Update();
	sTR.Update();
	sBL.Update();
	sBR.Update();


}

void Shadow::UpdateShadow() {
	//Define variables
	float bluramount = 75.0f * _distance;
	float offset = 5.0f * _distance;
	float opacity = 0.2f / (float)pow(_distance, 2.0);

	if (_size.x >= 0.0f && _size.y >= 0.0f) {

		// Center
		sC.setSize(_size);
		sC.setPosition(_position.x + offset , _position.y + offset );

		// Top left
		sTL.setSize(bluramount);
		sTL.setPosition(_position.x + offset - bluramount, _position.y + offset - bluramount);

		// Top right
		sTR.setSize(bluramount);
		sTR.setPosition(_position.x + offset + _size.x, _position.y + offset - bluramount);

		// Top
		sT.setSize(_size.x , bluramount);
		sT.setPosition(_position.x + offset , _position.y + offset - bluramount);

		// Bottom Left
		sBL.setSize(bluramount);
		sBL.setPosition(_position.x + offset - bluramount, _position.y + _size.y + offset);

		// Bottom Right
		sBR.setSize(bluramount);
		sBR.setPosition(_position.x + _size.x + offset , _position.y + _size.y + offset );

		// Bottom
		sB.setSize(_size.x, bluramount);
		sB.setPosition(_position.x + offset , _position.y + _size.y + offset);

		// Left
		sL.setSize(bluramount, _size.y);
		sL.setPosition(_position.x + offset - bluramount, _position.y + offset );

		// Right
		sR.setSize(bluramount, _size.y);
		sR.setPosition(_position.x + _size.x + offset, _position.y + offset );
	}
	else if (_size.x >= 0.0f && _size.y <= 0.0f)
	{
		float avgY = ((_size.y + _position.y) + (_position.y)) / 2.0f + offset;

		// Center
		sC.setSize(0.0f);
		//sC.setPosition(_position.x + offset, _position.y + offset);

		// Top left
		sTL.setSize(bluramount);
		sTL.setPosition(_position.x + offset - bluramount, avgY - bluramount);

		// Top right
		sTR.setSize(bluramount);
		sTR.setPosition(_position.x + offset + _size.x, avgY - bluramount);

		// Top
		sT.setSize(_size.x, bluramount);
		sT.setPosition(_position.x + offset, avgY-bluramount);

		// Bottom Left
		sBL.setSize(bluramount);
		sBL.setPosition(_position.x + offset - bluramount, avgY);

		// Bottom Right
		sBR.setSize(bluramount);
		sBR.setPosition(_position.x + _size.x + offset, avgY);

		// Bottom
		sB.setSize(_size.x, bluramount);
		sB.setPosition(_position.x + offset, avgY);

		// Left
		sL.setSize(0.0f);
		//sL.setPosition(_position.x + offset - bluramount, _position.y + offset);

		// Right
		sR.setSize(0.0f);
		//sR.setPosition(_position.x + _size.x + offset, _position.y + offset);

		opacity -= abs(_size.y)/500.0f;

	}
	else if (_size.x <= 0.0f && _size.y >= 0.0f)
	{
		float avgX = ((_size.x + _position.x) + (_position.x)) / 2.0f + offset;

		// Center
		sC.setSize(0.0f);
		//sC.setPosition(_position.x + offset, _position.y + offset);

		// Top left
		sTL.setSize(bluramount);
		sTL.setPosition(avgX - bluramount, _position.y + offset - bluramount);

		// Top right
		sTR.setSize(bluramount);
		sTR.setPosition(avgX, _position.y + offset - bluramount);

		// Top
		sT.setSize(0.0f);
		//sT.setPosition(_position.x + offset, _position.y + offset - bluramount);

		// Bottom Left
		sBL.setSize(bluramount);
		sBL.setPosition(avgX - bluramount, _position.y + _size.y + offset);

		// Bottom Right
		sBR.setSize(bluramount);
		sBR.setPosition(avgX, _position.y + _size.y + offset);

		// Bottom
		sB.setSize(0.0f);
		//sB.setPosition(_position.x + offset, _position.y + _size.y + offset);

		// Left
		sL.setSize(bluramount, _size.y);
		sL.setPosition(avgX - bluramount, _position.y + offset);

		// Right
		sR.setSize(bluramount, _size.y);
		sR.setPosition(avgX, _position.y + offset);

		opacity -= abs(_size.x) / 500.0f;


	}
	else if (_size.x <= 0.0f && _size.y <= 0.0f)
	{
		float avgX = ((_size.x + _position.x) + (_position.x)) / 2.0f + offset;
		float avgY = ((_size.y + _position.y) + (_position.y)) / 2.0f + offset;

		// Center
		sC.setSize(0.0f);
		//sC.setPosition(_position.x + offset, _position.y + offset);

		// Top left
		sTL.setSize(bluramount);
		sTL.setPosition(avgX - bluramount, avgY - bluramount);

		// Top right
		sTR.setSize(bluramount);
		sTR.setPosition(avgX, avgY - bluramount);

		// Top
		sT.setSize(0.0f);
		//sT.setPosition(_position.x + offset, _position.y + offset - bluramount);

		// Bottom Left
		sBL.setSize(bluramount);
		sBL.setPosition(avgX - bluramount, avgY);

		// Bottom Right
		sBR.setSize(bluramount);
		sBR.setPosition(avgX, avgY);

		// Bottom
		sB.setSize(0.0f);
		//sB.setPosition(_position.x + offset, _position.y + _size.y + offset);

		// Left
		sL.setSize(0.0f);
		//sL.setPosition(avgX - bluramount, _position.y + offset);

		// Right
		sR.setSize(0.0f);
		//sR.setPosition(avgX, _position.y + offset);

		if (abs(_size.x) > abs(_size.y))
		{
			opacity -= abs(_size.x) / 400.0f;
		}
		else{
			opacity -= abs(_size.y) / 400.0f;
		}



	}

	// Opacity
	sC.setOpacity (opacity);
	sL.setOpacity (opacity);
	sR.setOpacity (opacity);
	sT.setOpacity (opacity);
	sB.setOpacity (opacity);
	sTL.setOpacity(opacity);
	sTR.setOpacity(opacity);
	sBL.setOpacity(opacity);
	sBR.setOpacity(opacity);


	//this->setOpacity(0.01f);
	//this->_opacityChanged = true;
}


