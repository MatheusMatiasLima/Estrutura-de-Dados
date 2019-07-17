#include <iostream>

typedef int Dado;

class Noh {
    friend class Fila;
    private:
        Dado mDado;
        Noh* mPtProx;
    public:
        Noh(Dado d);
};

Noh::Noh (Dado d=0) {
    mDado = d;
    mPtProx = NULL;
}

class Fila {
    public:
        // Constroi uma fila vazia.
        Fila();
        // Desaloca memória de todos os nós da fila.
        ~Fila();
        // Remove e retorna o primeiro item da fila.
        Dado Remover();
        // Insere um item no final da fila.
        void Inserir(const Dado& d);
        // Retorna o primeiro item da fila sem remover.
        Dado Proximo() const;
        // Remove todos os itens da fila.
        void LimparTudo();
        // Consulta a quantidade de itens na fila.
        unsigned Tamanho() const { return mTamanho; }
        // Consulta se a fila está vaiza.
        bool Vazia() const;
        void Imprime();
    private:
        Noh* mPrimeiro;
        unsigned mTamanho;
};

using namespace std;

Fila::Fila() {
    mPrimeiro = NULL;
    mTamanho = 0;
}

Fila::~Fila() {
    LimparTudo();
}

void Fila::Inserir(const Dado& d) {
    Noh* novo = new Noh (d);
    if (Vazia()) {
        mPrimeiro = novo;
    }
    else {
        Noh* aux = mPrimeiro;
        while (aux->mPtProx != NULL) {
            aux = aux->mPtProx;
        }
        aux->mPtProx = novo;
    }
    mTamanho++;
}

Dado Fila::Remover() {
    Dado excluido = mPrimeiro->mDado;
    Noh* temp = mPrimeiro;
    mPrimeiro = mPrimeiro->mPtProx;
    delete temp;
    mTamanho--;
    return excluido;
}

Dado Fila::Proximo() const {
    return mPrimeiro->mDado;
}

void Fila::LimparTudo() {
    while (not(Vazia())) {
        Remover();
    }
}

bool Fila::Vazia() const {
    if (mTamanho == 0) {
        return true;
    }
    else {
        return false;
    }
}

void Fila::Imprime () {
    Noh* aux = mPrimeiro;
    while (aux != NULL) {
        cout << aux->mDado << " ";
        aux = aux->mPtProx;
    }
    cout << endl;
}

int main() {
    Fila fila;
    Dado valor;
    char comando;
    do {
        cin >> comando;
        switch (comando) {
            case 'i': // inserir
                cin >> valor;
                fila.Inserir(valor);
                break;
            case 'r': // remover
                cout << fila.Remover() << endl;
                break;
            case 'l': // limpar tudo
                fila.LimparTudo();
                break;
            case 't': // escrever tamanho
                cout << fila.Tamanho() << endl;
                break;
            case 'e': // espiar proximo
                cout << fila.Proximo() << endl;
                break;
            case 'f': // finalizar
                // vai verificar adiante
                break;
            case 'p':
                fila.Imprime();
            break;
            default:
                cerr << "comando inválido\n";
        }
    } while (comando != 'f'); // finalizar execução
    while (not fila.Vazia()) {
        cout << fila.Remover() << ' ';
    }
    cout << endl;
    return 0;
}
