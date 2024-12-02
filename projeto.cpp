#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>

#include <chrono>

//[res_val, x, val1, val2]
const int INFO_ARRAY = 4;


class Information{
	private:
		int _numInteiros;
		int _tamanhoSequencia;
		std::vector<std::vector<std::vector<std::array<int, INFO_ARRAY>>>> _matrizResultados;
		std::vector<std::vector<int>> _matrizOperacao;
		std::vector<int> _sequencia;
		int _resultado;
		void criarMatrizOperacao();
		void calcularValorCelulas();

	public:
		Information(int numInteiros, int tamanhoSequencia);
		//void printInfo();
		void criarMatrizResultados();
};

Information::Information(int numInteiros, int tamanhoSequencia){
	_numInteiros = numInteiros;
	_tamanhoSequencia = tamanhoSequencia;
	criarMatrizOperacao();
	_sequencia.resize(_tamanhoSequencia);
	for (int i = 0; i < tamanhoSequencia;i++)
		std::cin >> _sequencia[i];
	std::cin >> _resultado;
	criarMatrizResultados();
}

void Information::criarMatrizOperacao(){
	_matrizOperacao.resize(_tamanhoSequencia);
	for (int i = 0; i < _numInteiros; i++){
		_matrizOperacao[i].resize(_tamanhoSequencia);
		for (int a = 0; a < _numInteiros; a++){
			std::cin >> _matrizOperacao[i][a];
		}
	}
}

void Information::calcularValorCelulas(){
	
	//[res_val, x, val1, val2]
	for(int i = 1; i < _tamanhoSequencia; i++){
		for (int a = 0; (a + i) < _tamanhoSequencia; a++){
			_matrizResultados[a][a+i].resize(0);
			//(a, a+i)
			for (int j = 0; a + j < a + i; j++) {
				int size_u = _matrizResultados[a][a+j].size();
				int size_v = _matrizResultados[a+j+1][a+i].size();
				for(int u = 0; u < size_u; u++ ) {
					for (int v = 0; v < size_v; v++) {
						int v1 = _matrizResultados[a][a+j][u][0];
						int v2 = _matrizResultados[a+j+1][a+i][v][0];
						_matrizResultados[a][a+i].push_back({_matrizOperacao[v1 - 1][v2 - 1], j, v1, v2});
					}
				}
				
			}
		}
	}
}

void Information::criarMatrizResultados(){
	_matrizResultados.resize(_tamanhoSequencia);
	for (int i = 0; i < _tamanhoSequencia; i++){
		_matrizResultados[i].resize(_tamanhoSequencia);
		_matrizResultados[i][i].push_back({ _sequencia[i], -1, -1, -1});
	}
	auto start = std::chrono::high_resolution_clock::now();
	std::cout << "Start: " << std::endl;
	calcularValorCelulas();
	auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Time taken: " << duration.count() << " milliseconds" << std::endl;
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
	return 0;
}
