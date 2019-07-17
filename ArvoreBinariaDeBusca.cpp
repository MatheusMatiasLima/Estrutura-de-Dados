#include <iostream>

using namespace std;

enum posicao {esq, dir};

typedef int Tipo;

class Noh {
    friend class Arvore;
    public:
        Noh(int chave = 0);
        ~Noh();
    private:
        Tipo mChave;
        Noh* mEsquerdo;
        Noh* mDireito;
        Noh* mPai;
};

Noh::Noh(int chave) {
    mChave = chave;
    mEsquerdo = NULL;
    mDireito = NULL;
    mPai = NULL;
}

Noh::~Noh() {
    delete mEsquerdo;
    delete mDireito;
}

class Arvore {
    public:
        Arvore();
        ~Arvore();
        void Inserir(Tipo chave);
        Noh* Buscar(Tipo chave);
        void Remover(Tipo chave);
        void EscreverOrdem();
        void EscreverPreOrdem();
        bool Vazia();
    private:
        Noh* mRaiz;
        void Transplanta(Noh* antigo, Noh* novo);
        Noh* Minimo(Noh* raiz);
        void EscreverOrdemAux(Noh* atual, int nivel);
        void EscreverPreOrdemAux(Noh* atual, int nivel);
};

Arvore::Arvore() {
    mRaiz = NULL;
}

Arvore::~Arvore() {
    delete mRaiz;
}

void Arvore::Inserir(Tipo chave) {
    Noh* novo = new Noh(chave);
    posicao posInsercao;
    
    if (mRaiz == NULL) {
        mRaiz = novo;
    } else {
        Noh* atual = mRaiz;
        Noh* pai = NULL;
        
        while (atual != NULL) {
            pai = atual;
            
            if (atual->mChave > chave) {
                atual = atual->mEsquerdo;
                posInsercao = esq;
            } else {
                atual = atual->mDireito;
                posInsercao = dir;
            }
        }
        
        novo->mPai = pai;
        
        if (posInsercao == esq) {
            pai->mEsquerdo = novo;
        } else {
            pai->mDireito = novo;
        }
    }
}

Noh* Arvore::Buscar (Tipo chave) {
    Noh* atual = mRaiz;
    
    while (atual != NULL) {
        if (atual->mChave == chave) {
            return atual;
        } else {
            if (atual->mChave > chave) {
                atual = atual->mEsquerdo;
            } else {
                atual = atual->mDireito;
            }
        }
    }
    
    return atual;
}

void Arvore::Remover (Tipo chave) {
    Noh* nohRemover = Buscar(chave);
    
    if (nohRemover != NULL) {
		if (nohRemover->mEsquerdo == NULL) {
			Transplanta(nohRemover, nohRemover->mDireito);
		} else if (nohRemover->mDireito == NULL) {
			Transplanta(nohRemover, nohRemover->mEsquerdo);
		} else {
			Noh* sucessor = Minimo(nohRemover->mDireito);
			
			if (sucessor->mPai != nohRemover) {
				Transplanta(sucessor, sucessor->mDireito);
				sucessor->mDireito = nohRemover->mDireito;
				sucessor->mDireito->mPai = sucessor;
			}
			
			Transplanta(nohRemover, sucessor);
			sucessor->mEsquerdo = nohRemover->mEsquerdo;
			sucessor->mEsquerdo->mPai = sucessor;
		}
		
		nohRemover->mEsquerdo = NULL;
		nohRemover->mDireito = NULL;
		delete nohRemover;
	}
}

void Arvore::EscreverOrdemAux(Noh* atual, int nivel) {
    if (atual != NULL) {
        EscreverOrdemAux(atual->mEsquerdo, nivel+1);
        cout << atual->mChave << "/" << nivel << " ";
        EscreverOrdemAux(atual->mDireito, nivel+1);
    }
}

void Arvore::EscreverPreOrdemAux(Noh* atual, int nivel) {
    if (atual != NULL) {
        cout << atual->mChave << "/" << nivel << " ";
        EscreverPreOrdemAux(atual->mEsquerdo, nivel+1);
        EscreverPreOrdemAux(atual->mDireito, nivel+1);
    }
}

void Arvore::EscreverOrdem() {
    EscreverOrdemAux(mRaiz, 0);
    cout << endl;
}

void Arvore::EscreverPreOrdem() {
    EscreverPreOrdemAux(mRaiz, 0);
    cout << endl;
}

bool Arvore::Vazia() {
    return mRaiz == NULL;
}

void Arvore::Transplanta(Noh* antigo, Noh* novo) {
    if (antigo == mRaiz) {
        mRaiz = novo;
    } else if (antigo->mPai->mEsquerdo == antigo) {
        antigo->mPai->mEsquerdo = novo;
    } else {
        antigo->mPai->mDireito = novo;
    }
    
    if (novo != NULL) {
        novo->mPai = antigo->mPai;
    }
}

Noh* Arvore::Minimo(Noh* raiz) {
    while (raiz->mEsquerdo != NULL) {
        raiz = raiz->mEsquerdo;
    }
    
    return raiz;
}

int main() {
    Arvore abb;
    char operacao;
    Tipo chave;
    
    do {
        cin >> operacao;
        switch (operacao) {
            case 'i': // Inserir
                cin >> chave;
                abb.Inserir(chave);
                break;
            case 'r': // Remover
                cin >> chave;
                if (abb.Buscar(chave) == NULL) {
                    cout << "ERRO" << endl;
                } else {
                    abb.Remover(chave);
                }
                break;
            case 'o': // Escrever tudo
                abb.EscreverOrdem();
                break;
            case 'p': // Escrever nivel a nivel
                abb.EscreverPreOrdem();
                break;
        }
    } while (operacao != 'f');
}
