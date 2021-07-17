#include <iostream>
#include "instanced_rendering.h"

int main() {
	try {
		InstancedRendering app("../model");
		app.run();
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}