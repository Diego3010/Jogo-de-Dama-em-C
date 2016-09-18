//Engenharia da Computacao
//Gustavo Donnangelo Cassettari e Diego de Moraes Aguiar

#include <stdio.h>
#include <string.h>
#define N 8

//prototipos das funçoes

char **initialize();
void printmatriz (char **M);
void printposicoes (char **M);
int step (char **M, int lin, int col, int lind, int cold, char gamer);
int status(char **M);
int statusgamer(char **M, char gamer);

int main (void){

	system("color f0");
	char **M, gamer= 'B';
	int lin, col, lind, cold, jogoativo = -1;

 	M = initialize();
 	printposicoes(M);

    //loop do programa
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
        printf("\n\n\n");

        //condiçao do movimento dentro da matriz
        if(lin < 0 || lin > 7 || lind < 0 || lind > 7 || col < 0 || col > 7 || cold < 0 || cold > 7){
            printf("movimento invalido\n");
            continue;
        }

        // se nao pode prosseguir
        if( step(M,lin, col, lind, cold, gamer) == 1){
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

//funcoes:

//alocar posicoes
char **initialize() {
    char **M;
    int i,j;

    M = (char **) calloc (N, sizeof (char *));
    for (i = 0;i<N;i++)
        M[i]=(char *)calloc(N, sizeof(char));

    for(i=0;i<N;i++)
        for(j=0;j<N;j++)
            M[i][j]=' ';

    return M;
}

//colocar posicoes iniciais das pecas
void printposicoes (char **M){

	int i, j;

	for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            M[i][j] = 178;
        }
	}
	for(i=3;i<4;i++){
        for(j=0;j<8;j+=2){
            M[i][j] = ' ';
        }
	}
	for(i=4;i<5;i++){
        for(j=1;j<8;j+=2){
            M[i][j] = ' ';
        }
	}

//	M[5][0] = 'B';
//	M[4][1] = 'P';

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

//gera o tabuleiro com as peças
void printmatriz (char **M){

	int i,j;
	printf("  ");
    for(i=0;i<N;i++){
    	printf("   %d", i);
    }
    printf("\n\n");
    for(i=0;i<N;i++){
        printf(" %d ", i);
        for(j=0;j<N;j++){
            printf("  %c ",M[i][j]);
        }
        printf("\n\n");

    }

}

//verifica se pode jogar naquela posicao e movimentação
int step (char **M, int lin, int col, int lind, int cold, char gamer){

    char oposto;
    int i;

    //definição do rival
    if(gamer == 'B')
        oposto = 'P';
    else
        oposto = 'B';

    // P começa em cima e B em Baixo

    //condição de posiveis locais de peças


    if (M[lin][col] == ' '){
            printf ("Nao pode mover casas vazias\n");
            return 1;
    }



    if((lin + col) % 2 == 0 || (lind + cold) % 2 == 0){
        printf("movimento invalido\n");
        return 1;
    }

    //gambiarra
    if(M[lin][col] == 3 || M[lin][col] == 5){

    }
    else if(gamer == 'P'){
            if(lin>lind){
                printf("movimento invalido\n");
                return 1;
            }
            else if(col!=cold + 1 && col!=cold - 1){
                printf("movimento invalido\n");
                return 1;
            }


        if(gamer == 'B'){
            if(lin<lind){
                printf("movimento invalido1\n");
                    return 1;
            }
            else if(col!=cold + 1 && col!=cold - 1){
                printf("movimento invalido2\n");
                return 1;
            }

        }
    }

    //andar e comer com a peça normal
    if(M[lin][col] == 'B' || M[lin][col] == 'P'){
        if(gamer == 'B' && M[lind][cold] == oposto && M[lind - 1][cold - col + cold] == ' '){
            M[lin][col] = ' ';
            M[lind][cold] = ' ';
            M[lind - 1][cold - col + cold] = gamer;
        }
        else if(gamer == 'P' && M[lind][cold] == oposto && M[lind + 1][cold - col + cold] == ' '){
            M[lin][col] = ' ';
            M[lind][cold] = ' ';
            M[lind + 1][cold - col + cold] = gamer;
        }

        else if(gamer == 'P' && (col==cold + 1 || col==cold - 1) && M[lind][cold] == ' '){
            M[lin][col] = ' ';
            M[lind][cold] = gamer;
        }
        else if(gamer == 'B' && (col==cold + 1 || col==cold - 1) && M[lind][cold] == ' '){
            M[lin][col] = ' ';
            M[lind][cold] = gamer;
        }

        else{
            printf("movimento invalido\n");
            return 1;
        }
    }


    //Definindo o movimento e classificação de Dama
    for(i=0;i<8;i++){
        if(M[0][i] == 'B')
            M[0][i] = 3;
        if(M[7][i] == 'P')
            M[7][i] = 5;
    }

    if(M[lin][col] == 3 || M[lin][col] == 5){

        if(M[lin][col] == 3 && (M[lind][cold] == 'P' || M[lind][cold] == 5) && M[lind - lin + lind][cold - col + cold] == ' '){
            M[lin][col] = ' ';
            M[lind][cold] = ' ';
            M[lind - lin + lind][cold - col + cold] = 3;
        }
        else if(M[lin][col] == 5 && (M[lind][cold] == 'B' || M[lind][cold] == 3) && M[lind - lin + lind][cold - col + cold] == ' '){
            M[lin][col] = ' ';
            M[lind][cold] = ' ';
            M[lind - lin + lind][cold - col + cold] = 5;
        }
        else if(M[lin][col] == 3 && M[lind][cold] == ' '){
                M[lin][col] = ' ';
                M[lind][cold] = 3;
        }
        else if(M[lin][col] == 5 && M[lind][cold] == ' '){
                M[lin][col] = ' ';
                M[lind][cold] = 5;
        }

        else{
            printf("movimento invalido\n");
            return 1;
        }

    }

}

//verifica se continua ou para o jogo
int status(char **M){

    int i, j, r = 0, p = 0;
    //ele esta verificando apenas uma posicao
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            if(M[i][j]== 'B' || M[i][j]== 3){
                    //printf("O jogador B ainda esta no jogo.\n");
                    r = 1;
                    break;
            }
        }
        if(r==1)
            break;
    }
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            if(M[i][j]== 'P' || M[i][j]== 5){
                    //printf("O jogador P ainda esta no jogo.\n");
                    p = 1;
                    break;
            }
        }
        if(p==1)
            break;
    }
    if (r == 1 && p == 1){
        return -1;
    }
    else if (r == 1 && p == 0){
        printf("O jogador B ganhou\n");
        printmatriz(M);
        return 3;
    }
    else if (r == 0 && p == 1){
        printf("O jogador P ganhou\n");
        printmatriz(M);
        return 2;
    }

}
