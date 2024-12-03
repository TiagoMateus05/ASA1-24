#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_set>

//#include <chrono>

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
		void printSolucao();
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
	_matrizOperacao.resize(_numInteiros);
	for (int i = 0; i < _numInteiros; i++){
		_matrizOperacao[i].resize(_numInteiros);
		for (int a = 0; a < _numInteiros; a++){
			std::cin >> _matrizOperacao[i][a];
		}
	}
}

void Information::calcularValorCelulas() {
    for (int i = 1; i < _tamanhoSequencia; i++) {
        for (int a = 0; (a + i) < _tamanhoSequencia; a++) {
            auto& currentCell = _matrizResultados[a][a + i];
            currentCell.clear();
            currentCell.reserve(_numInteiros);

            std::unordered_set<int> resultsSet;
            bool reachedLimit = false;

            for (int j = a + i - 1; j >= a && !reachedLimit; --j) {
                const auto& leftCell = _matrizResultados[a][j];
                const auto& rightCell = _matrizResultados[j + 1][a + i];

                for (const auto& leftValue : leftCell) {
                    for (const auto& rightValue : rightCell) {
                        int v1 = leftValue[0];
                        int v2 = rightValue[0];
                        int res = _matrizOperacao[v1 - 1][v2 - 1];

                        if (resultsSet.insert(res).second) { // Insert only if unique
                            currentCell.push_back({ res, j, v1, v2 });

                            if ((int)currentCell.size() == _numInteiros) {
                                reachedLimit = true;
                                break;
                            }
                        }
                    }
                    if (reachedLimit) break;
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
	//auto start = std::chrono::high_resolution_clock::now();
	//std::cout << "Start: " << std::endl;
	calcularValorCelulas();
	/*auto end1 = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start);
	std::cout << "Time taken to Calculate: " << duration1.count() << " milliseconds" << std::endl;

	auto start1 = std::chrono::high_resolution_clock::now();*/
	printSolucao();
	/*auto end2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start1);
	std::cout << "Time taken to Resolve: " << duration2.count() << " milliseconds" << std::endl;

	auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Time taken: " << duration.count() << " milliseconds" << std::endl;*/
}

std::string Information::constroiParenteses(int x, int y, int val) {
    std::stringstream ss;
	bool resultFound = false;
	int list_size = _matrizResultados[x][y].size();

	if (x == y && val == _matrizResultados[x][y][0][0]){
		ss << val;
		return ss.str();
	}

	for (int i = 0; i < list_size; i++) {
		if (val == _matrizResultados[x][y][i][0]) {
			resultFound = true;
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
	if (resultFound)
		return ss.str();
	else
		return std::to_string(0);
}

void Information::printSolucao(){
	std::string tmp = constroiParenteses(0, _tamanhoSequencia - 1, _resultado);
	std::string res = (tmp == "0" ? "0" : "1\n" + tmp );
	std::cout << res << std::endl;
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
