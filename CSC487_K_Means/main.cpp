#include <iostream>
#include <atomic>
#include "CC_Interface.h"

// because I'm lazy
#include <string>

constexpr size_t hardcoded_k = 12;
static_assert(hardcoded_k <= default_max_k);
static_assert(hardcoded_k >= default_min_k);


int main(int argc, char** argv) {
	if (argc < 2) {
		std::cout << "No image supplied." << std::endl;
		return 0;
	}
	std::string filename = argv[1];
	
	CC_Interface cc_interface;
	cc_interface.ImageLoad(filename.c_str());
	if (!cc_interface.InputIsValid()) {
		return 1;
	}
	cc_interface.Process(hardcoded_k, CC_AlgorithmType::kMeansUnweighted);
	cc_interface.Display();

	std::cin.get();
	cc_interface.Close();

	filename += "01.jpeg";
	if (!cc_interface.CanSave()) {
		return 2;
	}
	cc_interface.Save(filename.c_str(), CC_FileType::jpeg);

	return 0;
}
