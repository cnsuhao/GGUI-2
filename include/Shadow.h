#ifndef SHADOW_H
#define SHADOW_H
#include "Drawable.h"
#include "Rectangle.h"

class Shadow : public Drawable {
public:
	Shadow();
	~Shadow();

	void Load();
	void Draw(Camera* camera, ShaderOptions* shader);
	void Update();

 private:
	 // Update positions and sizes
	 void UpdateShadow();
	 // Center
	 Rectangle sC;
	 // Left and right
	 Rectangle sL;
	 Rectangle sR;
	 // Top and bottom
	 Rectangle sT;
	 Rectangle sB;
	 // Top - Left and right
	 Rectangle sTL;
	 Rectangle sTR;
	 // Bottom - Left and right
	 Rectangle sBL;
	 Rectangle sBR;


};

#endif
