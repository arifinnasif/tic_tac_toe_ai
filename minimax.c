#include<limits.h>

int move_row;
int move_col;

int ** dup_board;
extern int N, O_count, X_count;
extern int check_winner(int ** board, int N, int update_row, int update_col);
int dummy_count;

void copy_board(int** board) {
	dup_board = (int **) malloc(N * sizeof(int *));
	for(int i = 0; i < N; i++) {
		dup_board[i] = (int *) malloc(N * sizeof(int));
		for(int j = 0; j < N; j++) {
			dup_board[i][j] = board[i][j]; // 0 mean empty, 1 means means cross, -1 means naught
		}
	}
}

void delete_dup_board() {
	for(int i = 0; i < N; i++) {
		free(dup_board[i]);
	}
	free(dup_board);
}

int minimax(int is_max, int depth) {
char rep_char[] = {'o', ' ', '*'};
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			printf(" %c", rep_char[dup_board[i][j] + 1]);
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
		printf("\n"); 
	int temp;
	if((temp = check_winner(dup_board, N, -1, -1)) || O_count+X_count+dummy_count >= N*N) {printf("*****************%d***************\n",temp); return temp;}
//	if((temp = check_winner(dup_board, N, -1, -1)) || O_count+X_count+dummy_count >= N*N) {return temp;}
	if(is_max) {
		int val = INT_MIN;
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < N; j++) {
				if(dup_board[i][j] == 0) {
					dup_board[i][j] = 1;
					dummy_count++;
					int t = minimax(0, depth+1);
					if(t > val) {
						val = t;
						if(depth == 0) {
							move_row = i;
							move_col = j;
		printf("max %d>> %d %d | %d\n",depth, move_row,move_col,val);
						}
					}
					dup_board[i][j] = 0;
					dummy_count--;
				}
			}
		}
		return val;
	} else {
		int val = INT_MAX;
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < N; j++) {
				if(dup_board[i][j] == 0) {
					dup_board[i][j] = -1;
					dummy_count++;
					int t = minimax(1, depth+1);
					if(t < val) {
						val = t;
						if(depth == 0) {
							move_row = i;
							move_col = j;
		printf("min %d>> %d %d | %d\n",depth,move_row,move_col,val);
						}
					}
					dup_board[i][j] = 0;
					dummy_count--;
				}
			}
		}
		return val;
	}
}

void ai_move(int **arg_board, int arg_is_max) {
	dummy_count=0;
	copy_board(arg_board);
	minimax(arg_is_max,0);
	delete_dup_board();
}
