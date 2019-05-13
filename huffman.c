#i#include <stdio.h>
#include <string.h>
#include <locale.h>
#define TAM 500
#define k 50

#define typeof(var) _Generic(char: "Char",int: "Integer",float: "Float",char *: "String",void *: "Pointer",default: "Undefined")

typedef struct arvore{ // definição da struct
	char letra; // char
	int freq;
	struct arvore *prox;
	struct arvore *direita; // endereço irmãos
	struct arvore *esquerda; // endereço filhos
} arvore;
//typedef struct alfa{ // cria estrutura da lista de indice
//	char letra;// cria a letra
//	int freq; // cria a frequencia de ocorrencia da letra
//} alfa;

int cria_lista(arvore lista[],char letra, int n){ // insere letra na lista e acumula frequencia
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

void imprime_lista(arvore lista[], int n){ // simplesmente imprime a lista
	int i;
	for(i=0;i<n;i++){
		printf("Letra %c - frequencia %d\n", lista[i].letra, lista[i].freq);
	}
}

void troca(arvore *a, arvore *b){ // função de troca para facilitar codigo do bubble sort
	arvore aux; // cria variavel auxiliar
	aux=*a;// copia o conteudo de a em aux
	*a=*b; // copia o conteudo de b no endereço de a
	*b=aux;// copia aux no endereço de b
}
void organiza_lista(arvore lista[], int n){ // bubble sort para organizar a lista por frequencia
	int i,j;
	for (i=0;i<n-1;i++){// percorre a lista até n-1
		for (j=i;j<n;j++){// percorre a lista a partir de i
			if (lista[i].freq>=lista[j].freq){ // compara e se for maior troca
				troca(&lista[i],&lista[j]); // troca
			}
		}
	}
	for (i=0;i<n-1;i++){
		lista[i].prox=&lista[i+1];
	}
	
}

int recebe_texto(char frase[],arvore lista[]){ // recebe o texto em forma de string e copia ele para a lista
	int i=0; // inicializa contador
	int n=0; // inicializa variavel de contagem de itens da lista
	while(frase[i]!='\0'){ // enquanto a frase não chega no fim...
		n=cria_lista(lista,frase[i],n);	// envia cada caracter para a funçao cria lista e recebe de volta o numero de itens na lista
		i++; // icrementa contador
	}
	return n; // retorna o numero de itens da lista
}

int dobra_arvore(arvore a[], int n){
	 char aux=a[k].letra;
	 int i,j=k;
  	 for (j=k;a[j].letra!='@';j++){
  	 	//printf("A[%d].letra=%c\n",j,a[j].letra);
	   };
  	 a[j]=a[0];
  	 a[j+1]=a[1];
  	 a[j+2].letra='@';
  	 
  	 
  	 for (i=0;i<n-2;i++){
  	 	a[i]=a[i+2];
  	 	a[i].prox=&a[i+1];
  	 	//printf("%c\n",a[i].letra);
	   }
	 //a[n-1].prox=NULL;  
  	 a[n-2].letra ='@'; 
	 a[n-2].direita=&a[j];
	 a[n-2].esquerda=&a[j+1];
	 a[n-2].freq=a[j].freq+a[j+1].freq;
	 a[n-3].prox=NULL;
	 return (n-1);
}

void imprime(arvore *a,int n){ // funçao para imprimir a arvore como ela está, recebe a lista e o numero de nós
	int i=0,j=k; // contador para definir o nivel de impressão
	while(i<n){ // Repete ate encontrar o ultimo endreço (end == NULL)
		 printf("Nó - %c %d n=%d aponta direita %p e esquerda %p\n",a[i].letra, a[i].freq ,i,a[i].direita,a[i].esquerda);
		 while (a[i].letra=='@' && a[j].letra!='\0'){
		 	printf("sub-arvore %p %c %d n=%d\n",&a[j],a[j].letra, a[j].freq ,j);
		 	j++;
		 }
		 i++;
	}
	
}

int main(){
	setlocale(LC_ALL, "Portuguese");
	int i=0,j;
	arvore a[TAM]; // cria arvore - duvida se cria como vetor estatico ou dinamico...
	a[k].letra='@';
	//char frase[TAM]="frase para testar a funçao de copiar os caracteres para o lista texto na outra linha pra verificar se o programa é capaz de lidar com essa questão funcionando perfeitamente";
	char frase[TAM]="aabbbccddeefg";
	printf("%s\n",frase);// imprime a frase de teste
	i=recebe_texto(frase,a);// transforma a string numa lista de letras e retorna o numero de letras
	organiza_lista(a,i);// organiza a lista para testar
	printf("\n");// da um espaço
	imprime_lista(a,i);// imprime novamente para ver se organizou
	printf("Primeira versão da arvore\n");// separação para verificar se está funcionando
	imprime(&a[0],i);
	while(i>1){
	i=dobra_arvore(a,i);
	organiza_lista(a,i);// organiza a lista para testar	
	printf("Imprimindo arvore\n");
	imprime(&a[0],i);
	}
	printf("Arvore Final\n");
	imprime(&a[0],i);
	return 0;// retorna 0 para informar que não houve erro
}
