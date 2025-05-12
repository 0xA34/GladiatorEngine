#include <vulkan/vulkan.h>
#include "GladiatorEngine.h"

int main() {
	GladiatorEngine gladiatorApp;

	try {
		gladiatorApp.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}