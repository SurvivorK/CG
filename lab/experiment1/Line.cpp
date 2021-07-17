#include "Line.h"

Line::Line(const glm::vec2& endx, const glm::vec2& endy) {
	_vertices[0] = endx;
	_vertices[1] = endy;
	// init vao and vbo
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);

	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

Line::~Line() {
	if (_vbo) {
		glDeleteBuffers(1, &_vbo);
		_vbo = 0;
	}

	if (_vao) {
		glDeleteBuffers(1, &_vao);
		_vao = 0;
	}
}

void Line::render() {
	_shader.use();
	glBindVertexArray(_vao);
	glDrawArrays(GL_LINE_STRIP, 0, 2);
}