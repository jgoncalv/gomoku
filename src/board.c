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

t_position DIRECTIONS[] = {
        HORIZONTAL_TOP,
        HORIZONTAL_BOT,
        VERTICAL_lEFT,
        VERTICAL_RIGHT,
        DIAGONAL_TOP_LEFT,
        DIAGONAL_BOT_RIGHT,
        DIAGONAL_TOP_RIGHT,
        DIAGONAL_BOT_LEFT
};

void print_board(int board[BOARD_SIZE][BOARD_SIZE]) {
    // print column index
    printf("   ");
    for (int i = 0; i < BOARD_SIZE; ++i) {
        int col = i + 1;
        printf("%d", col);
        printf(col < 10 ? "  " : " ");
    }
    printf("\n");

    // print row index as well as each square on board
    for (int i = 0; i < BOARD_SIZE; ++i) {
        char row = 'A' + i;
        printf("%c  ", row);
        for (int j = 0; j < BOARD_SIZE; ++j) {
            char c = ' ';
            switch (board[i][j]) {
                case EMPTY :
                    c = '.';
                    break;
                case BLACK :
                    c = 'x';
                    break;
                case WHITE :
                    c = 'o';
                    break;
            }
            printf("%c  ", c);
        }
        printf("\n");
    }
}

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
//        if (!free_threes(board, position, color)) {
            add_pawn(board, position, color);
            // TODO: Uncomment
//            captures(board, position, color);
            return 1;
//        }
    }
    return 0;
}

int has_a_pawn_near(int board[BOARD_SIZE][BOARD_SIZE], t_position pos) {
    int i = 0;
    t_position test_pos;

    while (i < sizeof(DIRECTIONS)) {
        test_pos.y = pos.y + DIRECTIONS[i].y;
        test_pos.x = pos.x + DIRECTIONS[i].x;
        if (is_pawn_in_the_board(test_pos)) {
            if (!is_pawn_color(board, test_pos, EMPTY)) {
                return 1;
            }
        }
        i++;
    }
    return 0;
}