#include <iostream>
using namespace std;
typedef int tipo;

class MinHeap {
    public:
        MinHeap(tipo vetor[], int tamanho);
        ~MinHeap();
        void Imprimir(int pos);
    private:
        tipo* mVetDados;
        int mTamanho;
        int Pai(int i);
        int Esquerdo(int i);
        int Direito(int i);
        void CorrigirDescendo(int i);
        void Arrumar();
};

MinHeap::MinHeap (tipo vetor[], int tamanho) {
    mTamanho = tamanho;
    mVetDados = new tipo [mTamanho];
    for (int i = 0; i < mTamanho; i++) {
        mVetDados[i] = vetor[i];
    }
    Arrumar();
}

MinHeap::~MinHeap () {
    delete[] mVetDados;
}

int MinHeap::Pai (int i) {
    return (i-1)/2;
}

int MinHeap::Esquerdo (int i) {
    return (2*i+1);
}

int MinHeap::Direito (int i) {
    return (2*i+2);
}

void MinHeap::CorrigirDescendo (int i) {
    int esquerdo = Esquerdo(i);
    int direito = Direito(i);
    int menor = i;

    if ((esquerdo < mTamanho) and mVetDados[esquerdo] < mVetDados[i]) {
        menor = esquerdo;
    }

    if ((direito < mTamanho) and mVetDados[direito] < mVetDados[menor]) {
        menor = direito;
    }

    if (menor != i) {
        swap(mVetDados[i],mVetDados[menor]);
        CorrigirDescendo(menor);
    }

}


void MinHeap::Arrumar () {
    for (int i = (mTamanho/2) - 1; i >= 0; i--) {
        CorrigirDescendo(i);
        Imprimir(i);
    }
}

void MinHeap::Imprimir(int pos) {
    cout << pos << ": ";
    for (int i = 0; i < mTamanho; ++i) {
        cout << mVetDados[i];
        
        if (i < mTamanho - 1) 
            cout << " ";
        else 
            cout << endl;

    }
}

int main() {
    int tam;
    cin >> tam;
    int vet[tam];
    for (int i = 0; i < tam; ++i) {
        cin >> vet[i];
    }
    MinHeap(vet, tam);
}