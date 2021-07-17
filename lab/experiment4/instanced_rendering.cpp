#include <unordered_map>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <tiny_obj_loader.h>
#include "skybox.h"
#include "instanced_rendering.h"


InstancedRendering::InstancedRendering(std::string basedir) {
	_windowTitle = "Instanced Rendering";

	_camera.position = glm::vec3(0.0f, 20.0f, 100.0f);
	_camera.rotation = glm::angleAxis(-glm::radians(20.0f), _camera.getRight());

	/* init imgui */
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(_window, true);
	ImGui_ImplOpenGL3_Init();

	/* import models */
	_planet.reset(importModel(basedir + "/" + "planet.obj"));
	_planet->position = glm::vec3(0.0f, -3.0f, 0.0f);
	_planet->scale = glm::vec3(4.0f, 4.0f, 4.0f);
	_planet->genTexture(basedir + "/" + "planet_Quom1200.png");
	_asternoid.reset(importModel(basedir + "/" + "rock.obj"));

	/* shader issues */
	const char* skyboxVsCode = 
		"#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"out vec3 texCoords;\n"
		"uniform mat4 projection;\n"
		"uniform mat4 view;\n"

		"void main() {\n"
		"	texCoords = aPos;\n"
		"	vec4 pos = projection * view * vec4(aPos, 1.0);\n"
		"	gl_Position = pos.xyww;\n"
		"}\n";
	const char* skyboxFsCode = 
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec3 texCoords;\n"
		"uniform samplerCube skybox;\n"
		"void main() {\n"
			"FragColor = texture(skybox, texCoords);\n"
		"}\n";
	_skyboxShader.reset(new Shader(skyboxVsCode, skyboxFsCode));

	const char* planetVsCode =
		"#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		//"layout (location = 2) in vec2 aTexCoords;\n"
		//"out vec2 TexCoords;\n"
		"uniform mat4 projection;\n"
		"uniform mat4 view;\n"
		"uniform mat4 model;\n"
		"void main() {\n"
		//"	TexCoords = aTexCoords;\n"
		"	gl_Position = projection * view * model * vec4(aPos, 1.0f);\n"
		"}\n";

	const char* planetFsCode =
		//"#version 330 core\n"
		//"out vec4 FragColor;\n"
		//"in vec2 TexCoords;\n"
		//"uniform sampler2D texture;\n"
		//"void main() {\n"
		//"	FragColor = texture(texture, TexCoords);\n"
		//"}\n";
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main() {\n"
		"	FragColor = vec4(0.0f, 0.0f, 0.5f, 1.0f);\n"
		"}\n";


	_planetShader.reset(new Shader(planetVsCode, planetFsCode));

	const char* asternoidVsCode =
		"#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		//"layout (location = 2) in vec2 aTexCoords;"
		//"out vec2 TexCoords;\n"
		"uniform mat4 projection;\n"
		"uniform mat4 view;\n"
		"uniform mat4 model;\n"
		"uniform mat4 rotate;\n"
		"void main() {\n"
		//"	TexCoords = aTexCoords;\n"
		"	gl_Position = projection * view * rotate * model *  vec4(aPos, 1.0f);\n"
		"}\n";

	const char* asternoidInstancedVsCode =
		"#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"layout(location = 3) in mat4 aInstanceMatrix;\n"
		"uniform mat4 projection;\n"
		"uniform mat4 view;\n"
		"uniform mat4 rotate;\n"
		"void main() {\n"
		//"	TexCoords = aTexCoords;\n"
		"	gl_Position = projection * view * rotate * aInstanceMatrix * vec4(aPos, 1.0f);\n"
		"}\n";

	const char* asternoidFsCode =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		//"in vec2 TexCoords;\n"
		//"uniform sampler2D texture_diffuse1;\n"
		"void main() {\n"
		//"	FragColor = texture(texture_diffuse1, TexCoords);\n"
		"FragColor = vec4(0.9f, 0.8f, 0.7f, 1.0f);\n"
		"}\n";

	_asternoidShader.reset(new Shader(asternoidVsCode, asternoidFsCode));
	_asternoidInstancedShader.reset(new Shader(asternoidInstancedVsCode, asternoidFsCode));

	skyBoxInit("../img/skybox/");
	
	const float radius = 70.0f;
	const float offset = 25.0f;
	for (int i = 0; i < _amount; ++i) {
		glm::mat4 model(1.0f);
		
		// translate
		float angle = (float)i / (float)_amount * 360.0f;
		float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float x = sin(angle) * radius + displacement;
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float y = displacement * 0.2f;
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float z = cos(angle) * radius + displacement;
		model = glm::translate(model, glm::vec3(x, y, z));

		// scale
		float scale = (rand() % 20) / 100.0f + 0.05;
		model = glm::scale(model, glm::vec3(scale));

		// rotate
		float rotAngle = (rand() % 360);
		model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));


		_modelMatrices.push_back(model);
	}
}

