#include <iostream>

using namespace std;

// constantes para verificação
const int MAXITENS = 3;
const int MINITENS = 1;
const int MAXFILHOS = 4;

// posição do elemento do meio (o que sobe para página pai em caso de estouro
const int MEIO = 1; 

// tipo de dado armazenado
typedef int Dado;

class noh {
friend class bt234;
private:
    bool folha;
    int num; // número de itens armazenadas no nó
    Dado itens[MAXITENS];
    noh* filhos[MAXFILHOS];
public:
    noh();
    ~noh();
};

noh::noh() {
    num = 0;
    folha = false;
    for (int i = 0; i < MAXFILHOS; i++) {
        filhos[i] = NULL;
    }
}

noh::~noh() {
    for (int i = 0; i < num+1; i++) {
        delete filhos[i];
    }
}

class bt234 {
private:
    noh* raiz;
    void percorreEmOrdemAux(noh* atual, int nivel);   
    // funções auxiliares para encontrar menor e maior valor 
    // de uma subárvore com pai em raizSub
    Dado* minimoAux(noh* raizSub); 
    Dado* maximoAux(noh* raizSub);
    // função auxiliar para busca recursiva
    Dado* buscaAux(noh* raizSub, int chave);
    // funções auxiliares para inserção de um Dado d no noh umNoh
    noh* insereAux(noh* umNoh, Dado umItem, Dado& itemPromovido);
    noh* divideNoh(noh* umNoh, Dado& itemPromovido);
    void insereEmNohFolhaNaoCheio(noh* umNoh, Dado umItem);
    void insereEmNohIntermediarioNaoCheio(noh* umNoh, noh* novoNoh, Dado itemPromovido);
public:
    bt234() { raiz = NULL; }
    ~bt234() { delete raiz; } 
    void insere(Dado umItem);
    // remove um item com uma dada chave - NÃO IMPLEMENTADO AINDA
    void remove(int chave);
    // busca um item na árvore a partir da chave
    Dado* busca(int chave);
    // menor e maior valor da árvore
    Dado* minimo();
    Dado* maximo();
    // percorrimento (impressão)
    void percorreEmOrdem();
};

void bt234::insere(Dado umItem) {
    // se árvore estiver vazia, aloca nó folha para a raiz
    // e insere objeto na posição inicial
    if (raiz == NULL) {
        raiz = new noh;
        raiz->folha = true;
        raiz->itens[0] = umItem;
        raiz->num = 1;
    } else { // já tem algo na raiz
        // para receber item de filho que foi dividido
        Dado itemPromovido; 
        // nó gerado em caso de divisão
        noh* novoNoh;
        // chama método auxiliar recursivo
        novoNoh = insereAux(raiz, umItem, itemPromovido);
        // verifica se houve divisão na raiz
        if (novoNoh) { 
            // se novoNoh não é nula, houve divisão
            // cria nova raiz apontando com antiga raiz e novoNoh como filhos
            cout << "*** Divisao da Raiz ***" << endl;
            noh* antigaRaiz = raiz;
            raiz = new noh;
            raiz->itens[0] = itemPromovido;
            raiz->num = 1;
            raiz->filhos[0] = antigaRaiz;
            raiz->filhos[1] = novoNoh;
        }
    }
}

noh* bt234::insereAux(noh* umNoh, Dado umItem, Dado& itemPromovido) {
    // Caso umNoh seja folha, encontre o local para inserir novo item
    if (umNoh->folha) {
        // verificando se umNoh não está cheio        
        if (umNoh->num < MAXITENS) {
            // não está cheio, basta inserir
            insereEmNohFolhaNaoCheio(umNoh, umItem);
            return NULL;
        } 
        else { 
            // umNoh está cheio, precisa dividir
            noh* novoNoh;
            novoNoh = divideNoh(umNoh, itemPromovido);
            // verifica quem vai receber o item, se umNoh ou novoNoh
            if (umItem <= umNoh->itens[MEIO]) {
                // item fica em umNoh
                insereEmNohFolhaNaoCheio(umNoh, umItem);
            }
            else { 
                // item fica em novoNoh
                insereEmNohFolhaNaoCheio(novoNoh, umItem);
            }
            return novoNoh;
        }
    } 
    else { // nó não é folha
        // Encontra filho que irá receber novo item
        int i = umNoh->num-1;
        while (i >= 0 && umNoh->itens[i] > umItem) {
            i--;
        }
        noh* nohAux; 
        nohAux = insereAux(umNoh->filhos[i+1], umItem, itemPromovido);
        // verifica se não houve estouro no filho
        if (nohAux) { // se novoNoh não é nulo, houve divisão
            // antes de inserir o item promovido, 
            // verifica se não deve dividir o noh atual
            // para isso armazena itemPromovido em variável auxiliar
            Dado itemAux = itemPromovido;
            if (umNoh->num < MAXITENS) {
                // umNoh não está cheio, só arrumar o estouro do filho
                insereEmNohIntermediarioNaoCheio(umNoh, nohAux, itemAux);
                return NULL;
            }
            else {
                // umNoh está cheio, divide antes de arrumar estouro do filho
                noh* novoNoh;
                novoNoh = divideNoh(umNoh, itemPromovido);
                // verifica quem vai receber novo nó e item promovido, se umNoh ou novoNoh
                if (itemAux <= umNoh->itens[MEIO]) {
                    // nó e item ficam em umNoh
                    insereEmNohIntermediarioNaoCheio(umNoh, nohAux, itemAux);
                }
                else { 
                    // nó e item ficam em novoNoh
                    insereEmNohIntermediarioNaoCheio(novoNoh, nohAux, itemAux);
                }
                return novoNoh;
            }
        } // caso novoNoh seja nulo, não precisa fazer mais nada
    }
    return NULL; // apenas para evitar warning    
}

