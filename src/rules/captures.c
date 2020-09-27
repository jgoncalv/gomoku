//
// Created by Jimmy Gonçalves on 25/09/2020.
//

#include "captures.h"

static void captures_dir(int board[BOARD_SIZE][BOARD_SIZE], t_position position, int color, t_position direction) {
    t_position more3;
    t_position more2;
    t_position more1;
    int opposite_color = get_opposite_pawn_color(color);

    more3.y = position.y + 3 * direction.y;
    more3.x = position.x + 3 * direction.x;

    more2.y = position.y + 2 * direction.y;
    more2.x = position.x + 2 * direction.x;

    more1.y = position.y + 1 * direction.y;
    more1.x = position.x + 1 * direction.x;

    printf("Test, x %d y %d\n", more2.x, more2.y);
    if (is_pawn_in_the_board(more3)) {
        if (is_pawn_color(board, more3, color) &&
            is_pawn_color(board, more2, opposite_color) &&
            is_pawn_color(board, more1, opposite_color)) {

            add_pawn(board, more2, color);
            add_pawn(board, more1, color);
        }
    }
}

void captures(int board[BOARD_SIZE][BOARD_SIZE], t_position position, int color) {
    captures_dir(board, position, color, g_directions.horizontal_bot);
    captures_dir(board, position, color, g_directions.horizontal_top);
    captures_dir(board, position, color, g_directions.vertical_right);
    captures_dir(board, position, color, g_directions.vertical_left);
    captures_dir(board, position, color, g_directions.diagonal_top_left);
    captures_dir(board, position, color, g_directions.diagonal_bot_right);
    captures_dir(board, position, color, g_directions.diagonal_bot_left);
    captures_dir(board, position, color, g_directions.diagonal_top_right);
}