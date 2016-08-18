#ifndef MESH_H
#define MESH_H
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <algorithm>

//using namespace glm;
using namespace std;

struct Vertex
{
	glm::vec3 position;
	glm::vec2 texcoord;
	glm::vec3 normal;

	Vertex(glm::vec3 position, glm::vec2 texcoord, glm::vec3 normal)
	{
		this->position	= position;
		this->texcoord	= texcoord;
		this->normal	= normal;
	}

};

enum MeshBufferPositions
{
	POSITION_VB,
	TEXCOORD_VB,
	NORMAL_VB,

	NUM_BUFFERS
};

class Mesh
{
public:
	Mesh();
	~Mesh();

	static void LoadGlobally();
	void Load(Vertex vertices[], unsigned int numVertices);
	//void PreLoaded(GLuint vertObject, GLuint drawCount, GLuint vertbuffers[3]);
	void LoadPlane();

	void Draw();
	void Unload();

private:
	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[NUM_BUFFERS];
	GLuint drawCount;

	// rect mesh
	static GLuint _rectvertexArrayObject;
	static GLuint _rectvertexArrayBuffers[NUM_BUFFERS];
	static GLuint _rectdrawCount;


};

#endif
