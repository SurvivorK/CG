#pragma once

#include "instanced_model.h"

InstancedModel::InstancedModel(
	const std::vector<Vertex>& vertices, 
	const std::vector<uint32_t>& indices) {
	glGenBuffers(1, &_instanceBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _instanceBuffer);
	glBufferData(GL_ARRAY_BUFFER, 100000 * sizeof(glm::mat4), , GL_STATIC_DRAW);


}

void InstancedModel::append(
	const glm::vec3& position, 
	const glm::quat& rotation, 
	const glm::vec3& scale) {
	_positions.push_back(position);
	_rotations.push_back(rotation);
	_scales.push_back(scale);
}

void InstancedModel::draw() {
	for (std::size_t i = 0; i < _vaos.size(); ++i) {
		glBindVertexArray(_vaos[i]);
		glDrawElementsInstanced(GL_TRIANGLES, , GL_UNSIGNED_INT, 0, amount);
		glBindVertexArray(0);
	}
}

