#include <iostream>
#include <fstream>
#include <string>
#include "Information.hpp"



int main(){

	int numInteiros;
	std::cin >> numInteiros;
	int tamanhoSequencia;
	std::cin >> tamanhoSequencia;

	Information info (numInteiros, tamanhoSequencia);
	info.printInfo();
}