InstancedRendering::~InstancedRendering() {

}

void InstancedRendering::handleInput() {
	if (_keyboardInput.keyStates[GLFW_KEY_ESCAPE] != GLFW_RELEASE) {
		glfwSetWindowShouldClose(_window, true);
		return;
	}

	if (_keyboardInput.keyStates[GLFW_KEY_W] != GLFW_RELEASE) {
		_camera.position += _camera.getFront() * _cameraMoveSpeed * (float)_deltaTime;
	}

	if (_keyboardInput.keyStates[GLFW_KEY_A] != GLFW_RELEASE) {
		_camera.position -= _camera.getRight() * _cameraMoveSpeed * (float)_deltaTime;
	}

	if (_keyboardInput.keyStates[GLFW_KEY_S] != GLFW_RELEASE) {
		_camera.position -= _camera.getFront() * _cameraMoveSpeed * (float)_deltaTime;
	}

	if (_keyboardInput.keyStates[GLFW_KEY_D] != GLFW_RELEASE) {
		_camera.position += _camera.getRight() * _cameraMoveSpeed * (float)_deltaTime;
	}
	//if (_mouseInput.move.xCurrent != _mouseInput.move.xOld) {
	//	std::cout << "mouse move in x direction" << std::endl;
	//	// rotate around world up: glm::vec3(0.0f, 1.0f, 0.0f)
	//	const float angle = -_cameraRotateSpeed * _deltaTime * 5 * (_mouseInput.move.xCurrent - _mouseInput.move.xOld);
	//	const glm::vec3 axis = glm::vec3(0.0f, 1.0f, 0.0f);
	//	/* write your code here */
	//	// you should know how quaternion works to represent rotation
	//	_camera.rotation = glm::angleAxis(angle, axis) * _camera.rotation;
	//	_mouseInput.move.xOld = _mouseInput.move.xCurrent;
	//}

	//if (_mouseInput.move.yCurrent != _mouseInput.move.yOld) {
	//	std::cout << "mouse move in y direction" << std::endl;
	//	/* write your code here */
	//	// rotate around local right
	//	const float angle = -_cameraRotateSpeed * _deltaTime * 5 * (_mouseInput.move.yCurrent - _mouseInput.move.yOld);
	//	const glm::vec3 axis = _camera.getRight();
	//	// you should know how quaternion works to represent rotation
	//	_camera.rotation = glm::angleAxis(angle, axis) * _camera.rotation;
	//	_mouseInput.move.yOld = _mouseInput.move.yCurrent;
	//}
}
glm::mat4 rotation = glm::mat4(1.0f);
void InstancedRendering::renderFrame() {
	// some options related to imGUI
	static bool instanced = true;
	static bool wireframe = false;

	showFpsInWindowTitle();

	glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glEnable(GL_DEPTH_TEST);


	if (wireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	// glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// get camera properties
	glm::mat4 projection = _camera.getProjectionMatrix();
	glm::mat4 view = _camera.getViewMatrix();

	// draw skybox
	_skyboxShader->use();
	_skyboxShader->setMat4("view", glm::mat4(glm::mat3(view)));
	_skyboxShader->setMat4("projection", projection);
	drawSkyBox();

	// draw planet
	_planetShader->use();
	_planetShader->setMat4("model", _planet->getModelMatrix());
	_planetShader->setMat4("view", view);
	_planetShader->setMat4("projection", projection);
	_planet->draw();

	
	float aroundAngle = 5 * _deltaTime;
	rotation = glm::rotate(rotation, glm::radians(aroundAngle), _planet->getUp());


	// draw asternoids
	if (!instanced) {
		_asternoidShader->use();
		_asternoidShader->setMat4("view", view);
		_asternoidShader->setMat4("projection", projection);
		_asternoidShader->setMat4("rotate", rotation);
		for (int i = 0; i < _amount; ++i) {
			_asternoidShader->setMat4("model", _modelMatrices[i]);
			_asternoid->draw();
		}

	} else {
		_asternoidInstancedShader->use();
		_asternoidInstancedShader->setMat4("view", view);
		_asternoidInstancedShader->setMat4("projection", projection);
		_asternoidInstancedShader->setMat4("rotate", rotation);
		glBindVertexArray(_asternoid->_vao);
		
		unsigned int instanceVBO;
		glGenBuffers(1, &instanceVBO);
		glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * _amount, &_modelMatrices[0], GL_STATIC_DRAW);
		// glBindBuffer(GL_ARRAY_BUFFER, 0);

		// 拆分变换矩阵为4个列向量
		GLsizei vec4Size = sizeof(glm::vec4);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(vec4Size));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));
		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);

		glBindVertexArray(0);
		_asternoid->instancedDraw(_amount);

	}
	

	// draw ui
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Options");

	ImGui::Text("render method");
	ImGui::Checkbox("instanced", &instanced);

	ImGui::Text("render mode");
	ImGui::Checkbox("wireframe", &wireframe);

	ImGui::Text("clear color");
	ImGui::ColorEdit3("", (float*)&_clearColor);
	
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

