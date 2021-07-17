#include "render_flag.h"

glm::vec2 pos2ndc(int x, int y, int w, int h) {
	return glm::vec2(-0.5f + (float)x / w, 0.5f - (float)y / h);
}
Star* RenderFlag::_stars[5];// = { new Star };
RenderFlag::RenderFlag() {
	if (glfwInit() != GLFW_TRUE) {
		throw std::runtime_error("init glfw failure");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	_window = glfwCreateWindow(
		_windowWidth, _windowHeight, _windowTitle.c_str(), nullptr, nullptr);

	if (_window == nullptr) {
		throw std::runtime_error("create glfw window failure");
	}

	glfwMakeContextCurrent(_window);
	glfwSetWindowUserPointer(_window, this);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error("initialize glad failure");
	}

	glViewport(0, 0, _windowWidth, _windowHeight);

	glfwSetFramebufferSizeCallback(_window, framebufferResizeCallback);

	_lastTimeStamp = std::chrono::high_resolution_clock::now();

	_flag = new Flag;
	// create 5 stars
	// write your code here
	// printf("%f %f\n", _windowWidth, _windowHeight);
	for (int i = 0; i < 5; i++)
		_stars[i] = new Star;
	int w = 900, h = 600;
	float aspect = (float)w / h;
	_stars[4]->set(pos2ndc(1, 1, 6, 4), pi / 2, 0.15, aspect);
	_stars[3]->set(pos2ndc(10, 2, 30, 20), pi / 2 - atan2(3.0, 5.0), 0.05, aspect);
	_stars[2]->set(pos2ndc(12, 4, 30, 20), pi + atan2(1.0, 7.0), 0.05, aspect);
	_stars[1]->set(pos2ndc(12, 7, 30, 20), pi / 2, 0.05, aspect);
	_stars[0]->set(pos2ndc(10, 9, 30, 20), pi / 2 - atan2(3.0, 5.0), 0.05, aspect);

	// draw guidelines
	for (int i = 0; i < 20; i++) {
		_lines[i] = new Line(glm::vec2(-0.5f, -0.5f + 0.05f * i), glm::vec2(0.5f, -0.5f + 0.05f * i));
	}
	for (int i = 20; i < 50; i++) {
		_lines[i] = new Line(glm::vec2(-0.5f + 1.0f * (i-20) / 30.0f, 0.5f), glm::vec2(-0.5f + 1.0f * (i-20) / 30.0f, -0.5f));
	}
	// hint: aspect_of_the_window = _windowWidth / _windowHeight
}

RenderFlag::~RenderFlag() {
	if (_flag) {
		delete _flag;
		_flag = nullptr;
	}

	for (int i = 0; i < 5; ++i) {
		delete _stars[i];
		_stars[i] = nullptr;
	}

	for (int i = 0; i < 50; i++) {
		delete _lines[i];
		_lines[i] = nullptr;
	}
}

void RenderFlag::handleInput() {
	// do nothing
	// int w, h;
	// glfwGetWindowSize(_window, &w, &h);
	// printf("%d %d\n", w, h);

}

void RenderFlag::renderFrame() {
	showFpsInWindowTitle();

	glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT);


	_flag->render();
	for (int i = 0; i < 5; ++i) {
		if (_stars[i] != nullptr) {
			_stars[i]->render();
			// _stars[i]->check();
		}
	}
	//for (int i = 0; i < 50; i++)
	//	if (_lines[i] != nullptr) {
	//		_lines[i]->render();
	//	}
}
void RenderFlag::framebufferResizeCallback(GLFWwindow* window, int w, int h) {
	RenderFlag* app = reinterpret_cast<RenderFlag*>(glfwGetWindowUserPointer(window));
	app->_windowWidth = w;
	app->_windowHeight = h;
	printf("%d %d\n", w, h);
	float aspect = (float)w / h;
	_stars[4]->set(pos2ndc(1, 1, 6, 4), pi / 2, 0.15, aspect);
	_stars[3]->set(pos2ndc(10, 2, 30, 20), pi / 2 - atan2(3.0, 5.0), 0.05, aspect);
	_stars[2]->set(pos2ndc(12, 4, 30, 20), pi + atan2(1.0, 7.0), 0.05, aspect);
	_stars[1]->set(pos2ndc(12, 7, 30, 20), pi / 2, 0.05, aspect);
	_stars[0]->set(pos2ndc(10, 9, 30, 20), pi / 2 - atan2(3.0, 5.0), 0.05, aspect);
	glViewport(0, 0, w, h);

}