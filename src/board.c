//
// Created by Jimmy Gonçalves on 24/09/2020.
//
#include "board.h"

t_direction g_directions = {
        HORIZONTAL_TOP,
        HORIZONTAL_BOT,
        VERTICAL_lEFT,
        VERTICAL_RIGHT,
        DIAGONAL_TOP_LEFT,
        DIAGONAL_BOT_RIGHT,
        DIAGONAL_TOP_RIGHT,
        DIAGONAL_BOT_LEFT,
};

int get_opposite_pawn_color(int color) {
    return color == BLACK ? WHITE : BLACK;
}

int is_pawn_in_the_board(t_position position) {
    if (position.x >= 0 && position.y >= 0 && position.x < BOARD_SIZE && position.y < BOARD_SIZE) {
        return 1;
    }
    return 0;
}

int is_pawn_color(int board[BOARD_SIZE][BOARD_SIZE], t_position position, int color) {
    return board[position.y][position.x] == color ? 1 : 0;
}

void add_pawn(int board[BOARD_SIZE][BOARD_SIZE], t_position position, int color) {
    board[position.y][position.x] = color;
}

// Return 0 if it failed else it return 1
int place_the_pawn(int board[BOARD_SIZE][BOARD_SIZE], t_position position, int color) {
    if (is_pawn_in_the_board(position) && is_pawn_color(board, position, EMPTY)) {
        // Apply the rules
        if (!free_threes(board, position, color)) {
            add_pawn(board, position, color);
//            captures(board, position, color);
            return 1;
        }
    }
    return 0;
}

static int there_is_a_pawn(int board[BOARD_SIZE][BOARD_SIZE], t_position position, t_position direction) {
    t_position test_pos;
    int i = 1;

//    while (i < MIN_TO_WIN) {
        test_pos.x = position.x + i * direction.x;
        test_pos.y = position.y + i * direction.y;
        if (is_pawn_in_the_board(test_pos)) {
            // If we find something else than EMPTY pawn we return true
            if (!is_pawn_color(board, test_pos, EMPTY)) {
                return 1;
            }
        }
//        i++;
//    }
    // We didn't not found any pawn arround;
    return 0;
}

// Find the position nearest pawn at 5 row max
t_position find_nearest_position(int board[BOARD_SIZE][BOARD_SIZE], t_position pos) {
    // Maybe the first one is a bad position so we modify
    if (!is_pawn_in_the_board(pos)) {
        pos.x = 0;
        pos.y++;
    }
    while (is_pawn_in_the_board(pos)) {
        while (is_pawn_in_the_board(pos)) {

            if (is_pawn_color(board, pos, EMPTY)) {

                // Checking this:
                // . c . . . c . . . c .
                // . . c . . c . . c . .
                // . . . c . c . c . . .
                // . . . . c c c . . . .
                // . c c c c x c c c c .
                // . . . . c c c . . . .
                // . . . c . c . c . . .
                // . . c . . c . . c . .
                // . c . . . c . . . c .
                if (there_is_a_pawn(board, pos, g_directions.horizontal_bot) ||
                    there_is_a_pawn(board, pos, g_directions.horizontal_top) ||
                    there_is_a_pawn(board, pos, g_directions.vertical_right) ||
                    there_is_a_pawn(board, pos, g_directions.vertical_left) ||
                    there_is_a_pawn(board, pos, g_directions.diagonal_bot_right) ||
                    there_is_a_pawn(board, pos, g_directions.diagonal_bot_left) ||
                    there_is_a_pawn(board, pos, g_directions.diagonal_top_left) ||
                    there_is_a_pawn(board, pos, g_directions.diagonal_top_right)) {
                    return pos;
                }
            }
            pos.x++;
        }
        pos.x = 0;
        pos.y++;
    }
    // If we haven't found anything but it should not be possible because we have put the black at the middle
    pos.x = -1;
    pos.y = -1;
    return pos;
}