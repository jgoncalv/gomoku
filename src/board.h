//
// Created by Jimmy Gonçalves on 24/09/2020.
//

#ifndef GOMOKU_BOARD_H
# define GOMOKU_BOARD_H
# define BOARD_SIZE 19
# define EMPTY 0
# define WHITE 1
# define BLACK 2
# define MIN_TO_WIN 5
# define MAX_MINMAX_DEPTH 4
# define HORIZONTAL_TOP {-1, 0}
# define HORIZONTAL_BOT {1, 0}
# define VERTICAL_lEFT {0, -1}
# define VERTICAL_RIGHT {0, 1}
# define DIAGONAL_TOP_LEFT {-1, -1}
# define DIAGONAL_BOT_RIGHT {1, 1}
# define DIAGONAL_TOP_RIGHT {-1, 1}
# define DIAGONAL_BOT_LEFT {1, -1}

typedef struct s_position {
    int x;
    int y;
} t_position;

typedef struct s_direction {
    t_position horizontal_top;
    t_position horizontal_bot;
    t_position vertical_left;
    t_position vertical_right;
    t_position diagonal_top_left;
    t_position diagonal_bot_right;
    t_position diagonal_top_right;
    t_position diagonal_bot_left;
} t_direction;

extern t_direction g_directions;


# include <stdio.h>
# include "rules/free_threes.h"
# include "rules/captures.h"


int get_opposite_pawn_color(int color);

int is_pawn_in_the_board(t_position position);

int is_pawn_color(int board[BOARD_SIZE][BOARD_SIZE], t_position position, int color);

void add_pawn(int board[BOARD_SIZE][BOARD_SIZE], t_position position, int color);

int place_the_pawn(int board[BOARD_SIZE][BOARD_SIZE], t_position position, int color);

int has_a_pawn_near(int board[BOARD_SIZE][BOARD_SIZE], t_position pos);

void print_board(int board[BOARD_SIZE][BOARD_SIZE]);

#endif //GOMOKU_BOARD_H
