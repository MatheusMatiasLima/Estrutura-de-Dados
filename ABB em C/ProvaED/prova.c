#include<stdio.h>
#include<stdlib.h>
typedef struct no
{
	int numero;
	struct no *dir;
	struct no *esq;
}no;

  // *inserir(1010,7)
     //*inserir(2020,7)
       //*inserir(3030,7)
no *inserir(no *raiz,int num){
   if(raiz == NULL)
   {
      no *novo = (no*)malloc(sizeof(no));

      novo->numero = num;
      novo->dir = NULL;
      novo->esq = NULL;
	  raiz = novo;
   }else{
   	  if(num == raiz->numero)
	  {
		 printf("\n O numero ja foi inserido!");
      }
      if(num > raiz->numero)//verifica se entra a direita
	  {
	     raiz->dir = inserir(raiz->dir,num);
	  }
	  if(num < raiz->numero)//verifica se entra a esquerda
	  {
	  	 raiz->esq = inserir(raiz->esq,num);
	  }
   }
   return(raiz);
}

void mostrar(no *mt){

   if(mt != NULL)
   {
   	   mostrar(mt->esq);
   	   printf("\n %i", mt->numero);
   	   mostrar(mt->dir);
   }
}


void menorElemento(no *menor){
   if(menor != NULL)
   {
   	  if(menor->esq == NULL)
   	  {
   	     printf("\n Elemento menor: %i",menor->numero);
   	  }
	  menorElemento(menor->esq);
   }
}

void maiorElemento(no *maior){
   if(maior != NULL)
   {
   	  if(maior->dir == NULL)
   	  {
   	     printf("\n Elemento maior: %i",maior->numero);
   	  }
	  maiorElemento(maior->dir);
   }
}


void mostrarEmOrdemDecrescente(no *mt){
   if(mt != NULL)
   {
   	   mostrarEmOrdemDecrescente(mt->dir);
   	   printf("\n %i", mt->numero);
   	   mostrarEmOrdemDecrescente(mt->esq);
   }
}



//======================================================

void insere_arvore(no *raiz,int valor){

   //cria um novo no
   no *novo =(no*)malloc(sizeof(no));
   no *atual=(no*)malloc(sizeof(no));
   no *ant  =(no*)malloc(sizeof(no));

   novo->numero=valor;
   novo->dir =NULL;
   novo->esq =NULL;

    if(raiz == NULL){ //se for a primeira vez entra no caso especial
      raiz=novo;
    }else{

        atual=raiz;
        ant=NULL;

        //enquanto n�o chegar no n� folha
        while(atual!=NULL){
                ant=atual;

                //valor maior que a raiz
                if(valor > atual->numero){
                    atual=atual->dir;

                //valor menor que a raiz
                }else{
                    atual=atual->esq;
                }
         }

            //insere como filho desse no folha
            if(valor > ant->numero){
                ant->dir = novo;
            }else{
                ant->esq = novo;
            }
            return;
       }
}


//==============================================================
//raiz esquerda direita
void pre_ordem(no *raiz){

    if(raiz == NULL){

        //printf("\n NULL");
        //"return" sem valor, simplesmente retorna o controle
        //para a fun��o que chamou a fun��o corrente.
        //Nenhum valor de retorno � passado, ou seja,
        //o valor de retorno � indefinido.
        return;

    }else if(raiz != NULL){

         printf("%d \n ",raiz->numero);
         pre_ordem(raiz->esq);
         pre_ordem(raiz->dir);

    }
}



//esquerda raiz direita
void em_ordem(no *raiz){

    if(raiz == NULL){
        return;
    }else if(raiz != NULL){

      em_ordem(raiz->esq);
      printf("%d \n",raiz->numero);
      em_ordem(raiz->dir);
    }
}


void pos_ordem(no *raiz){

    if(raiz ==NULL){
        return;
    }else if(raiz != NULL){

     pos_ordem(raiz->esq);
     pos_ordem(raiz->dir);
     printf("%d \n",raiz->numero);

    }
}

int contarNos(no *raiz){
   if(raiz == NULL)
        return 0;
   else
        return 1 + contarNos(raiz->esq) + contarNos(raiz->dir);
}

// *********** PROVA *************

