//Gustavo Donnangelo Cassettari e Diego de Moraes Aguiar

#include <stdio.h>
#include <string.h>
#define N 8

//Prototipos das funcoes

char **initialize();
void printmatriz (char **M);
void printposicoes (char **M);
int step (char **M, int lin, int col, int lind, int cold, char gamer);
int status(char **M);
int statusgamer(char **M, char gamer);
int contador (char **M);

int main (void){

	system("color f0");
	char **M, gamer = 'b';
	int lin, col, lind, cold, jogoativo = -1;

 	M = initialize();
 	printposicoes(M);

    //Loop do programa
 	while(jogoativo==-1){

        printmatriz(M);
        printf ("Caro jogador [%c] digite a linha da peca que deseja mover:",gamer);
        scanf ("%d",&lin);
        printf ("Caro jogador [%c] digite a coluna da peca que deseja mover:",gamer);
        scanf ("%d",&col);
        printf ("Caro jogador [%c] digite a linha para onde deseja mover:",gamer);
        scanf ("%d",&lind);
        printf ("Caro jogador [%c] digite a coluna para onde deseja mover:",gamer);
        scanf ("%d",&cold);
        printf ("\n\n\n");


        //Condiçao do movimento dentro da matriz
        if(lin < 0 || lin > 7 || lind < 0 || lind > 7 || col < 0 || col > 7 || cold < 0 || cold > 7){

            printf("\t  Movimento invalido\n\n");
            continue;
        }

        //Se nao pode prosseguir
        if( step (M, lin, col, lind, cold, gamer) == 1){
            continue;
        }

        jogoativo = status(M);

        //Alternancia de gamer
        if (gamer == 'p')
            gamer = 'b';
        else
            gamer = 'p';

        contador(M);

    }

	return 0;
}

//funcoes:

//Alocar posicoes
char **initialize() {
    char **M;
    int i, j;

    M = (char **) calloc (N, sizeof (char *));
    for (i = 0; i < N; i++)
        M[i]=(char *)calloc(N, sizeof(char));

    for(i = 0; i < N; i++)
        for(j = 0; j < N; j++)
            M[i][j] = ' ';

    return M;
}

//Colocar posicoes iniciais das pecas
void printposicoes (char **M){

	int i, j;

	for(i = 0; i < 8; i++){
        for(j = 0;j < 8; j++){
            M[i][j] = 178;
        }
	}
	for(i = 3; i<4;i++){
        for(j = 0; j < 8;j += 2){
            M[i][j] = ' ';
        }
	}
	for(i = 4; i < 5; i++){
        for(j = 1; j < 8; j += 2){
            M[i][j] = ' ';
        }
	}

	for(i = 0; i < 3; i++){

		if(i%2 == 0)
			j = 1;
		else
			j = 0;
		while(j < 8){

			M[i][j] = 'p';
			j += 2;
		}
	}
	for(i = 5; i < 8; i++){
		if(i%2 == 0)
			j = 1;

		else
			j = 0;
		while(j < 8){
			M[i][j] = 'b';
			j += 2;
		}
	}

//	M[1][2] = 'P';
//	M[0][3] = 'B';

}

//Gera o tabuleiro com as pecas
void printmatriz (char **M){

	int i, j;
	printf("  ");
    for(i = 0;i < N; i++){

    	printf("   %d", i);
    }

    printf("\n\n");

    for(i = 0;i < N; i++){

        printf(" %d ", i);

        for(j = 0;j < N; j++){

            printf("  %c ",M[i][j]);
        }

        printf("\n\n");

    }



}

