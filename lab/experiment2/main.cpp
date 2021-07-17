#include <cstdio>
#include <iostream>
#include "transformation.h"

int main() {
	try {
		Transformation app("C:/Users/Stellaris/OneDrive/code/CG/lab2/model/bunny.obj");
		app.run();
	} catch (std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	} catch (...) {
		std::cerr << "Unknown Error" << std::endl;
		exit(EXIT_FAILURE);
	}

	return 0;
}