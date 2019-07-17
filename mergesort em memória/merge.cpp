#include <iostream>

using namespace std;


// função que recebe dois vetores ordenados a e b 
// de tamanhos m e n, respectivamente
// e intercala os dois vetores, gerando um 
// novo vetor c, de tamanho m+n
void intercala(int a[], int b[], int c[], int m, int n){
	// iteradores i, j e k são utilizados, respectivamente, para
	// percorrer os vetores a[], b[] e c[]
	int i = 0;
	int j = 0;
	
	for (int k = 0; k < m+n; k++) {
		if ((i < m) and (j < n)){ // ainda não terminou de percorrer a e b
			if (a[i] <= b[j]){ // considerando elementos repetidos (senão teste pode ser apenas "<")
				c[k] = a[i]; // copia elemento de a[] em c[]
				i++; // avança no vetor a[]
			} else { // b[j] é menor que a[i]
				c[k] = b[j];
				j++;
			}		
		} else if (i == m) { // terminou o vetor a[], copia de b[] em c[]
			c[k] = b[j];
			j++;
		} else { // terminou o vetor b[], copia de a[] em c[]
			c[k] = a[i];
			i++;
		}
	}
}

// função que recebe um vetor ordenado em dois trechos 
// a[inicio:meio] (trecho1) e a[meio+1:fim] (trecho2) e intercala os dois trechos
// no trecho a[inicio:fim], usando uma ideia similar à função
// intercala() e um vetor auxiliar aux[]
void intercala_vetor(int a[], int inicio, int meio, int fim){
	int i = inicio;
	int j = meio+1;
	int tamanho = fim - inicio + 1;
	int aux[tamanho];
	
	for (int k=0; k < tamanho; k++){
		if ((i <= meio) and (j <= fim)){ // ainda não terminou de percorrer trecho1 e trecho2
			if (a[i] <= a[j]){ // considerando elementos repetidos (senão teste pode ser apenas "<")
				aux[k] = a[i]; // copia elemento do trecho1 em aux[]
				i++; // avança no trecho1
			} else { // elemento no trecho2 é menor que no trecho1
				aux[k] = a[j];
				j++;
			}		
		} else if (i > meio) { // terminou o trecho1, copia trecho2 em aux[]
			aux[k] = a[j];
			j++;
		} else { // terminou o trecho2, copia trecho1 em aux[]
			aux[k] = a[i];
			i++;
		}		
	}	
	
	// agora copiamos do vetor auxiliar aux[] em a[inicio:fim]
	for (int k=0; k < tamanho; k++){ 
		a[inicio + k] = aux[k];
	}
}

// merge sort propriamente dito: encontra o meio do vetor,
// divide o vetor em dois, chama merge recursivamente, até tamanho do
// vetor ser igual a um... após isso retorna a recursão intercalando
// os elementos
void mergesort(int a[], int inicio, int fim){
	int meio;
	if (inicio < fim) {
		meio = (inicio + fim)/2; // acha meio de a[inicio:fim]
		// chama recursivamente mergesort nas duas metades
		mergesort(a, inicio, meio);
		mergesort(a, meio+1, fim);		
		intercala_vetor(a,inicio,meio,fim);
	}
}

int main(){
	int n;

	// recebendo o tamanho do vetor a ser ordenado
	cin >> n;
	
	// criando o vetor usando VLA 
	// http://en.wikipedia.org/wiki/Variable-length_array
	// http://stackoverflow.com/questions/1887097/variable-length-arrays-in-c
	
	int a[n];
	
	// lendo o vetor a
	for (int i=0; i < n; i++){
		cin >> a[i];
	}	
	
	// chamando mergesort no vetor a inteiro
	mergesort(a, 0, n-1);
	
	// imprimindo a[]
	for (int i=0; i < n; i++){
		cout << a[i] << " ";
	}
	
	cout << endl;
	
	return 0;
}
