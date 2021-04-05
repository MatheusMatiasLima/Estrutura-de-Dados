#include <iostream>
using namespace std;

void intercala(int vet[], int ini, int meio, int fim){
	int i = ini, j = meio;
	int tam = fim-ini+1;
	int aux[tam];
	int k = 0;
	
	while((i < meio) and (j <= fim)){
		if (vet[i] <= vet[j]){
			aux[k++] = vet[i++];
		} else {
			aux[k++] = vet[j++];
		}
	}	
	while(i < meio){
		aux[k++] = vet[i++];
	}
	
	while(j <= fim){
		aux[k++] = vet[j++]; 
	}
	
	for (int m = 0; m < tam; m++){
		vet[ini+m] = aux[m];
	}
	
}

int particiona(int vet[], int c, int f){
	int pivo = vet[c], i = c+1, j = f;
	
	while(i <= j){
		if(vet[i] <= pivo) i++;
		else if(pivo <= vet[j]) j--;
		else{
			swap(vet[i], vet[j]);
			i++;
			j--;
		}
	}
	vet[c] = vet[j];
	vet[j] = pivo;
	
	return j;
}

void insertionSort(int vet[], int tam){
	int pivo;
	int j;
	
	for (int i = 0; i < tam; i++){
		pivo = vet[i];
		j = i - 1;
		
		while ((j >= 0) && (pivo < vet[j])){
			vet[j+1] = vet[j];
			j--;
		}
		vet[j+1] = pivo;
	}
}

void insertionSortInverso(int vet[],int tam){
	int j;
	int pivo;
	
	for(int i = tam - 2; i >= 0; i--){
		pivo = vet[i];
		j = i+1;
		
		while((j < tam) and (pivo < vet[j])){
			vet[j-1] = vet[j];
			j++;
		}
		vet[j-1] = pivo;
	}
}

void selectionSort(int vet[], int tam){
	int pos_menor;
	int aux;
	
	for (int i = 0; i < tam -1; i++){
		pos_menor = i;
		
		for (int j = i +1; j < tam; j++){
			if (vet[j] < vet[pos_menor]){
				pos_menor = j;
			}
		}
		aux = vet[i];
		vet[i] = vet[pos_menor];
		vet[pos_menor] = aux;
	}
}

void bubbleSort(int vet[], int tam){
	for (int i = 0; i < tam; i++){	
		for (int j = 0; j < tam-1-i; j++){
			if (vet[j] > vet[j+1]){
				int aux = vet[j];
				vet[j] = vet[j+1];
				vet[j+1] = aux;
			}
		}
	}
}

void mergeSort(int vet[], int tam){
	int pivo, fim, x = 1;
	
	while(x < tam){
		pivo = 0;
		
		while (pivo + x < tam){
			fim = pivo + 2 * x - 1;
			
			if (fim >= tam){
				fim = tam - 1;
			}
			intercala(vet, pivo, pivo + x, fim);
			
			pivo = pivo + 2 * x;
		}
		x = 2 * x;
	}
}

void quickSort(int vet[], int pivo, int fim){
	int novo_pivo;
	
	if(pivo < fim){
		novo_pivo = particiona(vet, pivo, fim);
		quickSort(vet, pivo, novo_pivo-1);
		quickSort(vet, novo_pivo+1, fim);
	}
}

void shellSort(int vet[], int tam){
	int gaps[9] ={1, 4, 10, 23, 57, 132, 301, 701, 1750};
	int pos_gap = 8;
	
	while(gaps[pos_gap] > tam){
		pos_gap--;
	}	
	
	int gap = gaps[pos_gap];
	int value;
	int j;
	
	while(pos_gap >= 0){
		for (int i = gap; i < tam; i++){
			value = vet[i];
			j = i;
			
			while ((j >= gap) and (value < vet[j-gap])){
				vet[j] = vet[j - gap];
				j = j - gap;
			}
			vet[j] = value;
		}
		pos_gap--;
		gap = gaps[pos_gap];
	}
}

int main(){
	int tam;
	cin >> tam;
	int vet[tam];
	
	for (int i = 0; i < tam; i++){
		cin >> vet[i];
	}
	//Metodos
	//insertionSort(vet, tam);
	//insertionSortInverso(vet, tam);
	//selectionSort(vet, tam);
	//bubbleSort(vet, tam);
	//mergeSort(vet, tam);
	//quickSort(vet, 0, tam-1);
	//shellSort(vet, tam);
	
	for (int i = 0; i < tam; i++){
		cout << vet[i] << " ";
	}
	
	return 0;
}
