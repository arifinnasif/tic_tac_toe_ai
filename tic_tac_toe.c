#include<stdio.h>
#include<stdlib.h>
#include "minimax.c"

#define INVALID 10

int **board; // dynamically allocated
int N; // number of rows and cols
char is_game_over;
int X_count;
int O_count;

void create_new_board(int arg_size) {
	X_count = 0;
	O_count = 0;
	is_game_over = 0;
	N = arg_size;
	board = (int **) malloc(N * sizeof(int *));
	for(int i = 0; i < N; i++) {
		board[i] = (int *) malloc(N * sizeof(int));
		for(int j = 0; j < N; j++) {
			board[i][j] = 0; // 0 mean empty, 1 means means cross, -1 means naught
		}
	}
}

void delete_board() {
	for(int i = 0; i < N; i++) {
		free(board[i]);
	}
	free(board);
}


int check_winner(int ** board, int N, int update_row, int update_col) {
	int ret;

	// checks for row-wise match
	for(int i = 0; i < N; i++) {
		if(update_row != -1 && i != update_row) continue;
		ret = board[i][0];
		for(int j = 1; j < N; j++) {
			if(ret != board[i][j]) {
				ret = 0;
				break;
			}
		}
		if(ret) {
			is_game_over = 1;
			return ret;
		}
	}

	// checks for col-wise match
	for(int i = 0; i < N; i++) {
		if(update_col != -1 && i != update_col) continue;
		ret = board[0][i];
		for(int j = 1; j < N; j++) {
			if(ret != board[j][i]) {
				ret = 0;
				break;
			}
		}
		if(ret) {
			is_game_over = 1;
			return ret;
		}
	}


	// major diagonal
	if((update_col == -1 || update_row == -1) || update_col == update_row) {
		ret = board[0][0];
		for(int k = 1; k < N; k++) {
			if(ret != board[k][k]) {
				ret = 0;
				break;
			}
		}
		if(ret) {
			is_game_over = 1;
			return ret;
		}
	}


	// minor diagonal
	if((update_col == -1 || update_row == -1) || update_col + update_row + 1 == N) {
		ret = board[0][N-1];
		for(int k = 1; k < N; k++) {
			if(ret != board[k][N-1-k]) {
				ret = 0;
				break;
			}
		}
		if(ret) {
			is_game_over = 1;
			return ret;
		}
	}

	return 0;
}

char rep_char[] = {'O', ' ', 'X'};

void print_board() {
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			printf(" %c", rep_char[board[i][j] + 1]);
			if(j < N-1) printf(" |");
		}
		if(i < N-1) {
			printf("\n");
			for(int j = 0; j < N; j++) {
				if(j < N-1) printf("----");
				else printf("---");
			}
		}
		printf("\n");
	}
}

int X_move(int arg_row, int arg_col) {
	if(arg_row < 0 || arg_row >= N || arg_col < 0 || arg_col >= N) {
		printf("%d %d is out of bound", arg_row, arg_col);
		return INVALID;
	}

	if(board[arg_row][arg_col]) {
		printf("%d %d is not free", arg_row, arg_col);
		return INVALID;
	}

	board[arg_row][arg_col] = 1;
	X_count++;
	is_game_over = (X_count + O_count) >= N*N;
	print_board();
	return check_winner(board, N, arg_row, arg_col);
}

int O_move(int arg_row, int arg_col) {
	if(arg_row < 0 || arg_row >= N || arg_col < 0 || arg_col >= N) {
		printf("%d %d is out of bound\n", arg_row, arg_col);
		return INVALID;
	}

	if(board[arg_row][arg_col]) {
		printf("%d %d is not free\n", arg_row, arg_col);
		return INVALID;
	}

	board[arg_row][arg_col] = -1;
	O_count++;
	is_game_over = (X_count + O_count) >= N*N;
	print_board();
	return check_winner(board, N, arg_row, arg_col);
}

int main() {
	scanf("%d",&N);
	create_new_board(N);
	printf("%dX%d BOARD CREATED\n",N,N);
	print_board();
	char is_X = 1;
	int arg_row, arg_col;
	int t;
	while(!is_game_over) {
		if(is_X) {
			printf("[X] : ");
			scanf("%d %d", &arg_row, &arg_col);
			t = X_move(arg_row, arg_col);
		} else {
			printf("[O] : ");
			// scanf("%d %d", &arg_row, &arg_col);
			ai_move(board, 0);
			printf("%d %d\n", move_row, move_col);
			t = O_move(move_row, move_col);
		}

		if(t == INVALID) continue;

		is_X = !is_X;
		if(t == 1) {
			printf("X wins!\n");
			break;
		} else if(t == -1) {
			printf("O wins!\n");
			break;
		} 

	}
	delete_board();
}
