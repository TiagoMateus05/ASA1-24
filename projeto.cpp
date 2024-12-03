#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
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
		void printSolução();
		std::string constroiParenteses(int x, int y, int val);
		bool isNumberInList(int x, int y, int num);
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

bool Information::isNumberInList(int x, int y, int num) {
	int list_size = _matrizResultados[x][y].size();
	for (int i = 0; i < list_size; i++) {
		if (num == _matrizResultados[x][y][i][0])
			return true;
	}
	return false;
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
			for (int j = a + i - 1; j >= a; --j) {
				int size_u = _matrizResultados[a][j].size();
				int size_v = _matrizResultados[j+1][a+i].size();
				bool breakOuterLoop = false;
				for(int u = 0; u < size_u; u++ ) {
					for (int v = 0; v < size_v; v++) {
						int v1 = _matrizResultados[a][j][u][0];
						int v2 = _matrizResultados[j+1][a+i][v][0];
						int res = _matrizOperacao[v1 - 1][v2 - 1];
						//std::cout << "(" << a << "," << j << ") & (" << j+1 << "," << a+i << ")" << std::endl;
						if (isNumberInList(a, a+i, res)) {
							breakOuterLoop = true;
							continue;
						}

						if (_matrizResultados[a][a+i].size() == _numInteiros) {
							breakOuterLoop = true;
							break;
						}
						_matrizResultados[a][a+i].push_back({res, j, v1, v2});
					}
					if (breakOuterLoop)
						break;
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
	printSolução();
	auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Time taken: " << duration.count() << " milliseconds" << std::endl;
}

std::string Information::constroiParenteses(int x, int y, int val) {
    std::stringstream ss;
	int list_size = _matrizResultados[x][y].size();
	if (x == y){
		ss << val;
		return ss.str();
	}

	for (int i = 0; i < list_size; i++) {
		if (val == _matrizResultados[x][y][i][0]) {
			ss << "(" << constroiParenteses(
				x,
				_matrizResultados[x][y][i][1],
				_matrizResultados[x][y][i][2]
			) << " " << constroiParenteses(
				_matrizResultados[x][y][i][1] + 1,
				y,
				_matrizResultados[x][y][i][3]
			) << ")";
			break;
		}
	}
	return ss.str();
}

void Information::printSolução(){
	std::cout << _resultado << std::endl;
	std::cout << constroiParenteses(0, _tamanhoSequencia - 1, _resultado) << std::endl;
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