//questao 1
int maiorQuantidade (no *raiz) {
   if (raiz == NULL) { //evitar erros, arvore vazia retorna 0
      return 0;
   }
   else {
      int direito = contarNos(raiz->dir);
      int esquerdo = contarNos(raiz->esq);

      //se os dois lados tiverem a mesma quantidade
      if (direito == esquerdo) {
         return 1;
      }
      //se o lado direito mais pesado retorna 2
      else if (direito > esquerdo) {
         return 2;
      }
      //se o lado esquerdo mais pesado retorna 3
      else{
         return 3;
      }
   }
}


//questao 2

void percorrer (no *A, no *B) {
   if(A == NULL){
         return;
   }

   else{
         percorrer(A->esq, B);

         no* atual = B;
         int achou = -1;

         while (atual != NULL)  {
            if (atual->numero == A->numero) {
               achou = 1;
            }

            if ( (atual->numero) > (A->numero)) {
               atual = atual->esq;
            }
            else {
               atual = atual->dir;
            }
         }
         if (achou == -1) {
            printf("%d ",A->numero);
         }
		}

			percorrer(A->dir, B);
    }




void compararValores (no *A, no *B) {
   printf("\n valores que estao na arvore A e nao estao na arvore B: ");
	 no *raizA = A;
	 no*raizB = B;
   percorrer(raizA,raizB);
   printf("\n valores que estao na arvore A e nao estao na arvore B: ");

   percorrer(raizB,raizA);
}

//questao 3
int igual(no *raiz, no *raiz2){

    if (( (raiz) == NULL) != ( (raiz2) == NULL) )
       return 0;
    if (raiz == raiz2)
       return 1;
    if (raiz->numero != raiz2->numero)
       return 0;
    if (!igual(&(raiz->esq), &(raiz2->esq)))
        return 0;
    if (!igual(&(raiz->dir), &(raiz2->dir)))
        return 0;

    return 1;
}



int main() {
	no *raiz = (no*)malloc(sizeof(no));
	raiz=NULL;
   no *raiz2 = (no*)malloc(sizeof(no));
   raiz2 = NULL;

	int opc = 0, num;
   //inserção arvore 1
   raiz = inserir(raiz,45);
   raiz = inserir(raiz,20);
   raiz = inserir(raiz,58);
   raiz = inserir(raiz,19);
   raiz = inserir(raiz,21);
   raiz = inserir(raiz,71);

   //inserção arvore 2
   raiz2 = inserir(raiz2,45);
   raiz2 = inserir(raiz2,20);
   raiz2 = inserir(raiz2,58);
   raiz2 = inserir(raiz2,19);
   raiz2 = inserir(raiz2,21);
   raiz2 = inserir(raiz2,70);

   while(opc != 9) {
		printf("\n\n --- MENU --- ");
		printf("\n 1- Inserir ");
		printf("\n 2- Mostrar ");
		printf("\n 3- Menor/maior elemento");
		printf("\n 4- Mostrar em ordem decrescente");
		printf("\n 5- Numero de nos");
		printf("\n 6- Calcular peso");
		printf("\n 7- Comparar valores");
      printf("\n 8- Iguais");
		//printf("\n 8- Numeros impares");
		//printf("\n 9- Sair \n -> ");
		printf("\n\nQual opcao: ");
		scanf("%i",&opc);
		printf("\n");
   if(opc == 1) {
			printf("\n Digite o numero a ser inserido: ");
			scanf("%i",&num);
			raiz = inserir(raiz,num);
   }
	if(opc == 2) {
      printf("\n Arvore 1: ");
      mostrar(raiz);
      printf("\n Arvore 2: ");
      mostrar(raiz2);
   }
		if(opc == 3) {
			menorElemento(raiz);
			maiorElemento(raiz);
      }
		if(opc == 4) {
			mostrarEmOrdemDecrescente(raiz);
		}

		if (opc == 5) {
			printf("O numero de nos é: %d\n",contarNos(raiz));
      }
      if (opc == 6) {
         int dado = maiorQuantidade(raiz);

         if (dado > 0) {
            if (dado == 1) {
               printf("Os dois lados tem o mesmo tamanho");
            }
            else if (dado == 2) {
               printf ("O lado direito tem mais nos");
            }
            else if (dado == 3) {
               printf ("O lado esquerdo tem mais nos");
            }
         }
         else {
            printf("Arvore Vazia");
         }

      }
      if (opc == 7) {
         compararValores(raiz,raiz2);
      }
      if (opc == 8) {
         if( igual(raiz,raiz2) == 1 ) {
            printf("Arvores iguais");
         }
         else {
            printf("Arvores diferentes");
         }
      }
   }
	return(0);
}
