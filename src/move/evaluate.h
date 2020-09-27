//
// Created by Jimmy Gonçalves on 26/09/2020.
//

#ifndef GOMOKU_EVALUATE_H
# define GOMOKU_EVALUATE_H

# include <limits.h>
# include "../board.h"

typedef struct s_evaluation {
    int open_end;
    int count;
    int count_empty;
    int can_align_5;
} t_evaluation;

int evaluate(int board[BOARD_SIZE][BOARD_SIZE], t_position position, int color);

#endif //GOMOKU_EVALUATE_H
