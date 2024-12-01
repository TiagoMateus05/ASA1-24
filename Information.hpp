#include <iostream>

class Information{
	private:
		int _numInteiros;
		int _tamanhoSequencia;
		int **_matrizOperacao;
		int *_sequencia;
		int _resultado;
		void criarMatrizOperacao();
		void destruirMatrizOperacao();

	public:
		Information(int numInteiros, int tamanhoSequencia);
		~Information();
		void setNumInteiros(const int num);
		void setTamanhoSequencia(const int num);
		int getNumInteiros() const;
		int getTamanhoSequencia() const;
		void printInfo();
};