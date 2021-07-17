#pragma once

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "../base/vertex.h"

class InstancedModel {
public:
	InstancedModel(std::vector<Vertex> vertices, std::vector<uint32_t> indices);

	void append(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale);

	void draw();

private:
	std::vector<Vertex> _vertices;
	std::vector<uint32_t> _indices;

	std::vector<GLuint> _vaos;
	std::vector<GLuint> _vbos;
	std::vector<GLuint> _ebo;

	std::vector<glm::vec3> _positions;
	std::vector<glm::quat> _rotations;
	std::vector<glm::vec3> _scales;

	GLuint _instanceBuffer = 0;
};