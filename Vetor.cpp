typedef float tipo;

//funcao de troca
void swap (tipo& a, tipo& b) {
    tipo aux = a;
    a = b;
    b = aux;
}

class dados {
    friend class vetor;
    private:
        tipo temperatura; //chave 1
        tipo umidade; //chave 2
    public:
        //contrutor
        dados (tipo t, tipo u) {
            umidade = u;
            temperatura = t;
        }
        //como as variaveis nao sao alocadas dinamicamente, nao precisa do destrutor
};

class vetor {
         //para acessar os atributos privados
    private:
        dados** vetDados; //vetor para ponteiro de dados. Possui umidade e temperatura em cada posicao
        int capacidade; // para guardar o tamanho total do vetor
        int tamanho; // para guardar o tanto de vetor
    public:
        vetor (); //construtor. Passa a capacidade por parametro, se nao passar o tamanho, recebe 5 por padrao
        ~vetor(); //destrutor

        //declarando metodos
        void insereOrdenando(tipo t, tipo u); //insere um novo dado no vetor e ordena
        void realocar(); //adiciona mais espaco no vetDados
        void percorre(); // percorre todo o vetor imprimindo
};

vetor::vetor () {
    vetDados = new dados* [5]; //alocando espaço inicial
    capacidade = 5;
    tamanho = 0;
}

vetor::~vetor () {
    delete[] vetDados; //foi alocada dinamicamente 
}

void vetor::insereOrdenando(tipo t, tipo u) {
    //se cheio precisa realocar
    if (tamanho >= capacidade)  
        realocar();

    //inserindo na ultima posicao
    vetDados[tamanho] = new dados (t,u); //chamou o construtor de dados para criar

    int i = tamanho;
    //achando seu lugar na ordem crescente ordenando pela chave 1 (temperatura)
    while ((i > 0) and (vetDados[i]->temperatura < vetDados[i-1]->temperatura)) {
        swap(vetDados[i]->temperatura, vetDados[i-1]->temperatura);
        swap(vetDados[i]->umidade, vetDados[i-1]->umidade);
        i--;
    }
    tamanho++;
}

void vetor::realocar() {
    //cria um aux pra copiar os dados
    dados** aux = new dados* [capacidade+5];
    //copiando...
    for (int i=0; i < tamanho; i++) {
        aux[i] = new dados (vetDados[i]->temperatura,vetDados[i]->umidade);
    }
    //deletando o antigo
    delete[] vetDados;
    //realocando vetDados
    vetDados = new dados* [capacidade+5];
    //vetDados agora é aux
    vetDados = aux;
    //incrementando a capacidade, poderia ter feito primeiro tambem
    capacidade += 5;
}

//funcao de percorrer, nao coloquei para imprimir umidade porque eu usei pra debugar
void vetor::percorre () {
    for (int i = 0; i < tamanho; i++) {
        //#escrever (vetDados[i]->temperatura) 
        //#escrever ( )
    }
    //# escrever (quebraDeLinha)
}

/*
    exemplo de como usar:
    
    // chama construtor de vetor e constroi um vetor de tamanho 5
    vetor meuVetor 

    //chama o metodo da variavel meuVetor para inserir os valores passados por parametro
    //esses valores voce vai colecar com a entrada analogica do arduino
    meuVetor.insereOrdenando(temperatura,umidade) 

    chama o metodo de percorrer
    meuVetor.percorre() 

*/

/* USEI SO PRO G++ COMPILAR
int main () {
    return 0;
}
*/