Model* InstancedRendering::importModel(const std::string& filepath) {
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string err;

	std::string::size_type index = filepath.find_last_of("/");
	std::string mtlBaseDir = filepath.substr(0, index + 1);

	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &err, filepath.c_str(), mtlBaseDir.c_str())) {
		throw std::runtime_error("load " + filepath + " failure: " + err);
	}

	if (!err.empty()) {
		std::cerr << err << std::endl;
	}

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	std::unordered_map<Vertex, uint32_t> uniqueVertices;

	for (const auto& shape : shapes) {
		for (const auto& index : shape.mesh.indices) {
			Vertex vertex{};

			vertex.position.x = attrib.vertices[3 * index.vertex_index + 0];
			vertex.position.y = attrib.vertices[3 * index.vertex_index + 1];
			vertex.position.z = attrib.vertices[3 * index.vertex_index + 2];

			if (index.normal_index >= 0) {
				vertex.normal.x = attrib.normals[3 * index.normal_index + 0];
				vertex.normal.y = attrib.normals[3 * index.normal_index + 1];
				vertex.normal.z = attrib.normals[3 * index.normal_index + 2];
			}

			// not used for this experiment
			if (index.texcoord_index >= 0) {
				vertex.texCoord.x = attrib.texcoords[2 * index.texcoord_index + 0];
				vertex.texCoord.y = attrib.texcoords[2 * index.texcoord_index + 1];
			}

			// check if the vertex appeared before to reduce redundant data
			if (uniqueVertices.count(vertex) == 0) {
				uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
				vertices.push_back(vertex);
			}

			indices.push_back(uniqueVertices[vertex]);
		}
	}

	// in this experiment we will not process with any material...
	// no more code for material preprocess
	return new Model(vertices, indices);
}

