#include <iostream>
#include <fstream>
#include <string>
#include "Information.hpp"



int main(){
	//Disables sync between c++ standard streams and c standard
	// streams. It makes operations faster, but after this, c and 
	// c++ streams shouldnt be mixed, because they are not synced
	// and the output might appear in an unexpected order.
	std::ios::sync_with_stdio(0);

	//By default, std::cin is tied to std::cout, so before any
	// std::cin operation, std::cout is flushed. This disables that.
	// It avoids unnecessary flushing, improving performance, but
	// makes it so that the output should be manually flushed when
	// we want to make sure it outputs.
	std::cin.tie(0);


	int numInteiros;
	std::cin >> numInteiros;
	int tamanhoSequencia;
	std::cin >> tamanhoSequencia;

	Information info (numInteiros, tamanhoSequencia);
	info.printInfo();
}