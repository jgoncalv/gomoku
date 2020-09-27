//
// Created by Jimmy Gonçalves on 24/09/2020.
//
#include "move.h"

static int max(int a, int b) {
    return a > b ? a : b;
}

static int min(int a, int b) {
    return a < b ? a : b;
}

static int minimax(t_position position, int depth,
                   int alpha, int beta, int maximizing_player, int board[BOARD_SIZE][BOARD_SIZE], int color) {
    t_position new_position;
    int eval;
    int y = 0;
    int opposite_color = get_opposite_pawn_color(color);

    // TODO: FIX
    // There is a problem here because we capture and replace we forget to reset like it has been
    if (!place_the_pawn(board, position, color)) {
        return -1;
    }
    if (depth == 0) {
        eval = evaluate(board, position, color);
//        printf("Hello ici eval: %d\n", eval);
        board[position.y][position.x] = EMPTY;
        return eval;
    } else if (has_won_the_game(board, position, color)) {
        printf("HAS_WON\n");
        board[position.y][position.x] = EMPTY;
        return INT_MAX;
    }

//    printf("Hello a:%d b:%d\n", alpha, beta);

    if (maximizing_player) {
        int max_eval = INT_MIN;
        while (1) {
            int x = 0;
            while (x < BOARD_SIZE) {
                if (board[y][x] == EMPTY) {
                    new_position.x = x;
                    new_position.y = y;
                    eval = minimax(new_position, depth - 1, alpha, beta, 0, board, opposite_color);
                    max_eval = max(max_eval, eval);
                    alpha = max(alpha, max_eval);
                    if (beta <= alpha) {
                        board[position.y][position.x] = EMPTY;
                        return max_eval;
                    }
                }
                x++;
            }
            y++;
        }
        board[position.y][position.x] = EMPTY;
        return max_eval;
    } else {
        int min_eval = INT_MAX;
        while (y < BOARD_SIZE) {
            int x = 0;
            while (x < BOARD_SIZE) {
                if (board[y][x] == EMPTY) {
                    new_position.x = x;
                    new_position.y = y;
                    eval = minimax(new_position, depth - 1, alpha, beta, 1, board,
                                   opposite_color);
                    min_eval = min(min_eval, eval);
                    beta = min(beta, min_eval);
                    if (beta <= alpha) {
                        board[position.y][position.x] = EMPTY;
                        return min_eval;
                    }
                }
                x++;
            }
            y++;
        }
        board[position.y][position.x] = EMPTY;
        return min_eval;
    }
}


t_position get_best_move(int board[BOARD_SIZE][BOARD_SIZE], int color) {
    int best_score = INT_MIN;
    int current_score = INT_MIN;
    t_position current_position = {0, 0};
    t_position best_position = {0, 0};

    while (1) {
        // It avoid of doing minmax on something empty
        current_position = find_nearest_position(board, current_position);

        if (current_position.x == -1) break;

        current_score = minimax(current_position, MAX_MINMAX_DEPTH, INT_MIN, INT_MAX, 1, board, color);

        printf("SCORE %d\n", current_score);

        if (current_score > best_score) {
            best_score = current_score;
            best_position = current_position;
        }

        current_position.x++;
    }
    return best_position;
}