//Verifica se pode jogar naquela posicao e movimentacao
int step (char **M, int lin, int col, int lind, int cold, char gamer){

    char oposto, Dg, Do;
    int i;

    //definição do rivais
    if(gamer == 'b'){
        oposto = 'p';
        Dg = 'B';
        Do = 'P';
    }

    else{
        oposto = 'b';
        Dg = 'P';
        Do = 'B';
    }


    // P começa em cima e b em Baixo

    //condição de posiveis locais de peças
    if((lin + col) % 2 == 0 || (lind + cold) % 2 == 0){
        printf("\t  Movimento invalido\n\n");
        return 1;
    }

    //Nao mover espacos vazios e movimenta apenas pecas do jogador
    if(M[lin][col] != gamer && M[lin][col] != Dg){
        printf("\t  Movimento invalido\n\n");
        return 1;
    }

    //nao deixa comer para fora do tabuleiro
    if((lind == 0 || lind == 7) && (M[lind][cold] == oposto || M[lind][cold] == Do)){
        printf("\t  Movimento invalido\n\n");
        return 1;
    }

    //gambs
    else if(M[lin][col] == 'B' || M[lin][col] == 'P'){

    //Movimento P apenas para frente
    }
    else if(M[lin][col] == 'p'){

            if(lin > lind){
                printf("\t  Movimento invalido\n\n");
                return 1;
            }
            else if(col != cold + 1 && col !=cold - 1){
                printf("\t  Movimento invalido\n\n");
                return 1;
            }
    }

    //Movimento B apenas para frente
    else if(M[lin][col] == 'b'){
        if(lin < lind){
            printf("\t  Movimento invalido\n\n");
                return 1;
        }
        else if(col != cold + 1 && col != cold - 1){
            printf("\t  Movimento invalido\n\n");
            return 1;
        }
    }

    //Andar e comer com a peça normal

    if(M[lin][col] == 'b' || M[lin][col] == 'p'){
        if(M[lin][col] == 'b' && M[lind][cold] == 'p' && M[lind - 1][cold - col + cold] == ' '){
            M[lin][col] = ' ';
            M[lind][cold] = ' ';
            M[lind - 1][cold - col + cold] = gamer;
        }
        else if(M[lin][col] == 'p' && M[lind][cold] == 'b' && M[lind + 1][cold - col + cold] == ' '){
            M[lin][col] = ' ';
            M[lind][cold] = ' ';
            M[lind + 1][cold - col + cold] = gamer;
        }
        else if(M[lin][col] == 'b' && M[lind][cold] == 'P' && M[lind - 1][cold - col + cold] == ' '){
            M[lin][col] = ' ';
            M[lind][cold] = ' ';
            M[lind - 1][cold - col + cold] = gamer;
        }
        else if(M[lin][col] == 'p' && M[lind][cold] == 'B' && M[lind + 1][cold - col + cold] == ' '){
            M[lin][col] = ' ';
            M[lind][cold] = ' ';
            M[lind + 1][cold - col + cold] = gamer;
        }

        else if(M[lin][col] == 'b' && (col==cold + 1 || col==cold - 1) && M[lind][cold] == ' '){
            M[lin][col] = ' ';
            M[lind][cold] = gamer;
        }
        else if(M[lin][col] == 'p' && (col==cold + 1 || col==cold - 1) && M[lind][cold] == ' '){
            M[lin][col] = ' ';
            M[lind][cold] = gamer;
        }

        else{

            printf("\t  Movimento invalido\n\n");
            return 1;
        }

    }


    //Classificacao de Dama
    for(i = 0; i < 8; i++){
        if(M[0][i] == 'b')
            M[0][i] = 'B';
        if(M[7][i] == 'p')
            M[7][i] = 'P';
    }
    //Andando e comendo com a dama
    if(M[lin][col] == 'B' || M[lin][col] == 'P'){
        if((cold != col + 1 && cold != col - 1) || (lind != lin + 1 && lind != lin - 1)){
            printf("\t  Movimento invalido\n\n");
            return 1;
        }

        else if(M[lin][col] == 'B' && (M[lind][cold] == 'p' || M[lind][cold] == 'P') && M[lind - lin + lind][cold - col + cold] == ' '){
            M[lin][col] = ' ';
            M[lind][cold] = ' ';
            M[lind - lin + lind][cold - col + cold] = 'B';
        }
        else if(M[lin][col] == 'P' && (M[lind][cold] == 'b' || M[lind][cold] == 'B') && M[lind - lin + lind][cold - col + cold] == ' '){
            M[lin][col] = ' ';
            M[lind][cold] = ' ';
            M[lind - lin + lind][cold - col + cold] = 'P';
        }
        else if(M[lin][col] == 'B' && M[lind][cold] == ' '){
                M[lin][col] = ' ';
                M[lind][cold] = 'B';
        }
        else if(M[lin][col] == 'P' && M[lind][cold] == ' '){
                M[lin][col] = ' ';
                M[lind][cold] = 'P';
        }
        else{

            printf("\t  Movimento invalido\n\n");
            return 1;
        }

    }

}

//Verifica se continua ou para o jogo
int status(char **M){

    int i, j, r = 0, p = 0;
    //verificar se ha pecas do jogador B no tabuleiro
    for(i = 0; i < N; i++){

        for(j = 0; j<N; j++){

            if(M[i][j]== 'b' || M[i][j]== 'B'){
                   r = 1;
                    break;
            }
        }
        if(r==1)
            break;
    }

    //Verificar se ha pecas do jogador P no tabuleiro
    for(i = 0; i < N; i++){

        for(j = 0; j < N; j++){

            if(M[i][j]== 'p' || M[i][j]== 'P'){
                    p = 1;
                    break;
            }
        }
        if(p == 1)
            break;
    }

    if (r == 1 && p == 1){

        return -1;
    }

    else if (r == 1 && p == 0){

        printf(">>>>>>>>O jogador B ganhou<<<<<<<<\n\n");

        printmatriz(M);

        return 3;
    }
    else if (r == 0 && p == 1){

        printf(">>>>>>>O jogador P ganhou<<<<<<<\n\n");

        printmatriz(M);

        return 2;
    }

}

//conta a quantidade de peças no jogo
int contador (char **M){

    int i, j, B=0, P=0;

    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            if(M[i][j] == 'b' || M[i][j] == 'B')
                B++;
            if(M[i][j] == 'p' || M[i][j] == 'P')
                P++;
        }
    }

    printf("Ainda tem %d peças B e ja foram comidas %d do jogador B.\n", B, 12-B);
    printf("Ainda tem %d peças P e ja foram comidas %d do jogador P.\n\n\n\n", P, 12-P);

}
