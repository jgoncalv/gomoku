//
// Created by Jimmy Gonçalves on 25/09/2020.
//

#include "free_threes.h"

static int free_threes_direction(int board[BOARD_SIZE][BOARD_SIZE],
                                 t_position position, int vertical_dir, int horizontal_dir, int color)
{
    t_position minus4;
    t_position minus3;
    t_position minus2;
    t_position minus1;
    t_position plus1;
    t_position plus2;


    minus4.y = position.y - 4 * vertical_dir;
    minus4.x = position.x - 4 * horizontal_dir;

    minus3.y = position.y - 3 * vertical_dir;
    minus3.x = position.x - 3 * horizontal_dir;

    minus2.y = position.y - 2 * vertical_dir;
    minus2.x = position.x - 2 * horizontal_dir;

    minus1.y = position.y - 1 * vertical_dir;
    minus1.x = position.x - 1 * horizontal_dir;

    plus1.y = position.y + 1 * vertical_dir;
    plus1.x = position.x + 1 * horizontal_dir;

    plus2.y = position.y + 2 * vertical_dir;
    plus2.x = position.x + 2 * horizontal_dir;


    if (is_pawn_in_the_board(minus4) && is_pawn_in_the_board(plus1)) {
        // . x x . c .
        if (is_pawn_color(board, minus4, EMPTY) &&
        is_pawn_color(board, minus3, color) &&
        is_pawn_color(board, minus2, color) &&
        is_pawn_color(board, minus1, EMPTY) &&
        is_pawn_color(board, plus1, EMPTY)) {
            return 1;
        }
    }

    if (is_pawn_in_the_board(minus3) && is_pawn_in_the_board(plus1)) {
        // . x x c .
        if (is_pawn_color(board, minus3, EMPTY) &&
            is_pawn_color(board, minus2, color) &&
            is_pawn_color(board, minus1, color) &&
            is_pawn_color(board, plus1, EMPTY)) {
            return 1;
        }
    }

    if (is_pawn_in_the_board(minus2) && is_pawn_in_the_board(plus2)) {
        // . x c x .
        if (is_pawn_color(board, minus2, EMPTY) &&
            is_pawn_color(board, minus1, color) &&
            is_pawn_color(board, plus1, color) &&
            is_pawn_color(board, plus2, EMPTY)) {
            return 1;
        }
    }
    return 0;
}

int free_threes(int board[BOARD_SIZE][BOARD_SIZE], t_position position, int color) {
    int count = 0;

    // horizontal
    if (free_threes_direction(board, position, 0, 1, color) ||
        free_threes_direction(board, position, 0, -1, color)) {
        count++;
    }

    // vertical
    if (free_threes_direction(board, position, 1, 0, color) ||
        free_threes_direction(board, position, -1, 0, color)) {
        count++;
    }

    // Diagonal top-left to bot-right
    if (free_threes_direction(board, position, -1, -1, color) ||
        free_threes_direction(board, position, 1, 1, color)) {
        count++;
    }

    // Diagonal top-right to bot-left
    if (free_threes_direction(board, position, -1, 1, color) ||
        free_threes_direction(board, position, 1, -1, color)) {
        count++;
    }

    if (count >= 2) {
        return 1;
    }
    return 0;
}