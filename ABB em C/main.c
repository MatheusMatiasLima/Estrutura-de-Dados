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
		printf("passou aqui");
}

//calcula o numero de nohs

int contarNos(no *raiz){
   if(raiz == NULL)
        return 0;
   else
        return 1 + contarNos(raiz->esq) + contarNos(raiz->dir);
}

int contarFolhas(no *raiz){
   if(raiz == NULL)
        return 0;
   if(raiz->esq == NULL && raiz->dir == NULL)
        return 1;
   return contarFolhas(raiz->esq) + contarFolhas(raiz->dir);
}

int contarNaoFolhas(no *raiz){
   if(raiz == NULL)
        return 0;
   if(raiz->esq != NULL || raiz->dir != NULL)
        return 1;
   return contarNaoFolhas(raiz->esq) + contarNaoFolhas(raiz->dir);
}

void numerosImapares(no *raiz){

    if(raiz == NULL){
        return;
    } else if(raiz != NULL) {
      numerosImapares(raiz->esq);
			if (raiz->numero % 2 != 0){
      	printf("%d \n",raiz->numero);
			}
      numerosImapares(raiz->dir);
    }
}


/*
Escreva uma função que conta o número de nós de uma árvore binaria de busca;

Escreva uma função que conta o número de nós folha de uma árvore binaria de busca;

Escreva uma função que conta o número de nós que não são folhas de uma árvore binaria de busca;

Escreva uma função para buscar os números impares em uma árvore não ordenada;
*/


int main()
{
	no *raiz = (no*)malloc(sizeof(no));
	raiz=NULL;

	int opc = 0, num;

	while(opc != 9)
	{
		printf("\n\n --- MENU --- ");
		printf("\n 1- Inserir ");
		printf("\n 2- Mostrar ");
		printf("\n 3- Menor/maior elemento");
		printf("\n 4- Mostrar em ordem decrescente");
		printf("\n 5- Numero de nos");
		printf("\n 6- Numero de folhas");
		printf("\n 7- Numero de não folhas");
		printf("\n 8- Numeros impares");
		printf("\n 9- Sair \n -> ");
		scanf("%i",&opc);
		if(opc == 1)
		{
			printf("\n Digite o numero a ser inserido: ");
			scanf("%i",&num);
			raiz = inserir(raiz,num);
			//raiz=inserir(NULL,6);
			//raiz=inserir(1010,3);
			//raiz=inserir(1010,8);
			//raiz=inserir(1010,7);
		}
		if(opc == 2)
		{
		   mostrar(raiz);
		}
		if(opc == 3)
		{
			menorElemento(raiz);
			maiorElemento(raiz);
		}
		if(opc == 4)
		{
			mostrarEmOrdemDecrescente(raiz);
		}

		if (opc == 5) {
			printf("O numero de nos é: %d\n",contarNos(raiz));
		}

		if (opc == 6) {
			printf("O numero de folhas é: %d\n", contarFolhas(raiz));
		}

		if (opc == 7) {
			printf("O numero de não folhas é: %d\n", contarNaoFolhas(raiz));
		}

		if (opc == 8) {
			printf("Os numeros impares são: ");
			numerosImapares(raiz);
		}

	}
	return(0);
}
