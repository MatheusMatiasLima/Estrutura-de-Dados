using namespace std;

typedef int Dado;

void swap (Dado& a, Dado& b) {
    Dado aux = a;
    a = b;
    b = aux;
}

class MaxHeap {
    public:
        MaxHeap();
        ~MaxHeap();
        void Insere(Dado valor);
        void Imprimir(int pos);
        Dado RetirarRaiz();
        Dado OlharRaiz() { return mVetDados[0]; }
        bool Vazio() { return mTamanho == 0 ? true : false; }
    private:
        Dado* mVetDados;
        int mTamanho;
        int Pai(int i);
        int Esquerdo(int i);
        int Direito(int i);
        void CorrigirDescendo(int i);
        void CorrigirSubindo(int i);
};

MaxHeap::MaxHeap () {
    mTamanho = 0;
    mVetDados = new Dado [6];
}

MaxHeap::~MaxHeap () {
    delete[] mVetDados;
}

int MaxHeap::Pai (int i) {
    return (i-1)/2;
}

int MaxHeap::Esquerdo (int i) {
    return (2*i+1);
}

int MaxHeap::Direito (int i) {
    return (2*i+2);
}

void MaxHeap::CorrigirDescendo (int i) {
    int esquerdo = Esquerdo(i);
    int direito = Direito(i);
    int maior = i;

    if ((esquerdo < mTamanho) and mVetDados[esquerdo] > mVetDados[i]) {
        maior = esquerdo;
    }

    if ((direito < mTamanho) and mVetDados[direito] > mVetDados[maior]) {
        maior = direito;
    }

    if (maior != i) {
        swap(mVetDados[i],mVetDados[maior]);
        CorrigirDescendo(maior);
    }
}

void MaxHeap::CorrigirSubindo (int i) {
    int p = Pai(i);
    if (i > 0 and mVetDados[i] > mVetDados[p]) {
        swap(mVetDados[i], mVetDados[p]);
        CorrigirSubindo(p);
    }
}

Dado MaxHeap::RetirarRaiz() {
    if (mTamanho >= 1) {
        Dado aux = mVetDados[0];
        swap(mVetDados[0],mVetDados[mTamanho-1]);
        mTamanho--;
        CorrigirDescendo(0);
        return aux;
    }
}

void MaxHeap::Insere (Dado valor) {
        mVetDados[mTamanho] = valor;
        CorrigirSubindo(mTamanho);
        mTamanho++;
}