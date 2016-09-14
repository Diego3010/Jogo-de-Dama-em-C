//Engenharia da Computacao
//Gustavo Donnangelo Cassettari e Diego de Moraes Aguiar

#include <stdio.h>
#include <string.h>
#define N 8

//prototipos

char **initialize();
void printmatriz (char **M);
void printposicoes (char **M);
int verificar_posicao (char **M, int lin, int col, int lind, int cold, char gamer);
int status(char **M);
int statusgamer(char **M, char gamer);

int main (void){

	char **M, gamer= 'B';
	int lin, col, lind, cold, jogoativo = -1;

 	M = initialize();
 	printposicoes(M);
 	
 	while(jogoativo==-1){
        printmatriz(M);
        printf("Caro jogador [%c] digite a linha da peça que deseja mover:",gamer);
        scanf("%d",&lin);
        printf("Caro jogador [%c] digite a coluna da peça que deseja mover:",gamer);
        scanf("%d",&col);
        printf("Caro jogador [%c] digite a linha para onde deseja mover:",gamer);
        scanf("%d",&lind);
        printf("Caro jogador [%c] digite a coluna para onde deseja mover:",gamer);
        scanf("%d",&cold);

        // se nao posso prosseguir
        if( verificar_posicao(M,lin, col, lind, cold, gamer) == -1){
            continue;
        }

        jogoativo = status(M);

        //alternancia de gamer
        if( gamer == 'P')
            gamer = 'B';
        else
            gamer = 'P';
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
int verificar_posicao (char **M, int lin, int col, int lind, int cold, char gamer){

    // P começa em cima e B em Baixo
    if((lin + col) % 2 == 0 || (lind + cold) % 2 == 0){
        printf("movimento invalido\n");
        return -1;
    }    

    if(gamer == 'P'){
        if(lin>lind){
            printf("movimento invalido");
            return -1;
        }
        else if(col!=cold + 1 || col!=cold - 1 || col!=cold + 2 || col!=cold - 2){
            printf("movimento invalido");
            return -1;
        }

    }
}

//verifica se continua ou para o jogo
int status(char **M){

    int i, j;
    //ele esta verificando apenas uma posicao
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            if(M[i][j]== ' ' || M[i][j]== 'P' && M[i][j]!= 'B' ){
                printf("As peças P ganharam\n");
                return 2;
            }
            if(M[i][j]== ' ' || M[i][j]== 'B' && M[i][j]!= 'P' ){
                printf("As peças B ganharam\n");
                return 3;
            }
            else
                return 1;
        }
    }

}

// verifica se ha um ganahdor
int statusgamer(char **M, char gamer){

	

}
