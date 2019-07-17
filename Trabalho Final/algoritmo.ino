/*
    Tabralho final da diciplina GCC216 (Estrutura de Dados)
    
    Um metodo para coleta de temperatura em arduino
    e salvamento dos dados em arquivo de texto
    utilizando as estruturas de arvore 2-3-4 e maxheap
    
    Copyright 2019 by:
        Emanuelle Herran Fabri da Silva
        Matheus Matias Lima

    constantes para verificação
        MAXITENS = 3
        MINITENS = 1
        MAXFILHOS = 4
        MEIO = 1 posição do meio (sobe em caso de estouro)
*/

#include <SD.h>

using namespace std;
typedef float Dado;

//função de troca 
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

// ******234******

class noh {
friend class arvore234;
private:
    bool folha;
    int num;
    Dado itens[3];
    noh* filhos[4];
public:
    noh();
    ~noh();
};

noh::noh() {
    num = 0;
    folha = false;
    for (int i = 0; i < 4; i++) {
        filhos[i] = NULL;
    }
}

noh::~noh() {
    for (int i = 0; i < num+1; i++) {
        delete filhos[i];
    }
}

class arvore234 {
private:
    noh* raiz;
    void percorreEmOrdemAux(noh* atual, File& dataFile, int nivel);   
    noh* insereAux(noh* umNoh, Dado umItem, Dado& itemPromovido);
    noh* divideNoh(noh* umNoh, Dado& itemPromovido);
    void insereEmNohFolhaNaoCheio(noh* umNoh, Dado umItem);
    void insereEmNohIntermediarioNaoCheio(noh* umNoh, noh* novoNoh, Dado itemPromovido);
public:
    arvore234() { raiz = NULL; }
    ~arvore234() { delete raiz; } 
    void insere(Dado umItem);
    void salvarEmArquivo();
};

void arvore234::insere(Dado umItem) {
    if (raiz == NULL) {
        raiz = new noh;
        raiz->folha = true;
        raiz->itens[0] = umItem;
        raiz->num = 1;
    } else {
        Dado itemPromovido; 
        noh* novoNoh;
        novoNoh = insereAux(raiz, umItem, itemPromovido);
        if (novoNoh) { 
            noh* antigaRaiz = raiz;
            raiz = new noh;
            raiz->itens[0] = itemPromovido;
            raiz->num = 1;
            raiz->filhos[0] = antigaRaiz;
            raiz->filhos[1] = novoNoh;
        }
    }
}

