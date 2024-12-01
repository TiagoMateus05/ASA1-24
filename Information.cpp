#include "Information.hpp"

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
	}
	for (int i = 0; i < _tamanhoSequencia; i++){
		for (int a = 1; a < _tamanhoSequencia; a++){
			_matrizResultados[i][a] = 0;
			calcularValorCelula();
		}
	}

}