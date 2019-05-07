#include <stdio.h>
#include <string.h>
#include <locale.h>
#define TAM 500

typedef struct arvore{ // definição da struct
	char letra; // char
	int freq;
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
int recebe_texto(char frase[],alfa lista[]){
	int i=0;
	int n=0;
	while(frase[i]!='\0'){
		n=cria_lista(lista,frase[i],n);	
		i++;
	}
	return n;
}


int main(){
	setlocale(LC_ALL, "Portuguese");
	int i=0;
	alfa lista[TAM]; // cria lista
	arvore *a[TAM];
	char frase[TAM]="frase para testar a funçao de copiar os caracteres para o lista\ntexto na outra linha pra verificar se o programa é capaz de lidar com essa questão\nfuncionando perfeitamente";
	printf("%s\n",frase);
	i=recebe_texto(frase,lista);// transforma a string numa lista de letras e retorna o numero de letras
//	imprime_lista(lista,i);// imprime a lista para conferir o funcionamento
	organiza_lista(lista,i);// organiza a lista para testar
	printf("\n");// da um espaço
	imprime_lista(lista,i);// imprime novamente para ver se organizou
	return 0;// retorna 0 para informar que não houve erro
}
