#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char **argv){

	std::ifstream inputFile;
	(void)argc;
	inputFile.open(argv[1], std::ifstream::in);
	if (!inputFile.is_open())
		return (EXIT_FAILURE);
	
	std::string buffer;
	std::getline(inputFile, buffer);
	std::string tempNumber = buffer.substr(0, buffer.find(' '));
	std::cout << "Temp number:" << tempNumber << std::endl;
	int numNumbers = std::stoi(tempNumber);
	std::cout << numNumbers << std::endl;

}