noh* arvore234::insereAux(noh* umNoh, Dado umItem, Dado& itemPromovido) {
    // Caso umNoh seja folha, encontre o local para inserir novo item
    if (umNoh->folha) {
        if (umNoh->num < 3) {
            insereEmNohFolhaNaoCheio(umNoh, umItem);
            return NULL;
        } 
        else { 
            noh* novoNoh; //para divisao do noh
            novoNoh = divideNoh(umNoh, itemPromovido);
            if (umItem <= umNoh->itens[1]) {
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
    else { // noh não é folha
        int i = umNoh->num-1; 
        while (i >= 0 && umNoh->itens[i] > umItem) { // Encontra filho que irá receber novo item
            i--;
        }
        noh* nohAux; 
        nohAux = insereAux(umNoh->filhos[i+1], umItem, itemPromovido);
        // verifica se não houve estouro no filho
        if (nohAux) { // se novoNoh não é nulo, houve divisão
            Dado itemAux = itemPromovido;
            if (umNoh->num < 3) { // verifica se não deve dividir o noh atual
                insereEmNohIntermediarioNaoCheio(umNoh, nohAux, itemAux);
                return NULL;
            }
            else { // umNoh está cheio, divide antes de arrumar estouro do filho
                noh* novoNoh;
                novoNoh = divideNoh(umNoh, itemPromovido);
                if (itemAux <= umNoh->itens[1]) {
                    insereEmNohIntermediarioNaoCheio(umNoh, nohAux, itemAux);
                }
                else { 
                    insereEmNohIntermediarioNaoCheio(novoNoh, nohAux, itemAux);
                }
                return novoNoh;
            }
        } 
    }
    return NULL;
}

noh* arvore234::divideNoh(noh* umNoh, Dado& itemPromovido) {
    itemPromovido = umNoh->itens[1];
    noh* novoNoh = new noh;
    novoNoh->folha = umNoh->folha;
    novoNoh->itens[0] = umNoh->itens[1+1];
    //noh com metade dos elementos
    novoNoh->num = 1;
    umNoh->num = 1;
    if (not umNoh->folha) {
        for (int i = 0; i < 1+1; i++) {
            novoNoh->filhos[i] = umNoh->filhos[1+1+i];
        }
    }
    return novoNoh;
}

void arvore234::insereEmNohFolhaNaoCheio(noh* umNoh, Dado umItem) {
    int pos = (umNoh->num - 1);
    while ((pos >= 0) and (umNoh->itens[pos] > umItem)) {
        umNoh->itens[pos+1] = umNoh->itens[pos];
        pos--;
    }
    umNoh->itens[pos+1] = umItem;
    umNoh->num++;
}

void arvore234::insereEmNohIntermediarioNaoCheio(noh* umNoh, noh* novoNoh, Dado itemPromovido) {
    int pos = (umNoh->num - 1);
    while ((pos >= 0) and (umNoh->itens[pos] > itemPromovido)) {
        umNoh->itens[pos+1] = umNoh->itens[pos];
        umNoh->filhos[pos+2] = umNoh->filhos[pos+1];
        pos--;
    }
    umNoh->itens[pos+1] = itemPromovido;
    umNoh->filhos[pos+2] = novoNoh;
    umNoh->num++;
}

void arvore234::salvarEmArquivo (){
  File dataFile = SD.open("data.txt", FILE_WRITE);
  if (dataFile) {
      percorreEmOrdemAux(raiz,dataFile,0);
  }
  dataFile.println();
  dataFile.println ("***Acabou de percorrer***");

  dataFile.close();
  
}

void arvore234::percorreEmOrdemAux(noh* umNoh,File& dataFile, int nivel) {
    int i;
    for (i = 0; i < umNoh->num; i++) {
        if (not umNoh->folha) {
            percorreEmOrdemAux(umNoh->filhos[i], dataFile, nivel+1);
        }
        dataFile.print(umNoh->itens[i]);
        Serial.print(umNoh->itens[i]);
        dataFile.print("/");
        Serial.print("/");
        dataFile.print(nivel);
        Serial.print(nivel);
        dataFile.print(" ");
        Serial.print(" ");
    }
     if (not umNoh->folha) {
        percorreEmOrdemAux(umNoh->filhos[i], dataFile, nivel+1);   
    }
}

int pinoDoSensor = 0;
int chipSelect = 10;

void setup() {
    Serial.begin(9600);
    pinMode(pinoDoSensor, INPUT);
    pinMode(chipSelect, OUTPUT);
    if (!SD.begin()) {
        Serial.println("Falha ao acessar o cartao!");
        return;
    }
    else {
        Serial.println("SD Card pronto para uso.");
    }
}

void loop() {
    arvore234 minhaArvore;
    MaxHeap meuHeap;
    float T; //temperatura
    float media = 0;

    for (int i=0; i < 6; i++) {
        //decodificando a temperatura
        T = (1.0 / (1.009249522e-03 + 2.378405444e-04*log(10000 * (1023.0/(float)analogRead(pinoDoSensor) - 1.0)) + 2.019202697e-07*log(10000 * (1023.0 / (float)analogRead(pinoDoSensor) - 1.0))*log(10000 * (1023.0 / (float)analogRead(pinoDoSensor) - 1.0))*log(10000 * (1023.0 / (float)analogRead(pinoDoSensor) - 1.0))));
        T = T - 273;
        Serial.println();
        Serial.print("Temperatura Coletada: ");
        Serial.print(T);
        Serial.println(" °C");
        meuHeap.Insere(T);
        delay(10000); //10 segundos
    }
    Serial.print("Maior: ");
    Serial.println(meuHeap.OlharRaiz());
    
    for (int i=0; i < 6; i++) {
        media += meuHeap.RetirarRaiz();
    }
    
    media = media/6;
    Serial.println();
    Serial.print("Media a ser inserida: ");
    Serial.print(media);
    Serial.println(" °C");
    Serial.println();
    minhaArvore.insere(media);
    minhaArvore.salvarEmArquivo();
}
