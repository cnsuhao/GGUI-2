// Copyright Candfa 2016
#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Mesh.h"
#include "Transform.h"
#include "Camera.h"
#include "GGUIShader.h"
#include "Texture.h"
#include "Drawable.h"

enum DrawMode {NORMAL, TEXTURELESS, SHADERLESS, EXTENDED};

class Rectangle : public Drawable{
 public:
	 Rectangle(string filename);
	 Rectangle();
	 ~Rectangle();

	 void Load();
	 void Draw(Camera* camera, ShaderOptions* shader);
	 void Update();
	 void BindShader(Camera* camera, ShaderOptions* shader);
     void BindTexture();

	 GGUIShader* getShaderPointer()
	 {return &rectShader;}

	 bool isShaderless = false;
	 bool isTextureless = false;
	 int RectangleDrawMode = NORMAL;

	 string SpecialPath = "";

	 GGUIShader rectShader = GGUIShader();

 private:
	 string _filename;
	 Mesh rectMesh = Mesh();
	 Texture rectTexture = Texture();
	 Transform rectTransform = Transform(
		 glm::vec3(0.0),
		 glm::vec3(0.0),
		 glm::vec3(2.0*100.0)
		 );


};

#endif
