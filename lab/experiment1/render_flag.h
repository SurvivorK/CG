#pragma once

#include "../base/application.h"
#include "flag.h"
#include "star.h"
#include "Line.h"

class RenderFlag : public Application {
public:
	RenderFlag();

	~RenderFlag();

private:
	Flag* _flag = nullptr;
	static Star* _stars[5];
	Line* _lines[50] = { nullptr };
	void handleInput() override;
	static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
	void renderFrame() override;
};
