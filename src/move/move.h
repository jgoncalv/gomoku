//
// Created by Jimmy Gonçalves on 24/09/2020.
//

#ifndef GOMOKU_MOVE_H
# define GOMOKU_MOVE_H
# include <limits.h>
# include "../board.h"
# include "../rules/has_won_the_game.h"
# include "evaluate.h"


t_position get_best_move(int board[BOARD_SIZE][BOARD_SIZE], int color);

#endif //GOMOKU_MOVE_H
