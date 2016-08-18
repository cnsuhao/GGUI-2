#include "Mesh.h"

GLuint Mesh::_rectvertexArrayObject = 0;
GLuint Mesh::_rectvertexArrayBuffers[NUM_BUFFERS] = {0,0,0};
GLuint Mesh::_rectdrawCount = 0;


Mesh::Mesh()
{

}


Mesh::~Mesh()
{
	glDeleteBuffers(NUM_BUFFERS, vertexArrayBuffers);
	glDeleteVertexArrays(1, &vertexArrayObject);
}

void Mesh::Draw()
{
	glBindVertexArray(vertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, drawCount);
	glBindVertexArray(0);



}

void Mesh::Unload()
{

}

void Mesh::Load(Vertex vertices[], unsigned int numVertices)
{
	cout << "Loading Mesh..." << endl;
	drawCount = numVertices;

	//Unpacking Vertices 1 - List init
	vector<glm::vec3> positions = vector<glm::vec3>();
	vector<glm::vec2> texcoords = vector<glm::vec2>();
	vector<glm::vec3> normals =   vector<glm::vec3>();

	//Unpacking Vertices 2 - Extraction
	for (int i = 0; i < numVertices; i++)
	{
		positions.push_back	(vertices[i].position);
		texcoords.push_back	(vertices[i].texcoord);
		normals.push_back	(vertices[i].normal);
	}

	//Generating the buffers for the mesh
	//VAO
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * positions.size(), &positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,			//Layout ID
		3,			//pieces of data
		GL_FLOAT,	//Type
		GL_FALSE,	//normalized
		0,			//stride
		0);			//offset

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * texcoords.size(), &texcoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(), &normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);

}

void Mesh::LoadGlobally() {

	// INIT GLOBAL PLAIN
	Vertex vertices[6] = {
		Vertex(glm::vec3(0, 1.0, 0), glm::vec2(0, 1.0), glm::vec3(0, 0, 1.0)),
		Vertex(glm::vec3(1.0, 0, 0), glm::vec2(1.0, 0), glm::vec3(0, 0, 1.0)),
		Vertex(glm::vec3(0, 0, 0), glm::vec2(0, 0), glm::vec3(0, 0, 1.0)),

		Vertex(glm::vec3(1.0, 1.0, 0), glm::vec2(1.0, 1.0), glm::vec3(0, 0, 1.0)),
		Vertex(glm::vec3(1.0, 0, 0), glm::vec2(1.0, 0.0), glm::vec3(0, 0, 1.0)),
		Vertex(glm::vec3(0, 1.0, 0), glm::vec2(0, 1.0), glm::vec3(0, 0, 1.0))
	};

	unsigned int numVertices = 6;

	//vector<GLuint> tmpVec = vector<GLuint>();
	GLuint vertArrayBuffers[NUM_BUFFERS];
	GLuint vertArrayObject;

	//Vertex array object - 0
	//tmpVec.push_back(0);
	//
	////Draw count - 1
	//tmpVec.push_back(0);
	//
	////vertexArrayBuffers - 2-4
	//tmpVec.push_back(0);
	//tmpVec.push_back(0);
	//tmpVec.push_back(0);

	cout << "Loading Plane Mesh..." << endl;
	//tmpVec[1] = numVertices;

	//Unpacking Vertices 1 - List init
	vector<glm::vec3> positions = vector<glm::vec3>();
	vector<glm::vec2> texcoords = vector<glm::vec2>();
	vector<glm::vec3> normals   = vector<glm::vec3>();

	//Unpacking Vertices 2 - Extraction
	for (int i = 0; i < numVertices; i++)
	{
		positions.push_back(vertices[i].position);
		texcoords.push_back(vertices[i].texcoord);
		normals.push_back(vertices[i].normal);
	}

	//Generating the buffers for the mesh
	//VAO
	glGenVertexArrays(1, &vertArrayObject);
	glBindVertexArray(vertArrayObject);

	glGenBuffers(NUM_BUFFERS, vertArrayBuffers);

	glBindBuffer(GL_ARRAY_BUFFER, vertArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)* positions.size(), &positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,			//Layout ID
		3,			//pieces of data
		GL_FLOAT,	//Type
		GL_FALSE,	//normalized
		0,			//stride
		0);			//offset

	glBindBuffer(GL_ARRAY_BUFFER, vertArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)* texcoords.size(), &texcoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)* normals.size(), &normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);

	Mesh::_rectvertexArrayObject = vertArrayObject;
	Mesh::_rectdrawCount = numVertices;
	Mesh::_rectvertexArrayBuffers[POSITION_VB] = vertArrayBuffers[POSITION_VB];
	Mesh::_rectvertexArrayBuffers[TEXCOORD_VB] = vertArrayBuffers[TEXCOORD_VB];
	Mesh::_rectvertexArrayBuffers[NORMAL_VB] = vertArrayBuffers[NORMAL_VB];

	//tmpVec[0] = vertArrayObject;
	//tmpVec[POSITION_VB + 2] = vertArrayBuffers[POSITION_VB];
	//tmpVec[TEXCOORD_VB + 2] = vertArrayBuffers[TEXCOORD_VB];
	//tmpVec[NORMAL_VB + 2]	= vertArrayBuffers[NORMAL_VB];

	//return tmpVec;


}

void Mesh::LoadPlane() {
	vertexArrayObject = Mesh::_rectvertexArrayObject;
	drawCount = Mesh::_rectdrawCount;
	vertexArrayBuffers[POSITION_VB] = Mesh::_rectvertexArrayBuffers[POSITION_VB];
	vertexArrayBuffers[TEXCOORD_VB] = Mesh::_rectvertexArrayBuffers[TEXCOORD_VB];
	vertexArrayBuffers[NORMAL_VB] = Mesh::_rectvertexArrayBuffers[NORMAL_VB];
}


/*
void Mesh::PreLoaded(GLuint vertObject, GLuint DrawCount, GLuint vertbuffers[3]) {
	vertexArrayObject		= vertObject;
	drawCount				= DrawCount;
	vertexArrayBuffers[0]	= vertbuffers[0];
	vertexArrayBuffers[1]	= vertbuffers[1];
	vertexArrayBuffers[2]	= vertbuffers[2];
}*/


