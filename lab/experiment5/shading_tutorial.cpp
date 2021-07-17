#include <unordered_map>

#include <tiny_obj_loader.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "shading_tutorial.h"

ShadingTutorial::ShadingTutorial(const std::string& modelpath) {
	// init model
	_bunny.reset(importModel(modelpath));

	// init shaders
	initFlatShader();
	initLambertShader();
	initPhongShader();

	// init lights
	_directionalLight.reset(new DirectionalLight);
	_directionalLight->position = glm::vec3(10.0f, 10.0f, 10.0f);
	_directionalLight->rotation = glm::angleAxis(glm::radians(45.0f), -glm::vec3(1.0f, 1.0f, 1.0f));

	_spotLight.reset(new SpotLight);
	_spotLight->position = glm::vec3(0.0f, 0.0f, 5.0f);
	_spotLight->rotation = glm::vec3(0.0f, 0.0f, 0.0f);

	// init camera
	_camera.reset(new PerspectiveCamera(glm::radians(50.0f), 1.0f * _windowWidth / _windowHeight, 0.1f, 10000.0f));
	_camera->position.z = 10.0f;

	// init imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(_window, true);
	ImGui_ImplOpenGL3_Init();
}

ShadingTutorial::~ShadingTutorial() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

Model* ShadingTutorial::importModel(const std::string& filepath) {
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

void ShadingTutorial::initFlatShader() {
	const char* vertCode =
		"#version 330 core\n"
		"layout(location = 0) in vec3 aPosition;\n"
		"layout(location = 1) in vec3 aNormal;\n"
		"layout(location = 2) in vec2 aTexCoord;\n"
		"uniform mat4 model;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"
		"void main() {\n"
		"	gl_Position = projection * view * model * vec4(aPosition, 1.0f);\n"
		"}\n";

	const char* fragCode =
		"#version 330 core\n"
		"out vec4 color;\n"
		"struct Material {\n"
		"	vec3 albedo;\n"
		"	float ka;\n"
		"};\n"
		"uniform Material material;\n"
		"void main() {\n"
		"	vec3 result = material.ka * material.albedo;\n"
		"	color = vec4(result, 1.0f);\n"
		"}\n";

	_ambientShader.reset(new Shader(vertCode, fragCode));
}

void ShadingTutorial::initLambertShader() {
	// change the shader code for lambert shading
	const char* vertCode =
		"#version 330 core\n"
		"layout(location = 0) in vec3 aPosition;\n"
		"layout(location = 1) in vec3 aNormal;\n"
		"layout(location = 2) in vec2 aTexCoord;\n"

		"out vec3 FragPos;\n"
		"out vec3 Normal;\n"
		
		"uniform mat4 model;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"

		"void main() {\n"
		"	FragPos = vec3(model * vec4(aPosition, 1.0f));\n"
		"	Normal = mat3(transpose(inverse(model))) * aNormal;\n"
		"	gl_Position = projection * view * model * vec4(aPosition, 1.0f);\n"
		"}\n";

	const char* fragCode =
		"#version 330 core\n"
		"in vec3 FragPos;\n"
		"in vec3 Normal;\n"
		"out vec4 color;\n"
		"// material data structure declaration\n"
		"struct Material {\n"
		"	vec3 albedo;\n"
		"	float ka;\n"
		"	vec3 kd;\n"
		"};\n"
		
		"// directional light data structure declaration\n"
		"struct DirectionalLight {\n"
		"	vec3 direction;\n"
		"	float intensity;\n"
		"	vec3 color;\n"
		"};\n"
		
		"// spot light data structure declaration\n"
		"struct SpotLight {\n"
		"	vec3 position;\n"
		"	vec3 direction;\n"
		"	float intensity;\n"
		"	vec3 color;\n"
		"	float angle;\n"
		"	float kc;\n"
		"	float kl;\n"
		"	float kq;\n"
		"};\n"
		
		"// uniform variables\n"
		"uniform Material material;\n"
		"uniform DirectionalLight directionalLight;\n"
		"uniform SpotLight spotLight;\n"

		"vec3 calcDirectionalLight(vec3 normal) {\n"
		"	vec3 lightDir = normalize(-directionalLight.direction);\n"
		"	// diffuse color\n"
		"	vec3 diffuse = directionalLight.color * max(dot(lightDir, normal), 0.0f) * material.kd;\n"
		"	return directionalLight.intensity * diffuse ;\n"
		"}\n"

		"vec3 calcSpotLight(vec3 normal) {\n"
		"	vec3 lightDir = normalize(spotLight.position - FragPos);\n"
		"	float theta = acos(-dot(lightDir, normalize(spotLight.direction)));\n"
		"	if (theta > spotLight.angle) {\n"
		"		return vec3(0.0f, 0.0f, 0.0f);\n"
		"	}\n"
		"	vec3 diffuse = spotLight.color * max(dot(lightDir, normal), 0.0f) * material.kd;\n"
		"	float distance = length(spotLight.position - FragPos);\n"
		"	float attenuation = 1.0f / (spotLight.kc + spotLight.kl * distance + spotLight.kq * distance * distance);\n"
		"	return spotLight.intensity * attenuation * diffuse;\n"
		"}\n"
		
		"void main() {\n"
		"	vec3 normal = normalize(Normal);\n"
		"	// ambient color\n"
		"	vec3 ambient = material.ka * material.albedo;\n"
		"	// diffuse color\n"
		"	vec3 diffuse = calcDirectionalLight(normal) + calcSpotLight(normal);\n"
		"	color = vec4(ambient + diffuse, 1.0f);\n"
		"}\n";

	_lambertShader.reset(new Shader(vertCode, fragCode));
}

void ShadingTutorial::initPhongShader() {
	// change the shader code for phong shading
	const char* vertCode =
		"#version 330 core\n"
		"layout(location = 0) in vec3 aPosition;\n"
		"layout(location = 1) in vec3 aNormal;\n"
		"layout(location = 2) in vec2 aTexCoord;\n"
		"out vec3 FragPos;\n"
		"out vec3 Normal;\n"
		"uniform mat4 model;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"
		"void main() {\n"
		"	FragPos = vec3(model * vec4(aPosition, 1.0f));\n"
		"	Normal = mat3(transpose(inverse(model))) * aNormal;\n"
		"	gl_Position = projection * view * model * vec4(aPosition, 1.0f);\n"
		"}\n";

	// change the fragment shader code here
	// you can copy fragment shader code from lambert and change the following functions
	// just add specular term to the result will be enough
	//   + vec3 calcDirectionalLight(vec3 normal)
	//   + vec3 calcSpotLight(vec3 normal)
	const char* fragCode =
		"#version 330 core\n"
		"in vec3 FragPos;\n"
		"in vec3 Normal;\n"
		"out vec4 color;\n"
		"// material data structure declaration\n"
		"struct Material {\n"
		"	vec3 albedo;\n"
		"	float ka;\n"
		"	vec3 kd;\n"
		"	vec3 ks;\n"
		"	float ns;\n"
		"};\n"

		"// directional light data structure declaration\n"
		"struct DirectionalLight {\n"
		"	vec3 direction;\n"
		"	float intensity;\n"
		"	vec3 color;\n"
		"};\n"

		"// spot light data structure declaration\n"
		"struct SpotLight {\n"
		"	vec3 position;\n"
		"	vec3 direction;\n"
		"	float intensity;\n"
		"	vec3 color;\n"
		"	float angle;\n"
		"	float kc;\n"
		"	float kl;\n"
		"	float kq;\n"
		"};\n"

		"// uniform variables\n"
		"uniform Material material;\n"
		"uniform DirectionalLight directionalLight;\n"
		"uniform SpotLight spotLight;\n"
		"uniform vec3 viewPos;\n"

		"vec3 calcDirectionalLight(vec3 normal) {\n"
		"	vec3 lightDir = normalize(-directionalLight.direction);\n"
		"	vec3 viewDir = normalize(viewPos - FragPos);\n"
		"	vec3 reflectDir = reflect(-lightDir, normal);\n"
		"	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.ns);\n"
		"	vec3 specular = 0.5 * spec * directionalLight.color * material.ks;\n"
		"	// diffuse color\n"
		"	vec3 diffuse = directionalLight.color * max(dot(lightDir, normal), 0.0f) * material.kd;\n"
		"	return directionalLight.intensity * (diffuse + specular);\n"
		"}\n"

		"vec3 calcSpotLight(vec3 normal) {\n"
		"	vec3 lightDir = normalize(spotLight.position - FragPos);\n"
		"	float theta = acos(-dot(lightDir, normalize(spotLight.direction)));\n"
		"	if (theta > spotLight.angle) {\n"
		"		return vec3(0.0f, 0.0f, 0.0f);\n"
		"	}\n"
		"	vec3 viewDir = normalize(viewPos - FragPos);\n"
		"	vec3 reflectDir = reflect(-lightDir, normal);\n"
		"	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.ns);\n"
		"	vec3 specular = 0.5 * spec * spotLight.color * material.ks;\n"

		"	vec3 diffuse = spotLight.color * max(dot(lightDir, normal), 0.0f) * material.kd;\n"
		"	float distance = length(spotLight.position - FragPos);\n"
		"	float attenuation = 1.0f / (spotLight.kc + spotLight.kl * distance + spotLight.kq * distance * distance);\n"
		"	return spotLight.intensity * attenuation * (diffuse + specular);\n"
		"}\n"


		"void main() {\n"
		"	vec3 normal = normalize(Normal);\n"
		"	// ambient color\n"
		"	vec3 ambient = material.ka * material.albedo;\n"
		"	// diffuse color\n"
		"	vec3 diffuse = calcDirectionalLight(normal) + calcSpotLight(normal);\n"
		"	color = vec4(ambient + diffuse, 1.0f);\n"
		"}\n";


	_phongShader.reset(new Shader(vertCode, fragCode));
}

void ShadingTutorial::handleInput() {
	if (_keyboardInput.keyStates[GLFW_KEY_ESCAPE] != GLFW_RELEASE) {
		glfwSetWindowShouldClose(_window, true);
		return;
	}
	float _cameraMoveSpeed = 5;
	if (_keyboardInput.keyStates[GLFW_KEY_W] != GLFW_RELEASE) {
		_camera->position += _camera->getFront() * _cameraMoveSpeed * (float)_deltaTime;
	}

	if (_keyboardInput.keyStates[GLFW_KEY_A] != GLFW_RELEASE) {
		_camera->position -= _camera->getRight() * _cameraMoveSpeed * (float)_deltaTime;
	}

	if (_keyboardInput.keyStates[GLFW_KEY_S] != GLFW_RELEASE) {
		_camera->position -= _camera->getFront() * _cameraMoveSpeed * (float)_deltaTime;
	}

	if (_keyboardInput.keyStates[GLFW_KEY_D] != GLFW_RELEASE) {
		_camera->position += _camera->getRight() * _cameraMoveSpeed * (float)_deltaTime;
	}
	float _cameraRotateSpeed = 0.3;
	if (_mouseInput.move.xCurrent != _mouseInput.move.xOld) {
		std::cout << "mouse move in x direction" << std::endl;
		// rotate around world up: glm::vec3(0.0f, 1.0f, 0.0f)
		const float angle = -_cameraRotateSpeed * _deltaTime * 5 * (_mouseInput.move.xCurrent - _mouseInput.move.xOld);
		const glm::vec3 axis = glm::vec3(0.0f, 1.0f, 0.0f);
		/* write your code here */
		// you should know how quaternion works to represent rotation
		_camera->rotation = glm::angleAxis(angle, axis) * _camera->rotation;
		_mouseInput.move.xOld = _mouseInput.move.xCurrent;
	}

	if (_mouseInput.move.yCurrent != _mouseInput.move.yOld) {
		std::cout << "mouse move in y direction" << std::endl;
		/* write your code here */
		// rotate around local right
		const float angle = -_cameraRotateSpeed * _deltaTime * 5 * (_mouseInput.move.yCurrent - _mouseInput.move.yOld);
		const glm::vec3 axis = _camera->getRight();
		// you should know how quaternion works to represent rotation
		_camera->rotation = glm::angleAxis(angle, axis) * _camera->rotation;
		_mouseInput.move.yOld = _mouseInput.move.yCurrent;
	}
}

void ShadingTutorial::renderFrame() {
	// some options related to imGUI
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

	switch (_renderMode) {
	case RenderMode::Ambient:
		_ambientShader->use();
		// 1. transfer mvp matrix to the shader
		_ambientShader->setMat4("projection", _camera->getProjectionMatrix());
		_ambientShader->setMat4("view", _camera->getViewMatrix());
		_ambientShader->setMat4("model", _bunny->getModelMatrix());
		// 2. transfer material attributes to the shader
		_ambientShader->setVec3("material.albedo", _albedo);
		_ambientShader->setFloat("material.ka", _ka);
		// 3. transfer light attributes to the shader
		// simply do nothing
		break;
	case RenderMode::Lambert:
		_lambertShader->use();
		// 1. transfer mvp matrix to the shader
		_lambertShader->setMat4("projection", _camera->getProjectionMatrix());
		_lambertShader->setMat4("view", _camera->getViewMatrix());
		_lambertShader->setMat4("model", _bunny->getModelMatrix());
		// 2. transfer material attributes to the shader
		_lambertShader->setVec3("material.albedo", _albedo);
		_lambertShader->setFloat("material.ka", _ka);
		_lambertShader->setVec3("material.kd", _kd);
		// 3. transfer light attributes to the shader
		_lambertShader->setVec3("spotLight.position", _spotLight->position);
		_lambertShader->setVec3("spotLight.direction", _spotLight->getFront());
		_lambertShader->setFloat("spotLight.intensity", _spotLight->intensity);
		_lambertShader->setVec3("spotLight.color", _spotLight->color);
		_lambertShader->setFloat("spotLight.angle", _spotLight->angle);
		_lambertShader->setFloat("spotLight.kc", _spotLight->kc);
		_lambertShader->setFloat("spotLight.kl", _spotLight->kl);
		_lambertShader->setFloat("spotLight.kq", _spotLight->kq);
		_lambertShader->setVec3("directionalLight.direction", _directionalLight->getFront());
		_lambertShader->setFloat("directionalLight.intensity", _directionalLight->intensity);
		_lambertShader->setVec3("directionalLight.color", _directionalLight->color);
		break;
	case RenderMode::Phong:
		_phongShader->use();
		// 1. transfer mvp matrix to the shader
		_phongShader->setMat4("projection", _camera->getProjectionMatrix());
		_phongShader->setMat4("view", _camera->getViewMatrix());
		_phongShader->setMat4("model", _bunny->getModelMatrix());
		_phongShader->setVec3("viewPos", _camera->position);
		// 2. transfer material attributes to the shader
		_phongShader->setVec3("material.albedo", _albedo);
		_phongShader->setFloat("material.ka", _ka);
		_phongShader->setVec3("material.kd", _kd);
		_phongShader->setVec3("material.ks", _ks);
		_phongShader->setFloat("material.ns", _ns);
		// 3. transfer light attributes to the shader
		_phongShader->setVec3("spotLight.position", _spotLight->position);
		_phongShader->setVec3("spotLight.direction", _spotLight->getFront());
		_phongShader->setFloat("spotLight.intensity", _spotLight->intensity);
		_phongShader->setVec3("spotLight.color", _spotLight->color);
		_phongShader->setFloat("spotLight.angle", _spotLight->angle);
		_phongShader->setFloat("spotLight.kc", _spotLight->kc);
		_phongShader->setFloat("spotLight.kl", _spotLight->kl);
		_phongShader->setFloat("spotLight.kq", _spotLight->kq);
		_phongShader->setVec3("directionalLight.direction", _directionalLight->getFront());
		_phongShader->setFloat("directionalLight.intensity", _directionalLight->intensity);
		_phongShader->setVec3("directionalLight.color", _directionalLight->color);
		break;
	}

	// draw the bunny
	_bunny->draw();

	// draw ui elements
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	const auto flags =
		ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoSavedSettings;

	if (!ImGui::Begin("Control Panel", nullptr, flags)) {
		ImGui::End();
	} else {
		ImGui::Text("Render Mode");
		ImGui::Separator();
		ImGui::RadioButton("ambient", (int*)&_renderMode, (int)(RenderMode::Ambient));
		ImGui::RadioButton("lambert", (int*)&_renderMode, (int)(RenderMode::Lambert));
		ImGui::RadioButton("phong", (int*)&_renderMode, (int)(RenderMode::Phong));
		ImGui::Checkbox("wireframe", &wireframe);
		ImGui::NewLine();

		ImGui::Text("directional light");
		ImGui::Separator();
		ImGui::SliderFloat("intensity##1", &_directionalLight->intensity, 0.0f, 2.0f);
		ImGui::ColorEdit3("color##1", (float*)&_directionalLight->color);
		ImGui::NewLine();

		ImGui::Text("spot light");
		ImGui::Separator();
		ImGui::SliderFloat("intensity##2", &_spotLight->intensity, 0.0f, 5.0f);
		ImGui::ColorEdit3("color##2", (float*)&_spotLight->color);
		ImGui::SliderFloat("angle##2", (float*)&_spotLight->angle, 0.0f, glm::radians(180.0f), "%f rad");
		ImGui::NewLine();

		ImGui::Text("Material");
		ImGui::Separator();
		ImGui::ColorEdit3("albedo", (float*)&_albedo);
		ImGui::SliderFloat("ka", &_ka, 0.0f, 1.0f);
		ImGui::ColorEdit3("kd", (float*)&_kd);
		ImGui::ColorEdit3("ks", (float*)&_ks);
		ImGui::SliderFloat("ns", &_ns, 0.0f, 50.0f);

		ImGui::End();
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}