noh* bt234::divideNoh(noh* umNoh, Dado& itemPromovido) {
    cout << "** Divisao de noh **" << endl;
    itemPromovido = umNoh->itens[MEIO];
    noh* novoNoh = new noh;
    novoNoh->folha = umNoh->folha;
    novoNoh->itens[0] = umNoh->itens[MEIO+1];
    // agora cada nó tem metade dos elementos
    novoNoh->num = 1;
    umNoh->num = 1;
    // se nó não é folha, divide os filhos
    if (not umNoh->folha) {
        for (int i = 0; i < MEIO+1; i++) {
            novoNoh->filhos[i] = umNoh->filhos[MEIO+1+i];
        }
    }
    return novoNoh;
}

void bt234::insereEmNohFolhaNaoCheio(noh* umNoh, Dado umItem) {
    //editado
    int pos = (umNoh->num - 1);
    while ((pos >= 0) and (umNoh->itens[pos] > umItem)) {
        //movendo para inserir
        umNoh->itens[pos+1] = umNoh->itens[pos];
        pos--;
    }
    //inserindo
    umNoh->itens[pos+1] = umItem;
    umNoh->num++;
}

void bt234::insereEmNohIntermediarioNaoCheio(noh* umNoh, noh* novoNoh, Dado itemPromovido) {
    //editado
    int pos = (umNoh->num - 1);
    while ((pos >= 0) and (umNoh->itens[pos] > itemPromovido)) {
        //move pra direita
        umNoh->itens[pos+1] = umNoh->itens[pos];
        umNoh->filhos[pos+2] = umNoh->filhos[pos+1];
        pos--;
    }
    //insere o novo item no local encontrado
    umNoh->itens[pos+1] = itemPromovido;
    //insere o novo noh
    umNoh->filhos[pos+2] = novoNoh;
    umNoh->num++;
}

void bt234::percorreEmOrdem() {
    percorreEmOrdemAux(raiz,0);    
    cout<< endl;
}

void bt234::percorreEmOrdemAux(noh* umNoh, int nivel) {
    int i;
    for (i = 0; i < umNoh->num; i++) {
        // se nó não é folha, imprima os dados do filho i
        // antes de imprimir o item i
        if (not umNoh->folha) {
            percorreEmOrdemAux(umNoh->filhos[i], nivel+1); 
        }
        cout << umNoh->itens[i] << '/' << nivel << ' ';
    }
 
    // Imprima os dados do último filho
    if (not umNoh->folha) {
        percorreEmOrdemAux(umNoh->filhos[i], nivel+1);   
    }
}

Dado* bt234::minimo() {
    if (raiz == NULL) {
        cerr << "Arvore vazia!" << endl;
        return NULL;
        //exit(EXIT_FAILURE);
    } else {
        Dado* menorItem = minimoAux(raiz);
        return menorItem;
    }
}

Dado* bt234::minimoAux(noh* raizSub) {
    if (raizSub->folha) {
        // retorna primeiro elemento
        return &(raizSub->itens[0]);
    } else {
        // entra no primeiro filho (filho mais à esquerda)
        return minimoAux(raizSub->filhos[0]);
    }
}

Dado* bt234::maximo() {
    if (raiz == NULL) {
        cerr << "Arvore vazia!" << endl;
        return NULL;
        //exit(EXIT_FAILURE);
    } else {
        Dado* maiorItem = maximoAux(raiz);
        return maiorItem;
    }
}

Dado* bt234::maximoAux(noh* raizSub) {
    int pos = raizSub->num - 1;
    if (raizSub->folha) {
        // retorna último elemento
        return &(raizSub->itens[pos]);
    } else {
        // entra no último filho (filho mais à direita)
        return maximoAux(raizSub->filhos[pos+1]);
    }
}

Dado* bt234::busca(int chave) {
    if (raiz == NULL) {
        cerr << "Arvore vazia!" << endl;
        return NULL;
        //exit(EXIT_FAILURE);
    } else {
        Dado* itemBuscado = buscaAux(raiz,chave);
        return itemBuscado;
    }
}

Dado* bt234::buscaAux(noh* raizSub, int chave) {
    int i = 0;
    // percorre raizSub até achar um item com chave maior ou igual à procurada
    while ((i < raizSub->num) and (raizSub->itens[i] <= chave))
        i++;
    // retorna à posição anterior (desfazendo o último incremento)
    i--;
    // se é igual, terminou o serviço
    if (raizSub->itens[i] == chave) {
        return &(raizSub->itens[i]);
    }
    else {
        // se nó é folha, então não tem o elemento buscado
        if (raizSub->folha) {
            cout << "Elemento nao encontrado!" << endl;
            return NULL;
        } 
        // não é folha, desce em no filho à esquerda do item com chave maior que a procurada
        else {
            return buscaAux(raizSub->filhos[i+1],chave);
        }
    }
}


int main() {
    bt234* B = new bt234;
    int n;
    
    cin >> n;
    
    while (n >= 0) {
        cout << "=> inserindo " << n << endl;
        Dado d = n; 
        B->insere(d);
        B->percorreEmOrdem();
        cin >> n;
    }
    
    Dado* minimo;
    minimo = B->minimo();
    if (minimo) 
        cout << "#minimo: " << *minimo << endl;
    
    Dado* maximo;
    maximo = B->maximo();
    if (maximo) 
        cout << "#maximo: " << *maximo << endl;
    
    cin >> n;
    Dado* busca;
    busca = B->busca(n);
    cout << "#busca: ";
    if (busca) 
        cout << *busca << endl;
    else
        cout << -1 << endl;
    
    delete B;    
    return 0;
}
