#include <iostream>

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