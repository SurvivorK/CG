#pragma once
#pragma once

#include <glm/glm.hpp>
#include "../base/shader.h"

class Line {
public:
	Line(const glm::vec2 &endx, const glm::vec2 &endy);

	~Line();

	void render();

private:
	glm::vec2 _vertices[2];

	const char* _vsCode =
		"#version 330 core\n"
		"layout(location = 0) in vec2 aPosition;\n"
		"void main() {\n"
		"	gl_Position = vec4(aPosition, 0.0f, 1.0f);\n"
		"}\n";

	const char* _fsCode =
		"#version 330 core\n"
		"out vec4 fragColor;\n"
		"void main() {\n"
		"	fragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);\n"
		"}\n";

	Shader _shader = { _vsCode, _fsCode };

	GLuint _vao = 0;

	GLuint _vbo = 0;
};