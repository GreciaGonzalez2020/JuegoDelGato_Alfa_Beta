/*Juego del Gato
    Trabajo realizado para la materia de Inteligencia Artificial I.
    En este juego se ultiliza algoritmo minimax por parte de la máquina
    Se Implementa Poda Alfa_Beta*/


#include<stdio.h>
#include<stdbool.h>

#define COMPUTER 1
#define HUMAN 2

#define SIDE 3

#define COMPUTERMOVE 'O'
#define HUMANMOVE 'X'

void showBoard(char board[][SIDE])
{
	printf("\t\t\t %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
	printf("\t\t\t-----------\n");
	printf("\t\t\t %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
	printf("\t\t\t-----------\n");
	printf("\t\t\t %c | %c | %c \n\n", board[2][0], board[2][1], board[2][2]);
}

void showInstructions()//Función para indicarle al usuario cómo deberá jugar
{
	printf("\t\nElige una casilla de acuerdo a lo siguiente:\n\n");

	printf("\t\t\t 1 | 2 | 3 \n");
	printf("\t\t\t-----------\n");
	printf("\t\t\t 4 | 5 | 6 \n");
	printf("\t\t\t-----------\n");
	printf("\t\t\t 7 | 8 | 9 \n\n");
}

void initialise(char board[][SIDE])
{
	for (int i=0; i<SIDE; i++)
	{
		for (int j=0; j<SIDE; j++)
			board[i][j] = ' ';
	}
}

void declareWinner(int whoseTurn)
{
	if (whoseTurn == COMPUTER)
		printf("\t\tHa ganado la IA\n");
	else
		printf("\t\tLo lograste! Ganaste!\n");
}

bool rowCrossed(char board[][SIDE])
{
	for (int i=0; i<SIDE; i++)
	{
		if (board[i][0] == board[i][1] &&
			board[i][1] == board[i][2] &&
			board[i][0] != ' ')
			return (true);
	}
	return(false);
}

//Funciones que buscan si se ha ganado de forma lineal o cruzada
bool columnCrossed(char board[][SIDE])
{
	for (int i=0; i<SIDE; i++)
	{
		if (board[0][i] == board[1][i] &&
			board[1][i] == board[2][i] &&
			board[0][i] != ' ')
			return (true);
	}
	return(false);
}

bool diagonalCrossed(char board[][SIDE])
{
	if (board[0][0] == board[1][1] &&
		board[1][1] == board[2][2] &&
		board[0][0] != ' ')
		return(true);

	if (board[0][2] == board[1][1] &&
		board[1][1] == board[2][0] &&
		board[0][2] != ' ')
		return(true);

	return(false);
}

//Si se encuentra un ganador se termina el juego.
bool gameOver(char board[][SIDE])
{
	return(rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board) );
}

//Función minimax con poda alfa-beta
int minimax(char board[][SIDE], int depth, bool isAI, int alpha, int beta)
{
	if (gameOver(board))
	{
		if (isAI)
			return -1;
		else
			return 1;
	}

	if (depth >= 9)
		return 0;
    //Poda Alfa
	if (isAI)
	{
		int bestScore = -999;
		for (int i = 0; i < SIDE; i++)
		{
			for (int j = 0; j < SIDE; j++)
			{
				if (board[i][j] == ' ')
				{
					board[i][j] = COMPUTERMOVE;
					int score = minimax(board, depth + 1, false, alpha, beta);
					board[i][j] = ' ';
					bestScore = score > bestScore ? score : bestScore;
					alpha = alpha > bestScore ? alpha : bestScore;
					if (alpha >= beta)
						return bestScore;
				}
			}
		}
		return bestScore;
	}
	else //Poda Beta
	{
		int bestScore = 999;
		for (int i = 0; i < SIDE; i++)
		{
			for (int j = 0; j < SIDE; j++)
			{
				if (board[i][j] == ' ')
				{
					board[i][j] = HUMANMOVE;
					int score = minimax(board, depth + 1, true, alpha, beta);
					board[i][j] = ' ';
					bestScore = score < bestScore ? score : bestScore;
					beta = beta < bestScore ? beta : bestScore;
					if (alpha >= beta)
						return bestScore;
				}
			}
		}
		return bestScore;
	}
}

int bestMove(char board[][SIDE], int moveIndex)
{
	int x = -1, y = -1;
	int bestScore = -999;
	for (int i = 0; i < SIDE; i++)
	{
		for (int j = 0; j < SIDE; j++)
		{
			if (board[i][j] == ' ')
			{
				board[i][j] = COMPUTERMOVE;
				int score = minimax(board, moveIndex + 1, false, -999, 999);
				board[i][j] = ' ';
				if (score > bestScore)
				{
					bestScore = score;
					x = i;
					y = j;
				}
			}
		}
	}
	return x * SIDE + y;
}

void playGato(int whoseTurn)
{
	char board[SIDE][SIDE];
	int moveIndex = 0, x = 0, y = 0;

	initialise(board);

	while (gameOver(board) == false && moveIndex != SIDE * SIDE)
	{
		int n;
		if (whoseTurn == COMPUTER)
		{
			n = bestMove(board, moveIndex);
			x = n / SIDE;
			y = n % SIDE;
			board[x][y] = COMPUTERMOVE;
			printf("\tLa IA ha colocado %c en la casilla %d\n\n", COMPUTERMOVE, n + 1);
			showBoard(board);
			moveIndex++;
			whoseTurn = HUMAN;
		}

		else if (whoseTurn == HUMAN)
		{
			printf("\tPuedes elegir las siguientes casillas : ");
			for (int i = 0; i < SIDE; i++)
				for (int j = 0; j < SIDE; j++)
					if (board[i][j] == ' ')
						printf("%d ", (i * SIDE + j) + 1);
			printf("\t\n\nElige una casilla = ");
			scanf("%d", &n);
			n--;
			x = n / SIDE;
			y = n % SIDE;
			if (board[x][y] == ' ' && n < SIDE * SIDE && n >= 0)
			{
				board[x][y] = HUMANMOVE;
				printf("\t\nHaz puesto %c en la casilla %d\n\n", HUMANMOVE, n + 1);
				showBoard(board);
				moveIndex++;
				whoseTurn = COMPUTER;
			}
			else if (board[x][y] != ' ' && n < SIDE * SIDE && n >= 0)
			{
				printf("\t\nLa casilla está ocupada, selecciona una casilla disponible\n\n");
			}
			else if (n < 0 || n >= SIDE * SIDE)
			{
				printf("\tPosición inválida\n");
			}
		}
	}

	if (gameOver(board) == false && moveIndex == SIDE * SIDE)
		printf("\t\tEs un empate\n");
	else
	{
		if (whoseTurn == COMPUTER)
			whoseTurn = HUMAN;
		else if (whoseTurn == HUMAN)
			whoseTurn = COMPUTER;

		declareWinner(whoseTurn);
	}
}

int main()
{
	printf("\n-----------------------------------------------------------------\n\n");
	printf("|\t\t\t Juego del Gato\t\t\t\t|\n");
	printf("\n-----------------------------------------------------------------\n\n");
	char cont = 'y';
	do {
		char choice;
		printf("\t¿Quieres empezar primero? (y/n): ");
		scanf(" %c", &choice);
		showInstructions();
		if (choice == 'n')
			playGato(COMPUTER);
		else if (choice == 'y')
			playGato(HUMAN);
		else
			printf("\tElección inválida\n");

		printf("\t\n¿Quieres salir? (y/n): ");
		scanf(" %c", &cont);
	} while (cont == 'n');
	return (0);
}
