#include "Rectangle.h"
#include "Globals.h"

/*
Vertex rectVertices[6] = {
	Vertex(vec3(0, 1.0, 0), vec2(0, 1.0), vec3(0, 0, 1.0)),
	Vertex(vec3(1.0, 0, 0), vec2(1.0, 0), vec3(0, 0, 1.0)),
	Vertex(vec3(0, 0, 0), vec2(0, 0), vec3(0, 0, 1.0)),

	Vertex(vec3(1.0, 1.0, 0), vec2(1.0, 1.0), vec3(0, 0, 1.0)),
	Vertex(vec3(1.0, 0, 0), vec2(1.0, 0.0), vec3(0, 0, 1.0)),
	Vertex(vec3(0, 1.0, 0), vec2(0, 1.0), vec3(0, 0, 1.0))
};*/


Rectangle::Rectangle(string filename) {
	_filename = filename;

}

Rectangle::Rectangle() {
	_filename = "blank";

}

Rectangle::~Rectangle() {
	rectMesh.Unload();
}

void Rectangle::Load() {
	//rectMesh.Load(rectVertices, 6);

	//rectMesh.PreLoaded(Globals::rectvertexArrayObject, Globals::rectdrawCount, Globals::rectvertexArrayBuffers);
	rectMesh.LoadPlane();

	if (SpecialPath == "")
	{
        rectTexture.Load(_filename);

	}else{
        rectTexture.Load(SpecialPath, true);
	}


	rectShader.Load();

}

void Rectangle::BindShader(Camera* camera, ShaderOptions* shader)
{

    shader->Opacity = _opacity;
    rectShader.Bind(rectTransform, camera, shader);

}

void Rectangle::BindTexture()
{
    rectTexture.Bind(0);
}

void Rectangle::Draw(Camera* camera, ShaderOptions* shader) {
	if (RectangleDrawMode != TEXTURELESS && RectangleDrawMode != EXTENDED)
	    rectTexture.Bind(0);

    if (RectangleDrawMode != SHADERLESS && RectangleDrawMode != EXTENDED)
    {
             shader->Opacity = _opacity;
             rectShader.Bind(rectTransform, camera, shader);

    }
	rectMesh.Draw();

}

void Rectangle::Update() {
	if (_positionChanged) {
		rectTransform.pos = glm::vec3(_position.x, _position.y, 0.0f);
		_positionChanged = false;
	}

	if (_sizeChanged) {
		rectTransform.scale = glm::vec3(_size.x, _size.y, 1.0f);
		_sizeChanged = false;
	}

	//glUniform1f(rectShader.getOpacityLocation(), _opacity);


}

