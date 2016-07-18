#include "Player.h"
#include "globals.h"
#include <glm\gtc\matrix_transform.hpp>


Player::Player(const glm::vec3 pos) :
	OpenMeshObject("shaders\\spherical.vert", "shaders\\simple.frag", pos, glm::vec4(0.2, 0.2, 0.6, 1), "meshes\\sphere.obj", "textures\\frontend-large.bmp")

{
}

void Player::init() {
	OpenMeshObject::init();

	// Initialize vertices buffer and transfer it to OpenGL
	{
		// Create and bind the Mesh Vertex Array Object
		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		// Create and load vertex data into a Vertex Buffer Object
		{
			glGenBuffers(1, &_vbo);
			glBindBuffer(GL_ARRAY_BUFFER, _vbo);
			glBufferData(GL_ARRAY_BUFFER,
				sizeof(glm::vec4) * _vertices.size(),
				&_vertices[0],
				GL_STATIC_DRAW);

			// Obtain attribute handles:
			GLint _posAttr = glGetAttribLocation(_programID, "position");
			glEnableVertexAttribArray(_posAttr);
			glVertexAttribPointer(_posAttr, // attribute handle
				4,          // number of scalars per vertex
				GL_FLOAT,   // scalar type
				GL_FALSE,
				sizeof(glm::vec4),
				0);

			// Unbind vertex array:
			glBindVertexArray(0);
		}
	}

	_position.z -= getSize() / 2;
}

void Player::move(Commands comm) { _commands[comm] = true; }

void Player::movelogic(glm::vec3 dir, float speed, Commands comm)
{
	_commands[comm] = false;
	_position += dir*speed;
}

GLuint Player::update(int deltaTime) { 
	float delta = deltaTime * 0.001f;
	float speed = MOVE_SPEED * delta;

	if (_commands[MOVE_UP]) { movelogic(glm::vec3(0, 0, -1), speed, Commands::MOVE_UP); }
	if (_commands[MOVE_DOWN]) { movelogic(glm::vec3(0, 0, 1), speed, Commands::MOVE_DOWN); }
	if (_commands[MOVE_RIGHT]) { movelogic(glm::vec3(1, 0, 0), speed, Commands::MOVE_RIGHT); }
	if (_commands[MOVE_LEFT]) { movelogic(glm::vec3(-1, 0, 0), speed, Commands::MOVE_LEFT); }
	_model = glm::translate(glm::mat4(1), _position);
	return 0; 
}

void Player::draw(const glm::mat4 & projection, const glm::mat4& view, const glm::vec3 camPos, glm::vec3 lightPos, glm::vec4 lightColor)
{
	BEGIN_OPENGL;
	{
		_useMVP(projection, view);
		_setWorldUniforms(camPos, lightPos, lightColor);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBindVertexArray(_vao);

		// Get a handle for our "gMaterialColor" uniform
		GLuint materialID = getUniformLocation(MATERIAL_COLOR);
		glUniform4f(materialID, _color.r, _color.g, _color.b, _color.a);

		GLuint textureSamplerID = getUniformLocation(TEXTURE_SAMPLER);
		glUniform1i(textureSamplerID, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _textureID);

		//draw
		glDrawArrays(GL_TRIANGLES, 0, _vertices.size());

		// Unbind the Vertex Array object
		glBindVertexArray(0);
	}
	END_OPENGL;
}

