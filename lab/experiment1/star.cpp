#include "star.h"

Star::Star() {
	for (int i = 0; i < 30; i++) _vertices[i] = glm::vec2(0, 0);
	glGenBuffers(1, &_vbo);
	glGenVertexArrays(1, &_vao);
}
void Star::check() {
	printf("%f %f\n", _position[0], _position[1]);
}
void Star::set(const glm::vec2& position, float rotation, float radius, float aspect) {
	// assemble the vertex data of the star
	// write your code here
	// -------------------------------------
	_position = position, _rotation = rotation, _radius = radius;
	float angle = rotation;
	float k = 0.382;
	printf("%f\n", aspect);
	for (int i = 0; i < 5; ++i) {
		_vertices[6 * i] = _position;
		_vertices[6 * i + 1] = _position + glm::vec2(cos(angle) * radius / aspect, sin(angle) * radius);
		angle = angle + theta;
		_vertices[6 * i + 2] = _position + glm::vec2(cos(angle) * radius * k / aspect, sin(angle) * radius * k);
		_vertices[6 * i + 3] = _position;
		_vertices[6 * i + 4] = _position + glm::vec2(cos(angle) * radius * k / aspect, sin(angle) * radius * k);
		angle = angle + theta;
		_vertices[6 * i + 5] = _position + glm::vec2(cos(angle) * radius / aspect, sin(angle) * radius);
	}
	
	

	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_DYNAMIC_DRAW);

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