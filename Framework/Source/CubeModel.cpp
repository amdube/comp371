//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
// Updated by Gary Chang on 14/1/15
//
// Modified by: Francois Stelluti
//
// Copyright (c) 2014-2015 Concordia University. All rights reserved.
//

#include "CubeModel.h"
#include "Renderer.h"
#include "Camera.h"
#include "World.h"

// Include GLEW - OpenGL Extension Wrangler
#include <GL/glew.h>

using namespace glm;

CubeModel::CubeModel(vec3 size) : Model()
{
	// Create Vertex Buffer for all the verices of the Cube
	vec3 halfSize = size * 0.5f;
	
	Vertex vertexBuffer[] = {  // position,                normal,                  color
								{ vec3(-halfSize.x,-halfSize.y,-halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec3(243.0f / 255.0f, 164.0f / 255.0f, 232.0f / 255.0f) }, //left - red
								{ vec3(-halfSize.x,-halfSize.y, halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec3(243.0f / 255.0f, 164.0f / 255.0f, 232.0f / 255.0f) },
								{ vec3(-halfSize.x, halfSize.y, halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec3(164.0f / 255.0f, 192.0f / 255.0f, 243.0f / 255.0f) },

								{ vec3(-halfSize.x,-halfSize.y,-halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec3(243.0f / 255.0f, 164.0f / 255.0f, 232.0f / 255.0f) },
								{ vec3(-halfSize.x, halfSize.y, halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec3(164.0f / 255.0f, 192.0f / 255.0f, 243.0f / 255.0f) },
								{ vec3(-halfSize.x, halfSize.y,-halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec3(164.0f / 255.0f, 192.0f / 255.0f, 243.0f / 255.0f) },

								{ vec3( halfSize.x, halfSize.y,-halfSize.z), vec3( 0.0f, 0.0f,-1.0f), vec3(164.0f / 255.0f, 192.0f / 255.0f, 243.0f / 255.0f) }, // far - blue
								{ vec3(-halfSize.x,-halfSize.y,-halfSize.z), vec3( 0.0f, 0.0f,-1.0f), vec3(243.0f / 255.0f, 164.0f / 255.0f, 232.0f / 255.0f) },
								{ vec3(-halfSize.x, halfSize.y,-halfSize.z), vec3( 0.0f, 0.0f,-1.0f), vec3(164.0f / 255.0f, 192.0f / 255.0f, 243.0f / 255.0f) },

								{ vec3( halfSize.x, halfSize.y,-halfSize.z), vec3( 0.0f, 0.0f,-1.0f), vec3(164.0f / 255.0f, 192.0f / 255.0f, 243.0f / 255.0f) },
								{ vec3( halfSize.x,-halfSize.y,-halfSize.z), vec3( 0.0f, 0.0f,-1.0f), vec3(243.0f / 255.0f, 164.0f / 255.0f, 232.0f / 255.0f) },
								{ vec3(-halfSize.x,-halfSize.y,-halfSize.z), vec3( 0.0f, 0.0f,-1.0f), vec3(243.0f / 255.0f, 164.0f / 255.0f, 232.0f / 255.0f) },

								{ vec3( halfSize.x,-halfSize.y, halfSize.z), vec3( 0.0f,-1.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f) }, // bottom - turquoise
								{ vec3(-halfSize.x,-halfSize.y,-halfSize.z), vec3( 0.0f,-1.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f) },
								{ vec3( halfSize.x,-halfSize.y,-halfSize.z), vec3( 0.0f,-1.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f) },
																
								{ vec3( halfSize.x,-halfSize.y, halfSize.z), vec3( 0.0f,-1.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f) },
								{ vec3(-halfSize.x,-halfSize.y, halfSize.z), vec3( 0.0f,-1.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f) },
								{ vec3(-halfSize.x,-halfSize.y,-halfSize.z), vec3( 0.0f,-1.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f) },

								{ vec3(-halfSize.x, halfSize.y, halfSize.z), vec3( 0.0f, 0.0f, 1.0f), vec3(164.0f / 255.0f, 192.0f / 255.0f, 243.0f / 255.0f) }, // near - green
								{ vec3(-halfSize.x,-halfSize.y, halfSize.z), vec3( 0.0f, 0.0f, 1.0f), vec3(243.0f / 255.0f, 164.0f / 255.0f, 232.0f / 255.0f) },
								{ vec3( halfSize.x,-halfSize.y, halfSize.z), vec3( 0.0f, 0.0f, 1.0f), vec3(243.0f / 255.0f, 164.0f / 255.0f, 232.0f / 255.0f) },

								{ vec3( halfSize.x, halfSize.y, halfSize.z), vec3( 0.0f, 0.0f, 1.0f), vec3(164.0f / 255.0f, 192.0f / 255.0f, 243.0f / 255.0f) },
								{ vec3(-halfSize.x, halfSize.y, halfSize.z), vec3( 0.0f, 0.0f, 1.0f), vec3(164.0f / 255.0f, 192.0f / 255.0f, 243.0f / 255.0f) },
								{ vec3( halfSize.x,-halfSize.y, halfSize.z), vec3( 0.0f, 0.0f, 1.0f), vec3(243.0f / 255.0f, 164.0f / 255.0f, 232.0f / 255.0f) },

								{ vec3( halfSize.x, halfSize.y, halfSize.z), vec3( 1.0f, 0.0f, 0.0f), vec3(164.0f / 255.0f, 192.0f / 255.0f, 243.0f / 255.0f) }, // right - purple
								{ vec3( halfSize.x,-halfSize.y,-halfSize.z), vec3( 1.0f, 0.0f, 0.0f), vec3(243.0f / 255.0f, 164.0f / 255.0f, 232.0f / 255.0f) },
								{ vec3( halfSize.x, halfSize.y,-halfSize.z), vec3( 1.0f, 0.0f, 0.0f), vec3(164.0f / 255.0f, 192.0f / 255.0f, 243.0f / 255.0f) },

								{ vec3( halfSize.x,-halfSize.y,-halfSize.z), vec3( 1.0f, 0.0f, 0.0f), vec3(243.0f / 255.0f, 164.0f / 255.0f, 232.0f / 255.0f) },
								{ vec3( halfSize.x, halfSize.y, halfSize.z), vec3( 1.0f, 0.0f, 0.0f), vec3(164.0f / 255.0f, 192.0f / 255.0f, 243.0f / 255.0f) },
								{ vec3( halfSize.x,-halfSize.y, halfSize.z), vec3( 1.0f, 0.0f, 0.0f), vec3(243.0f / 255.0f, 164.0f / 255.0f, 232.0f / 255.0f) },

								{ vec3( halfSize.x, halfSize.y, halfSize.z), vec3( 0.0f, 1.0f, 0.0f), vec3(82.0f / 255.0f, 191.0f / 255.0f, 82.0f / 255.0f) }, // top - grass green
								{ vec3( halfSize.x, halfSize.y,-halfSize.z), vec3( 0.0f, 1.0f, 0.0f), vec3(82.0f / 255.0f, 191.0f / 255.0f, 82.0f / 255.0f) },
								{ vec3(-halfSize.x, halfSize.y,-halfSize.z), vec3( 0.0f, 1.0f, 0.0f), vec3(82.0f / 255.0f, 191.0f / 255.0f, 82.0f / 255.0f) },

								{ vec3( halfSize.x, halfSize.y, halfSize.z), vec3( 0.0f, 1.0f, 0.0f), vec3(82.0f / 255.0f, 191.0f / 255.0f, 82.0f / 255.0f) },
								{ vec3(-halfSize.x, halfSize.y,-halfSize.z), vec3( 0.0f, 1.0f, 0.0f), vec3(82.0f / 255.0f, 191.0f / 255.0f, 82.0f / 255.0f) },
								{ vec3(-halfSize.x, halfSize.y, halfSize.z), vec3( 0.0f, 1.0f, 0.0f), vec3(82.0f / 255.0f, 191.0f / 255.0f, 82.0f / 255.0f) }
						};

	// Create a vertex array
	glGenVertexArrays(1, &mVertexArrayID);

	// Upload Vertex Buffer to the GPU, keep a reference to it (mVertexBufferID)
	glGenBuffers(1, &mVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer), vertexBuffer, GL_STATIC_DRAW);
}

CubeModel::~CubeModel()
{
	// Free the GPU from the Vertex Buffer
	glDeleteBuffers(1, &mVertexBufferID);
	glDeleteVertexArrays(1, &mVertexArrayID);
}

void CubeModel::Update(float dt)
{
	// If you are curious, un-comment this line to have spinning cubes!
	// That will only work if your world transform is correct...
	// mRotationAngleInDegrees += 90 * dt; // spins by 90 degrees per second

	Model::Update(dt);
}

void CubeModel::Draw()
{
	// Draw the Vertex Buffer
	// Note this draws a unit Cube
	// The Model View Projection transforms are computed in the Vertex Shader

	//Set current shader to be the environment Shader,  so that only cubes get reflect the environment, to reflect the skybox
	//First get the old shader
    ShaderType oldShader = (ShaderType)Renderer::GetCurrentShader();
	//Use the Environment shaders
	Renderer::SetShader(ShaderType::SHADER_ENVIRONMENT); 
	glUseProgram(Renderer::GetShaderProgramID());

	//Send the skybox texture to the shader
	GLuint textureLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "skybox");
    glUniform1i(textureLocation, 0);	// Set our Texture sampler to user Texture Unit 0

	// Send the view projection constants to the shader
	//Get the World, view and projection matricies
    const Camera* currentCamera = World::GetInstance()->GetCurrentCamera();
	mat4 projectionM = currentCamera->GetProjectionMatrix();

	glBindVertexArray(mVertexArrayID);

	GLuint WorldMatrixLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "WorldTransform"); 
	glUniformMatrix4fv(WorldMatrixLocation, 1, GL_FALSE, &GetWorldMatrix()[0][0]);

	GLuint ProjMatrixID = glGetUniformLocation(Renderer::GetShaderProgramID(), "ProjectionTransform");
	glUniformMatrix4fv(ProjMatrixID,  1, GL_FALSE, &projectionM[0][0]);

	mat4 viewMatrix = currentCamera->GetViewMatrix();

	//Get the view transform matrix
	GLuint ViewMatrixLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "ViewTransform"); 

	glUniformMatrix4fv(ViewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 1); 

	// 1st attribute buffer : vertex Positions
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glVertexAttribPointer(	0,				// attribute. No particular reason for 0, but must match the layout in the shader.
							3,				// size
							GL_FLOAT,		// type
							GL_FALSE,		// normalized?
							sizeof(Vertex), // stride
							(void*)0        // array buffer offset
						);

	// 2nd attribute buffer : vertex normal
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glVertexAttribPointer(	1,
							3,
							GL_FLOAT,
							GL_FALSE,
							sizeof(Vertex),
							(void*)sizeof(vec3)    // Normal is Offseted by vec3 (see class Vertex)
						);


	// 3rd attribute buffer : vertex color
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glVertexAttribPointer(	2,
							3,
							GL_FLOAT,
							GL_FALSE,
							sizeof(Vertex),
							(void*) (2* sizeof(vec3)) // Color is Offseted by 2 vec3 (see class Vertex)
						);

	// Draw the triangles !
	glDrawArrays(GL_TRIANGLES, 0, 36); // 36 vertices: 3 * 2 * 6 (3 per triangle, 2 triangles per face, 6 faces)

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	//Set shader back to the previous one
	Renderer::SetShader(oldShader);
	glUseProgram(Renderer::GetShaderProgramID());

}

bool CubeModel::ParseLine(const std::vector<ci_string> &token)
{
	if (token.empty())
	{
		return true;
	}
	else
	{
		return Model::ParseLine(token);
	}
}
