#include <stdio.h>
#include <string.h>
#include <locale.h>
#define TAM 500

typedef struct arvore{ // defini��o da struct
	char letra; // char
	int freq;
	struct arvore *direita; // endere�o irm�os
	struct arvore *esquerda; // endere�o filhos
} arvore;
typedef struct alfa{ // cria estrutura da lista de indice
	char letra;// cria a letra
	int freq; // cria a frequencia de ocorrencia da letra
} alfa;

int cria_lista(alfa lista[],char letra, int n){ // insere letra na lista e acumula frequencia
	int i,status=0;
	for (i=0;i<n;i++){ // corre toda a lista
		if (letra==lista[i].letra){ // verifica se o caracter � igual a algum da lista
			status=1;// se for muda o status para 1
			lista[i].freq++; // acumula frequencia
		}
	}
	if (status==0){ // se status =0 ent�o letra n�o est� na lista
		lista[n].letra=letra;// inclui letra na lista
		lista[n].freq=1; // coloca frequencia =1 pois � primeira ocorrencoa
		n++;// incrementa tamanho da lista
	}
	return n; // retorna novo tamanho da lista
}
void imprime_lista(alfa lista[], int n){ // simplesmente imprime a lista
	int i;
	for(i=0;i<n;i++){
		printf("Letra %c - frequencia %d\n", lista[i].letra, lista[i].freq);
	}
}

void troca(alfa *a, alfa *b){ // fun��o de troca para facilitar codigo do bubble sort
	alfa aux; // cria variavel auxiliar
	aux=*a;// copia o conteudo de a em aux
	*a=*b; // copia o conteudo de b no endere�o de a
	*b=aux;// copia aux no endere�o de b
}
void organiza_lista(alfa lista[], int n){ // bubble sort para organizar a lista por frequencia
	int i,j;
	for (i=0;i<n-1;i++){// percorre a lista at� n-1
		for (j=i;j<n;j++){// percorre a lista a partir de i
			if (lista[i].freq<lista[j].freq){ // compara e se for maior troca
				troca(&lista[i],&lista[j]); // troca
			}
		}
	}
}
void organiza_arvore(arvore a[],alfa lista[], int n){ // bubble sort para organizar a lista por frequencia
	int  i,j;
	for (i=0;i<n-1;i++){// percorre a lista at� n-1
		for (j=i;j<n;j++){// percorre a lista a partir de i
			if (lista[i].freq<lista[j].freq){ // compara e se for maior troca
				troca(&lista[i],&lista[j]); // troca
			}
		}
	}
}
int recebe_texto(char frase[],alfa lista[]){ // recebe o texto em forma de string e copia ele para a lista
	int i=0; // inicializa contador
	int n=0; // inicializa variavel de contagem de itens da lista
	while(frase[i]!='\0'){ // enquanto a frase n�o chega no fim...
		n=cria_lista(lista,frase[i],n);	// envia cada caracter para a fun�ao cria lista e recebe de volta o numero de itens na lista
		i++; // icrementa contador
	}
	return n; // retorna o numero de itens da lista
}
void percorre_arvore(arvore *a, alfa lista[], int max ){ // fun��o para trasnferir todos os caracteres da lista para a arvore
	int i;
	for (i=0;i<max;i++){
		cria_arvore(a,lista,i);
	}
}
void cria_arvore(arvore *a[], alfa lista[], int i){ // em contru��o - contruido como vetor, parece que funcionou, 
	 						  	   					//todos os caracteres est�o alinhados a direita falta agora criar uma fun��o que junte 
	 						  	   					//os pares e altere a arvore
	if (*a==NULL) {
		*a = (arvore*)malloc(sizeof(arvore)); // aloca a memoria para a arvore
		(*(*a)).letra=lista[i].letra; //  copia a letra
		(*(*a)).freq=lista[i].freq; // copia a frequencia
		(*(*a)).direita=NULL; // define o endere�o da proxima a direita como NULL por ser folha
		(*(*a)).esquerda=NULL;
	}
	else {
		cria_arvore(&(*(*a)).direita, lista,i); // chama a recursividade a direita para formar a lista inicial
		}
}
void imprime(arvore *a,int n){ // fun�ao para imprimir a arvore como ela est�, recebe a lista e o numero de n�s
	int i;
	n++;
	if (a != NULL) {
      imprime (a->direita,n);
      for (i=0;i<n;i++){
      	printf(" ");
	  }
      printf("%c %d\n",(*a).letra,(*a).freq);
      imprime (a->esquerda,n); 
   }	
}

int main(){
	setlocale(LC_ALL, "Portuguese");
	int i=0,j;
	alfa lista[TAM]; // cria lista
	arvore *a; // cria arvore - duvida se cria como vetor estatico ou dinamico...
	char frase[TAM]="frase para testar a fun�ao de copiar os caracteres para o lista texto na outra linha pra verificar se o programa � capaz de lidar com essa quest�o funcionando perfeitamente";
	printf("%s\n",frase);// imprime a frase de teste
	i=recebe_texto(frase,lista);// transforma a string numa lista de letras e retorna o numero de letras
//	imprime_lista(lista,i);// imprime a lista para conferir o funcionamento
	organiza_lista(lista,i);// organiza a lista para testar
	printf("\n");// da um espa�o
	imprime_lista(lista,i);// imprime novamente para ver se organizou
	printf("Primeira vers�o da arvore\n");// separa��o para verificar se est� funcionando
	percorre_arvore(&a,lista,i);// envia a lista para cria��o das folhas da arvore
	imprime(&(a[0]),i);
	return 0;// retorna 0 para informar que n�o houve erro
}
