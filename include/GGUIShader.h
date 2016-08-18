#ifndef DERPSHADER_H
#define DERPSHADER_H
#include <GL/glew.h>
#include <vector>
#include <map>
#include "Shader.h"
#include "Transform.h"
#include "Camera.h"

class GGUIShader
{
public:
	GGUIShader() {};
	~GGUIShader(){}

	void Load(){
		shader = Shader();

		std::vector<const GLchar*> uniformNames;

		uniformNames.push_back("MVP");
		uniformNames.push_back("Opacity");
		uniformNames.push_back("FillColor");
		uniformNames.push_back("FontRendering");
		uniformNames.push_back("TextureWidth");
		uniformNames.push_back("TextureHeight");
		uniformNames.push_back("FontX");
		uniformNames.push_back("FontY");
		uniformNames.push_back("FontWidth");
		uniformNames.push_back("FontHeight");


		uniforms = shader.Load("GGUIShader", uniformNames);

	};

	void Bind(Transform transform, const Camera* camera, ShaderOptions* shader){
		this->shader.Bind();

		//Position (MVP)
		glm::mat4 MVP = transform.GetMVP(*camera);
		glm::mat4 Normal = transform.GetModel();
		glUniformMatrix4fv(uniforms["MVP"], 1, GL_FALSE, &MVP[0][0]);

		glUniform1f(uniforms["Opacity"], shader->Opacity);
        //Color
        glUniform3f(uniforms["FillColor"], shader->Color.x,
        shader->Color.y, shader->Color.z);


		if (shader->FontInfoChanged)
		{
		    glUniform1f(uniforms["TextureWidth"], shader->TextureWidth);
            glUniform1f(uniforms["TextureHeight"], shader->TextureHeight);
            shader->FontInfoChanged = false;
		}

		if (shader->CharacterInfoChanged)
		{
            glUniform1f(uniforms["FontX"], shader->FontX);
            glUniform1f(uniforms["FontY"], shader->FontY);
            glUniform1f(uniforms["FontWidth"], shader->FontWidth);
            glUniform1f(uniforms["FontHeight"], shader->FontHeight);
		}

		glUniform1i(uniforms["FontRendering"], shader->FontRendering);
		//glUniform1ui(uniforms["time"], (unsigned int)Globals::time);

	};


    GLuint getShaderProgram()
    {
        return shader.m_program;
    }

    std::map<const GLchar*, GLuint> GetUniformLocations()
    {
        return uniforms;
    }


private:
	Shader shader;
	std::map<const GLchar*, GLuint> uniforms;

};

#endif
