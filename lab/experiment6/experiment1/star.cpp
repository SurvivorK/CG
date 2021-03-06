#include "star.h"

Star::Star(const glm::vec2& position, float rotation, float radius, float aspect)
	: _position(position), _rotation(rotation), _radius(radius) {
	// assemble the vertex data of the star
	// write your code here
	// -------------------------------------
	//for (int i = 0; i < 5; ++i) {
	//	.....
	// }
	// -------------------------------------
	
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);

	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

Star::~Star() {
	if (_vbo) {
		glDeleteVertexArrays(1, &_vbo);
		_vbo = 0;
	}

	if (_vao) {
		glDeleteVertexArrays(1, &_vao);
		_vao = 0;
	}
}

void Star::render() {
	_shader.use();
	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLES, 0, sizeof(_vertices) / sizeof(glm::vec2));
}