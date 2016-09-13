//Engenharia da Computacao
//Gustavo Donnangelo Cassettari e Diego de Moraes Aguiar

#include <stdio.h>
#include <string.h>
#define N 8

//prototipos

char **initialize();
void printmatriz (char **M);
void printposicoes (char **M);
int verificar_posicao (char **M, int lin, int col, char gamer);
int status(char **M);
int statusgamer(char **M, char gamer);

int main (void){

	char **M, gamer= 'B';
	int lin, col, jogoativo;

 	M = initialize();
 	printposicoes(M);
 	printmatriz(M);

 	while(jogoativo==-1){
        printmatriz(M);
        printf("Caro jogador [%c] digite a linha:",gamer);
        scanf("%d",&lin);
        printf("Caro jogador [%c] digite a coluna:",gamer);
        scanf("%d",&col);

        // se nao posso prosseguir
        if( !step(M,lin, col, gamer) ){
            printf("\njogada invalida !\n");
            continue;
        }

        jogoativo = status(tabuleiro);

        //alternancia de gamer
        if( gamer == 'P')
            gamer = 'B';
        else
            gamer = 'P';
    }
}

	return 0;
}

//funcoes

//alocar posicoes
char **initialize() {
    char **M;
    int i,j;

    M = (char **) calloc (N, sizeof (char *));
    for (i = 0;i<N;i++)
        M[i]=(char *)calloc(N, sizeof(char));

    for(i=0;i<N;i++)
        for(j=0;j<N;j++)
            M[i][j]=' ';//espaco em branco

    return M;
}

//printar posicoes iniciais das pecas

void printposicoes (char **M){

	int i, j;
	for(i=0; i<3; i++){
		if(i%2==0)
			j=1;
		else
			j=0;
		while(j<8){
			M[i][j] = 'P';
			j += 2;
		}
	}
	for(i=5; i<8; i++){
		if(i%2==0)
			j=1;
		else
			j=0;
		while(j<8){
			M[i][j] = 'B';
			j += 2;
		}
	}

}

//printa a matriz
void printmatriz (char **M){

	int i,j;
	printf(" ");
    for(i=0;i<N;i++){
    	printf("  %d", i);
    }
    printf("\n");
    for(i=0;i<N;i++){
        printf("%d ", i);
        for(j=0;j<N;j++){
            printf("[%c]",M[i][j]);
        }
        printf("\n");

    }

}

//verifica se pode jogar naquela posicao
int verificar_posicao (char **M, int lin, int col, char gamer){



}

//verifica se continua ou para o jogo
int status(char **M){



}

// verifica se ha um ganahdor
int statusgamer(char **M, char gamer){

	int i;
    for(i=0;i<N;i++){
        // verifica na linha
        if(M[i][0]==gamer && M[i][1]==gamer && M[i][2]==gamer)
            return 1;
        // verica coluna
        if(M[0][i]==gamer && M[1][i]==gamer && M[2][i]==gamer)
            return 1;
    }
    // diagonal principal
    if(M[0][0]==gamer && M[1][1]==gamer && M[2][2]==gamer)
        return 1;

    // diagonal secundaria
    if(M[0][2]==gamer && M[1][1]==gamer && M[2][0]==gamer)
        return 1;
    return 0;

}
