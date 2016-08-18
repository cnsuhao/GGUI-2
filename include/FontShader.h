#ifndef FONTSHADER_H_INCLUDED
#define FONTSHADER_H_INCLUDED
#include <GL/glew.h>
#include <vector>
#include <map>

#include "Globals.h"
#include "Shader.h"
#include "Transform.h"
#include "Camera.h"


class FontShader
{
public:
	FontShader() {};
	~FontShader(){}

	void Load(){
		shader = Shader();

		std::vector<const GLchar*> uniformNames;

		uniformNames.push_back("MVP");
		uniformNames.push_back("Opacity");
		//uniformNames.push_back("time");

		uniforms = shader.Load("FontShader", uniformNames);

	};

	void Bind(Transform transform, const Camera* camera){
		shader.Bind();

		glm::mat4 MVP = transform.GetMVP(*camera);
		glm::mat4 Normal = transform.GetModel();

		glUniformMatrix4fv(uniforms["MVP"], 1, GL_FALSE, &MVP[0][0]);
		glUniform1f(uniforms["Opacity"], 1.0f);

		//glUniform1ui(uniforms["time"], (unsigned int)Globals::time);
	};


private:
	Shader shader;
	std::map<const GLchar*, GLuint> uniforms;

};





#endif // FONTSHADER_H_INCLUDED
