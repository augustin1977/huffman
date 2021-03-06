#include <stdio.h>
#include <string.h>
#include <locale.h>
#define TAM 500

#define typeof(var) _Generic(char: "Char",int: "Integer",float: "Float",char *: "String",void *: "Pointer",default: "Undefined")

typedef struct arvore{ // definição da struct
	char letra; // char
	int freq;
	struct arvore *prox;
	struct arvore *direita; // endereço irmãos
	struct arvore *esquerda; // endereço filhos
} arvore;
typedef struct alfa{ // cria estrutura da lista de indice
	char letra;// cria a letra
	int freq; // cria a frequencia de ocorrencia da letra
} alfa;

int cria_lista(alfa lista[],char letra, int n){ // insere letra na lista e acumula frequencia
	int i,status=0;
	for (i=0;i<n;i++){ // corre toda a lista
		if (letra==lista[i].letra){ // verifica se o caracter é igual a algum da lista
			status=1;// se for muda o status para 1
			lista[i].freq++; // acumula frequencia
		}
	}
	if (status==0){ // se status =0 então letra não está na lista
		lista[n].letra=letra;// inclui letra na lista
		lista[n].freq=1; // coloca frequencia =1 pois é primeira ocorrencoa
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

void troca(alfa *a, alfa *b){ // função de troca para facilitar codigo do bubble sort
	alfa aux; // cria variavel auxiliar
	aux=*a;// copia o conteudo de a em aux
	*a=*b; // copia o conteudo de b no endereço de a
	*b=aux;// copia aux no endereço de b
}
void organiza_lista(alfa lista[], int n){ // bubble sort para organizar a lista por frequencia
	int i,j;
	for (i=0;i<n-1;i++){// percorre a lista até n-1
		for (j=i;j<n;j++){// percorre a lista a partir de i
			if (lista[i].freq>lista[j].freq){ // compara e se for maior troca
				troca(&lista[i],&lista[j]); // troca
			}
		}
	}
}

int recebe_texto(char frase[],alfa lista[]){ // recebe o texto em forma de string e copia ele para a lista
	int i=0; // inicializa contador
	int n=0; // inicializa variavel de contagem de itens da lista
	while(frase[i]!='\0'){ // enquanto a frase não chega no fim...
		n=cria_lista(lista,frase[i],n);	// envia cada caracter para a funçao cria lista e recebe de volta o numero de itens na lista
		i++; // icrementa contador
	}
	return n; // retorna o numero de itens da lista
}

void cria_arvore(arvore **a, alfa lista[], int i){ // em contrução - contruido como vetor, parece que funcionou, 
	 						  	   					//todos os caracteres estão alinhados a direita falta agora criar uma função que junte 
	 						  	   					//os pares e altere a arvore
	if (*a==NULL) {
		*a = (arvore*)malloc(sizeof(arvore)); // aloca a memoria para a arvore
		(*(*a)).letra=lista[i].letra; //  copia a letra
		(*(*a)).freq=lista[i].freq; // copia a frequencia
		(*(*a)).prox=NULL;
		(*(*a)).direita=NULL; // define o endereço da proxima a direita como NULL por ser folha
		(*(*a)).esquerda=NULL;
	}
	else {
		cria_arvore(&(*(*a)).prox, lista,i); // chama a recursividade a proximo para formar a lista inicial
		}

}

void dobra_arvore(arvore **a, alfa lista[], int i){
	 arvore *aux1,*aux2;
	 
  	 aux1=*a;
  	 aux2=((*(*a))).prox;
  	 //aux2=((*aux2)).prox;
  	 printf("aux1=%c %d \n",&(*aux2).letra,(*aux2).freq);
  	 printf("aux2=%c %d \n",&(*aux1).letra,(*aux1).freq);
	 //aux2=&a->prox;
	 printf("----------\n");	
	 //printf("%p",&(*aux2).direita);
	 //printf("passei\n");
	 *a = (arvore*)malloc(sizeof(arvore));
	 (*(*a)).direita=*&(aux1->prox);
	 (*(*a)).esquerda=*&(aux2->prox);
	 (*(*a)).freq=*&(*aux1).freq+*&(*aux2).freq;
	 (*(*a)).prox=aux2;
	 aux1->prox=NULL;
	 aux1->prox=NULL;
	 printf("%c %c %d\n", (*(*(*a)).esquerda).letra,(*(*(*a)).direita).letra,(*(*a)).freq);
	 //(*(*a)).freq=aux2->freq+aux1->freq;
}

void imprime(arvore **a,int n){ // funçao para imprimir a arvore como ela está, recebe a lista e o numero de nós
	int i; // contador para definir o nivel de impressão
	if (*a != NULL) { // verifica se terminou a arvore
      imprime (&(*(*a)).prox,n);// chama a recursão do proximo
      if (&(*(*a)).esquerda!=NULL) {
        imprime (&(*(*a)).esquerda,n);// chama a recursão do esquerda 
	  }
      printf("%c %d\n",(*(*a)).letra,(*(*a)).freq); // imprime a letra e a frequencia
	  	  if (&(*(*a)).direita!=NULL) {
		  imprime (&(*(*a)).direita,n); // chama a recursão a esquerda
		  }
   }	
}

int main(){
	setlocale(LC_ALL, "Portuguese");
	int i=0,j;
	alfa lista[TAM]; // cria lista
	arvore *a=NULL; // cria arvore - duvida se cria como vetor estatico ou dinamico...
	//char frase[TAM]="frase para testar a funçao de copiar os caracteres para o lista texto na outra linha pra verificar se o programa é capaz de lidar com essa questão funcionando perfeitamente";
	char frase[TAM]="aabbcccdedefgagaabb";
	printf("%s\n",frase);// imprime a frase de teste
	i=recebe_texto(frase,lista);// transforma a string numa lista de letras e retorna o numero de letras
//	imprime_lista(lista,i);// imprime a lista para conferir o funcionamento
	organiza_lista(lista,i);// organiza a lista para testar
	printf("\n");// da um espaço
	imprime_lista(lista,i);// imprime novamente para ver se organizou
	printf("Primeira versão da arvore\n");// separação para verificar se está funcionando
	
	for (j=0;j<i;j++){
		printf("%d\n",j);
		cria_arvore(&a,lista,j);// envia a lista para criação das folhas da arvore
	}
	imprime(&a,i);
	dobra_arvore(&a,lista,i);
	printf("Imprimindo arvore\n");
	imprime(&a,i);
	return 0;// retorna 0 para informar que não houve erro
}
