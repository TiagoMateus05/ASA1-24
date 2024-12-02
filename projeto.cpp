#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include "Information.hpp"

class Information{
	private:
		int _numInteiros;
		int _tamanhoSequencia;
		int **_matrizOperacao;
		int **_matrizResultados;
		int *_sequencia;
		int _resultado;
		void criarMatrizOperacao();
		void destruirMatrizOperacao();
		void destruirMatrizResultados();
		void calcularValorCelula();

	public:
		Information(int numInteiros, int tamanhoSequencia);
		~Information();
		void printInfo();
		void criarMatrizResultados();
};

Information::Information(int numInteiros, int tamanhoSequencia){
	_numInteiros = numInteiros;
	_tamanhoSequencia = tamanhoSequencia;
	criarMatrizOperacao();
	_sequencia = new int[_tamanhoSequencia];
	for (int i = 0; i < tamanhoSequencia;i++)
		std::cin >> _sequencia[i];
	std::cin >> _resultado;
	criarMatrizResultados();
}

Information::~Information(){
	destruirMatrizOperacao();
	destruirMatrizResultados();
	delete[] _sequencia;
}

void Information::criarMatrizOperacao(){
	_matrizOperacao = new int*[_numInteiros];
	for (int i = 0; i < _numInteiros; i++){
		_matrizOperacao[i] = new int[_numInteiros];
		for (int a = 0; a < _numInteiros; a++){
			std::cin >> _matrizOperacao[i][a];
		}
	}
}

void Information::destruirMatrizOperacao(){
	for (int i = 0; i < _numInteiros; i++){
		delete[] _matrizOperacao[i];
	}
	delete[] _matrizOperacao;
}

void Information::destruirMatrizResultados(){
	for (int i = 0; i < _numInteiros; i++){
		delete[] _matrizResultados[i];
	}
	delete[] _matrizResultados;	
}

void Information::printInfo(){

	std::cout << "Número de inteiros: " << _numInteiros << std::endl;
	std::cout << "Tamanho da sequência: " << _tamanhoSequencia << std::endl;  
	
	//Imprime matriz operação
	for (int i = 0; i < _numInteiros; i++){
		for (int a = 0; a < _numInteiros; a++){
			std::cout << _matrizOperacao[i][a] << " ";
		}
		std::cout << std::endl;
	}	

	//Imprime Sequência
	for (int i = 0; i < _tamanhoSequencia; i++)
		std::cout << _sequencia[i] << " ";
	std::cout << std::endl;

	//Imprime resultado
	std::cout << _resultado << std::endl;

	//Imprime matriz resultados
	std::cout << std::endl << std::endl << "Matriz resultados:" << std::endl;
	for (int i = 0; i < _tamanhoSequencia; i++){
		for (int a = 0; a < _tamanhoSequencia; a++){
			std::cout << _matrizResultados[i][a] << " ";
		}
		std::cout << std::endl;
	}	
}

void Information::calcularValorCelula(){
	// Função recursiva que calcula os valores possíveis de cada
	// célula com base nos outros valores já presentes na tabela.
}

void Information::criarMatrizResultados(){
	_matrizResultados = new int*[_tamanhoSequencia];
	for (int i = 0; i < _tamanhoSequencia; i++){
		_matrizResultados[i] = new int[_tamanhoSequencia];
		_matrizResultados[i][i] = _sequencia[i];
		std::cout << "i: " << i << std::endl << "sequencia[i]: " << _sequencia[i] << std::endl;
	}
	for (int i = 0; i < _tamanhoSequencia; i++){
		for (int a = i + 1; a < _tamanhoSequencia; a++){
			_matrizResultados[i][a] = 0;
			calcularValorCelula();
		}
	}

}

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