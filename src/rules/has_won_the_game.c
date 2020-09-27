//
// Created by Jimmy Gonçalves on 25/09/2020.
//

#include "has_won_the_game.h"

static int count_align_pawn(int board[BOARD_SIZE][BOARD_SIZE], t_position position, int color, t_position dir) {
    int i = 1;
    int count = 0;
    t_position npos;

    while (i < MIN_TO_WIN) {
        npos.x = position.x + i * dir.x;
        npos.y = position.y + i * dir.y;

        if (!is_pawn_in_the_board(npos)) break;

        if (is_pawn_color(board, npos, color)) {
            count++;
        } else {
            break;
        }
        i++;
    }
    return count;
}

static int check_win(int board[BOARD_SIZE][BOARD_SIZE], t_position position, int color) {
    if (!is_pawn_in_the_board(position) || !is_pawn_color(board, position, color)) {
        return 0;
    }
    int hor = count_align_pawn(board, position, color, g_directions.horizontal_top) +
              count_align_pawn(board, position, color, g_directions.horizontal_bot);
    if (hor >= MIN_TO_WIN - 1) {
        return 1;
    }

    int ver = count_align_pawn(board, position, color, g_directions.vertical_left) +
              count_align_pawn(board, position, color, g_directions.vertical_right);
    if (ver >= MIN_TO_WIN - 1) {
        return 1;
    }

    int diag_left = count_align_pawn(board, position, color, g_directions.diagonal_top_left) +
                    count_align_pawn(board, position, color, g_directions.diagonal_bot_right);
    if (diag_left >= MIN_TO_WIN - 1) {
        return 1;
    }

    int diag_right = count_align_pawn(board, position, color, g_directions.diagonal_top_right) +
                     count_align_pawn(board, position, color, g_directions.diagonal_bot_left);
    if (diag_right >= MIN_TO_WIN - 1) {
        return 1;
    }
    return 0;
}

static int in_case_of_captures(int board[BOARD_SIZE][BOARD_SIZE], t_position position, int color, t_position dir, int i) {
    t_position pos;

    pos.x = position.x + i * dir.x;
    pos.y = position.y + i * dir.y;
    return check_win(board, pos, color);
}

// For check if the game is won we apply the rules by counting the number of the same colors apply around the next move
int has_won_the_game(int board[BOARD_SIZE][BOARD_SIZE], t_position position, int color) {
    t_position  pos;
    if (check_win(board, position, color)) {
        return 1;
    }

    // Check more two if ones have been changed
    int i = 1;
    while (i <= 2) {
        if (in_case_of_captures(board, position, color, g_directions.diagonal_top_right, i) ||
                in_case_of_captures(board, position, color, g_directions.diagonal_bot_left, i) ||
                in_case_of_captures(board, position, color, g_directions.diagonal_bot_right, i) ||
                in_case_of_captures(board, position, color, g_directions.diagonal_top_left, i) ||
                in_case_of_captures(board, position, color, g_directions.horizontal_top, i) ||
                in_case_of_captures(board, position, color, g_directions.horizontal_bot, i) ||
                in_case_of_captures(board, position, color, g_directions.vertical_left, i) ||
                in_case_of_captures(board, position, color, g_directions.vertical_right, i)
        ) {
            return 1;
        }
        i++;
    }

    return 0;
}
