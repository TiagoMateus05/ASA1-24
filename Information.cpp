#include "Information.hpp"

Information::Information(int numInteiros, int tamanhoSequencia){
	_numInteiros = numInteiros;
	_tamanhoSequencia = tamanhoSequencia;
	criarMatrizOperacao();
	_sequencia = new int[_tamanhoSequencia];
	for (int i = 0; i < tamanhoSequencia;i++)
		std::cin >> _sequencia[i];
	std::cin >> _resultado;
}

Information::~Information(){
	destruirMatrizOperacao();
	delete[] _sequencia;
}

void Information::setNumInteiros(const int num){
	_numInteiros = num;
}

void Information::setTamanhoSequencia(const int num){
	_tamanhoSequencia = num;
}

int Information::getNumInteiros() const{
	return _numInteiros;
}

int Information::getTamanhoSequencia() const{
	return _tamanhoSequencia;
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
}